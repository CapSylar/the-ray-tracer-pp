#include "KdTreeAccel.h"
#include <memory>
#include <cstring>
#include <algorithm>
#include <utility>
#include "Vec3f.h"
#include "Ray.h"
#include "Intersection.h"

KdTreeAccel::KdTreeAccel(std::vector<std::unique_ptr<Primitive>> prims, int intersectCost, int traversalCost, float emptyBonus,
                         int maxPrims, int maxDepth) : intersectCost(intersectCost) , traversalCost(traversalCost) , maxPrims(maxPrims),
                                                       emptyBonus(emptyBonus) , primitives(std::move(prims)) , nodes(nullptr)
{
    nAllocedNodes = nextFreeNode = 0;

     if ( maxDepth <= 0 ) // we have to compute it ourselves
         maxDepth = ( int ) std::round(8 + 1.3f * std::log2(primitives.size())) ;

     // compute bounds for kd-tree construction
     std::vector<Bounds3f> primBounds; // save the computed bounds of all primitives along the way since these calculations are slow
     // collect all the world bounds of all the primitives and join them

     for (const auto & primitive : primitives)
     {
         const auto bound = primitive->worldBounds();
         bounds = Union( bounds , bound );
         primBounds.push_back(bound); // save the bounds of the current Primitive
     }

     std::unique_ptr<BoundEdge[]> edges[3];

    for (auto & edge : edges)
    {
        edge = std::make_unique<BoundEdge[]>(2 * primitives.size()); // each primitive needs 2 points when projected on axis
    }

    auto prims0 = std::make_unique<int[]>( primitives.size() );
    auto prims1 = std::make_unique<int[]>( (maxDepth+1)* primitives.size() );

    // initialise primNums for kd-tree construction
    auto primNums = std::make_unique<int[]>( primitives.size() );
    // initially all shapes overlap the root node, so insert all indices reflecting this
    for ( size_t i = 0 ; i < primitives.size() ; ++i )
        primNums[i] = i;

    // build the tree
    buildTree(0 , bounds , primBounds , primNums.get() , primitives.size() , maxDepth , edges , prims0.get() , prims1.get() );
}

