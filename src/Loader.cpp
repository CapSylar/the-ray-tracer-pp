// just testing the wavefront obj loader

#include <string>
#include <iostream>
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "World.h"
#include "Triangle.h"
#include "PlainMaterial.h"
#include "KdTreeAccel.h"

void load_obj(World &world, const Mat4 &trans, const std::shared_ptr<Material>& material, const std::string &filename)
{
    // trans is a transformation to be applied on every triangle imported
    // remember that every triangle is in world space by definition

    tinyobj::ObjReaderConfig readerConfig;
    readerConfig.mtl_search_path = "./";
    readerConfig.triangulate = true; // triangulate all polygon faces

    tinyobj::ObjReader reader;

    // log errors if any

    if ( !reader.ParseFromFile(filename, readerConfig ))
    {
        if (!reader.Error().empty())
        {
            std::cerr << "TinyObjReader: " << reader.Error();
        }

        exit(1);
    }

    // get warnings if any

    if (!reader.Warning().empty())
    {
        std::cout << "TinyObjReader: " << reader.Warning();
    }

    auto &attrib = reader.GetAttrib();
    auto &shapes = reader.GetShapes();
//    auto &materials = reader.GetMaterials();

    std::vector<std::unique_ptr<Primitive>> list;

    // loop over shapes
    for (const auto & shape : shapes)
    {
        size_t index_offset = 0 ;
        // loop over the polygon faces
        for ( size_t f = 0 ; f < shape.mesh.num_face_vertices.size() ; ++f )
        {
            // get the number of vertices of the current face ( 3 is triangulate is on which it is )
            auto fv = ( size_t ) shape.mesh.num_face_vertices[f] ;

            Point3f point_triple[3];
            Vec3f normal_triple[3];

            bool isNormal = false;

            for ( size_t v = 0 ; v < fv ; ++v )
            {
                // access the vertex components
                tinyobj::index_t idx = shape.mesh.indices[index_offset + v];
                tinyobj::real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
                tinyobj::real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
                tinyobj::real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];

                point_triple[v] = trans * Point3f( vx , vy , vz );

                // Check if `normal_index` is zero or positive. negative = no normal data
                if (idx.normal_index >= 0)
                {
                    isNormal = true;
                    tinyobj::real_t nx = attrib.normals[3 * size_t(idx.normal_index) + 0];
                    tinyobj::real_t ny = attrib.normals[3 * size_t(idx.normal_index) + 1];
                    tinyobj::real_t nz = attrib.normals[3 * size_t(idx.normal_index) + 2];
                    normal_triple[v] = trans.multiplyNormal(Vec3f(nx,ny,nz)) ; // transform to new position
                }
            }

            // construct a triangle from the 3 vertices

            std::unique_ptr<Triangle> tri;
            if ( isNormal )
                tri = std::make_unique<Triangle>(material , point_triple[0] , point_triple[1] , point_triple[2] , normal_triple[0] , normal_triple[1] , normal_triple[2] );
            else
                tri = std::make_unique<Triangle>(material , point_triple[0] , point_triple[1] , point_triple[2]);

            list.push_back(std::move(tri));
            index_offset += fv;

            // per face material
            shape.mesh.material_ids[f];
        }
    }

    world.add( std::make_unique<KdTreeAccel>( std::move(list) ) );
}

