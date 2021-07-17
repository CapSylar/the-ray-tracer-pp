#ifndef RAY_TRACER_KDTREEACCEL_H
#define RAY_TRACER_KDTREEACCEL_H

#include "Aggregate.h"
#include "Bounds3f.h"
#include <memory>

struct KdAccelNode;
struct BoundEdge;

// KdTreeAccel is the implementation of a K-d tree space partitioning data structure

class KdTreeAccel : public Aggregate
{
public:
    explicit KdTreeAccel(std::vector<std::unique_ptr<Primitive>> prims , int intersectCost = 80, int traversalCost = 1, float emptyBonus = 0.5f,
                         int maxPrims = 1, int maxDepth = -1);
    bool intersect(const Ray &ray, Intersection &record) const override;

    [[nodiscard]] Bounds3f worldBounds() const override;

private:
    void buildTree (int nodeNum , const Bounds3f &nodeBounds, const std::vector<Bounds3f> &allPrimBounds , int *primNums, int nPrimitives , int depth,
                    const std::unique_ptr<BoundEdge[]> edges[] , int *prims0 , int *prims1 , int badRefines = 0 ) ;

    const int intersectCost , traversalCost, maxPrims;
    const float emptyBonus;

    std::vector<std::unique_ptr<Primitive>> primitives; // stores the total primitives present in the tree
    std::vector<int> primitiveIndices;
    KdAccelNode *nodes;
    int nAllocedNodes, nextFreeNode;

    Bounds3f bounds;

    //***
    std::allocator<KdAccelNode> alloc;
};

// Node structure used in Kd Tree
// node made to be fit in 8bytes of memory to make in more cache friendly and increase performance ( assuming 4 byte floats )
struct KdAccelNode
{
    void initLeaf (int *primNums , int numPrimitives , std::vector<int> *primitiveIndices);
    void initInterior (int axis , int ac, float s);

    [[nodiscard]] float splitPos() const { return split; }
    [[nodiscard]] int nPrimitives() const { return nPrims >> 2; }
    [[nodiscard]] int splitAxis() const { return flags & 3; }
    [[nodiscard]] bool isLeaf() const { return (flags&3) == 3; }
    [[nodiscard]] int aboveChild() const { return abvChild >> 2; }

    union
    {
        float split; // used by interior node
        int onePrimitive; // used by leaf node
        int primitiveIndicesOffset; // used by leaf node
    };

    union
    {
        // flags: 0 == x split ,  1 == y split , 2 == z split , 3 == no split, => leaf node
        int flags; // used by leaf and interior node
        int nPrims; // used by leaf node
        int abvChild; // used by interior node
    };
};

enum class EdgeType { Start, End };

struct BoundEdge
{
    BoundEdge() = default;
    BoundEdge( float t, int primNum , bool starting ) : t(t) , primNum(primNum)
    {
        type = starting ? EdgeType::Start : EdgeType::End ;
    }

    float t;
    int primNum;
    EdgeType type;
};

#endif //RAY_TRACER_KDTREEACCEL_H