bool KdTreeAccel::intersect(const Ray &ray, Intersection &record) const
{
    struct KdToDo
    {
        const KdAccelNode *node;
        float tMin , tMax;
    };

    float tMin, tMax;

    if ( !bounds.intersect( ray , &tMin , &tMax ))
        return false;

    Vec3f invDir ( 1 / ray.direction.x , 1/ray.direction.y , 1/ray.direction.z );
    constexpr int maxTodo = 64;
    // record the nodes yet to be processed
    KdToDo todo[maxTodo];
    int todoPos = 0;
    bool hit = false;

    const KdAccelNode *node = nodes; // start with root

    while ( node != nullptr )
    {
        // we can stop if we found a hit closer than the current node
        // but in our case we want to record all hits
        if ( ray.tMax < tMin )
            break;

        if ( !node->isLeaf() ) // is an interior node
        {
            int axis = node->splitAxis();
            // compute t value of split plane along current axis
            float tPlane = (node->splitPos() - ray.origin[axis]) * invDir[axis];

            const KdAccelNode *firstChild, *secondChild;
            // determine which of the two we "see" first

            bool isBelowFirst = (ray.origin[axis] < node->splitPos() || // handle rare second case
                   ( ray.origin[axis] == node->splitPos() && ray.direction[axis] <= 0) );

            if ( isBelowFirst )
            {
                firstChild = node + 1;
                secondChild = nodes + node->aboveChild();
            }
            else
            {
                firstChild = nodes + node->aboveChild();
                secondChild = node + 1;
            }

            // at this point it may not be necessary to process both children of this node.
            // it may miss one of the children but never both of them
            // since otherwise we would not have visited the current node in the first place

            // we miss the second child
            if ( tPlane > tMax || tPlane <= 0 )
                node = firstChild;

            // we miss the first child
            else if ( tPlane < tMin )
                node = secondChild;

            // we hit both children
            else
            {
                todo[todoPos].node = secondChild;
                todo[todoPos].tMin = tPlane;
                todo[todoPos].tMax = tMax;
                ++todoPos;

                // handle first child
                node = firstChild;
                tMax = tPlane;
            }
        }
        else // process current leaf node
        {
            int nPrimitives = node->nPrimitives();
            // see how can access them
            if ( nPrimitives == 1 )
            {
                // in this case the index is stored directly in the node
                const auto &p = primitives[node->onePrimitive];
                // intersect the primitive

                if(p->intersect(ray , record ))
                    hit = true;
            }
            else
            {
                for ( int i = 0 ; i < nPrimitives ; ++i )
                {
                    // in this case the number stored is essentially an index into an index
                    int index = primitiveIndices[node->primitiveIndicesOffset + i];
                    const auto &p = primitives[index];

                    if(p->intersect(ray , record ))
                        hit = true;
                }
            }

            // grab next node to process
            if ( todoPos > 0 )
            {
                --todoPos;
                const auto to = todo[todoPos];
                node = to.node;
                tMin = to.tMin;
                tMax = to.tMax;
            }
            else
                break;
        }

    }

    return hit;
}
void KdTreeAccel::buildTree(int nodeNum, const Bounds3f &nodeBounds, const std::vector<Bounds3f> &allPrimBounds, int *primNums,
                            int nPrimitives, int depth, const std::unique_ptr<BoundEdge[]> *edges, int *prims0, int *prims1,
                            int badRefines)
{
    // get next free node from nodes array of KdTreeNodes
    if ( nextFreeNode == nAllocedNodes ) // no more free space
    {
        int nNewAllocNodes = std::max(2 * nAllocedNodes , 512 );
        KdAccelNode *n = alloc.allocate(nNewAllocNodes);

        if ( nAllocedNodes > 0 ) // we had allocated something before, free that after copying the data over
        {
            std::memcpy( n , nodes , nAllocedNodes * sizeof(KdAccelNode));
            alloc.deallocate(nodes,nAllocedNodes);
        }

        nodes = n;
        nAllocedNodes = nNewAllocNodes;
    }

    ++nextFreeNode;

    if ( nPrimitives <= maxPrims || depth == 0 )
    {
        nodes[nodeNum].initLeaf( primNums , nPrimitives , &primitiveIndices );
        return;
    }

    // this node is an internal node, choose splitting plane => classify primitives => repeat

    int bestAxis = -1 ,  bestOffset = -1; // keeps track of best so far
    float bestCost = INFINITY; // lowest cost so far
    const float oldCost = intersectCost * float(nPrimitives);
    float totalSA = nodeBounds.surfaceArea();
    float invTotalSA = 1 / totalSA;

    Vec3f d = nodeBounds.diagonal();

    // first try to split along the axis with the largest spatial extent, since it tends to give regions of space that tend toward being square in shape
    int axis = nodeBounds.maximumExtent() ; // longest axis of bounding box

    int retries = 0;
    retrySplit:
        for ( int i = 0 ; i < nPrimitives ; ++i )
        {
            // fill the edges array
            int pn = primNums[i];
            const Bounds3f &currentBounds = allPrimBounds[pn];
            edges[axis][2*i] = BoundEdge( currentBounds.pMin[axis] , pn , true );
            edges[axis][2*i+1] = BoundEdge( currentBounds.pMax[axis] , pn , false );
        }

        // now sort the points in the edges[]

        std::sort( &(edges[axis][0] ), &(edges[axis][nPrimitives*2] ), []( const BoundEdge &e0 , const BoundEdge &e1 ) -> bool
        {
            if ( e0.t == e1.t ) // very unlikely, but if it happens type start < type end
                return e0.type < e1.type ;
            return e0.t < e1.t;
        } );

        // compute cost af all split for the current chosen axis
        int nBelow = 0 , nAbove = nPrimitives;
        // at first edge point, no prims are below hence = 0 and all prims are above it hence = total_num

        // now we sweep along the axis looking for splitting positions
        for ( int i = 0 ; i < 2 * nPrimitives ; ++i )
        {
            // arrived at the end of a primitive, it is now below the splitting plane
            if ( edges[axis][i].type == EdgeType::End )
                --nAbove;

            const float edgeT = edges[axis][i].t;

            //TODO: what the purpose of this condition?
            if ( edgeT > nodeBounds.pMin[axis] && edgeT < nodeBounds.pMax[axis] )
            {
                // compute cost for split at the current edge
                // using SAH = surface area heuristic

                // first compute the Surface Area for the two children that have been split
                int otherAxis0 = (axis+1) % 3 , otherAxis1 = ( axis + 2 ) % 3;
                // surface area below the splitting plane
                float belowSA = 2 * ( d[otherAxis0] * d[otherAxis1] +
                                      (edgeT - nodeBounds.pMin[axis]) * ( d[otherAxis1] + d[otherAxis0] )); // 3 surfaces * 2

                float aboveSA = 2 * ( d[otherAxis0] * d[otherAxis1] +
                        ( nodeBounds.pMax[axis] - edgeT ) * ( d[otherAxis0] + d[otherAxis1 ])) ;

                const float probBelow = belowSA * invTotalSA; // probability that a ray hits the above portion = AboveSA / totSA
                const float probAbove = aboveSA * invTotalSA;

                const float bonus = ( nAbove == 0 || nBelow == 0 ) ? emptyBonus : 0 ;
                const float cost = traversalCost + intersectCost * ( 1 - bonus ) * ( probBelow * nBelow + probAbove * nAbove );

                if ( cost < bestCost ) // new best
                {
                    bestCost = cost;
                    bestAxis = axis;
                    bestOffset = i; // record edge point index along this best axis
                }
            }

            // arrived at the start of a primitive, it is not above the splitting plane
            if ( edges[axis][i].type == EdgeType::Start )
                ++nBelow;
        }

        if ( bestAxis == -1  && retries <= 1 )
        {
            ++retries;
            // advance to the next axis
            axis = ( axis + 1 ) % 3;
            goto retrySplit;
        }

    if ( bestCost > oldCost ) ++badRefines;

    // It is possible that the cost of the best split is still higher than the cost of not splitting at all
    // Should we construct a leaf node and stop the process ? Wait...
    // It's worth allowing a few slightly poor refinement since later splits may be able to find better ones given a smaller subset to consider

    // but ifs much worse and there aren't many primitives then we stop here

    // TODO: how could bestAxis be -1 since bestCost start with infinity ?
    // 4, 16 are magik numbers, experiment with them
    if ((bestCost > 4 * oldCost && nPrimitives < 16) || ( bestAxis == -1 ) || badRefines == 3 )
    {
        nodes[nodeNum].initLeaf(primNums , nPrimitives , &primitiveIndices);
        return;
    }

    // we chose to split at this point
    // classify primitives with respect to split

    int n0 = 0, n1 = 0;
    // n0 number of prims below, n1 number of prims above the splitting plane

    for ( int i = 0 ; i < bestOffset ; ++i )
        if ( edges[bestAxis][i].type == EdgeType::Start )
            prims0[n0++] = edges[bestAxis][i].primNum;
    for ( int i = bestOffset+1 ; i < 2 *nPrimitives ; ++i )
        if ( edges[bestAxis][i].type == EdgeType::End )
            prims1[n1++] = edges[bestAxis][i].primNum;

    // init children nodes
    float tSplit = edges[bestAxis][bestOffset].t;

    // create 2 bounds for the children
    Bounds3f bounds0 = nodeBounds, bounds1 = nodeBounds;
    // resize the bounds to reflect the split, upper bound of lower bounding box is tSplit, lower bound of upper bounding box is tSplit
    bounds0.pMax[bestAxis] = bounds1.pMin[bestAxis] = tSplit;
    buildTree( nodeNum + 1 , bounds0 , allPrimBounds , prims0 , n0 , depth-1 , edges , prims0 , prims1 + nPrimitives , badRefines );

    int aboveChild = nextFreeNode;
    nodes[nodeNum].initInterior( bestAxis , aboveChild , tSplit );
    buildTree( aboveChild , bounds1 , allPrimBounds , prims1 , n1 , depth - 1 , edges , prims0 , prims1 + nPrimitives , badRefines );
}

Bounds3f KdTreeAccel::worldBounds() const
{
    return bounds;
}

void KdAccelNode::initInterior(int axis, int ac, float s)
{
    split = s;
    flags = axis;
    abvChild |= (ac << 2);
}

void KdAccelNode::initLeaf(int *primNums, int numPrimitives, std::vector<int> *primitiveIndices)
{
    // !! remember flags and nPrims share the same memory space,
    flags = 3;
    nPrims |= ( numPrimitives << 2 );

    if (numPrimitives == 0 ) // no primitives in this leaf
        onePrimitive = 0;
    else if ( numPrimitives == 1 ) // we can store its index directly in the structure
        onePrimitive = primNums[0];
    else
    {
        primitiveIndicesOffset = primitiveIndices->size(); // store index into the primitiveIndices vector
        for ( int i = 0 ; i < numPrimitives ; ++i )
            primitiveIndices->push_back(primNums[i]); // then store the actual indices that we want in the vector
    }
}
