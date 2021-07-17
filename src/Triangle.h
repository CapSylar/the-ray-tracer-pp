#ifndef RAY_TRACER_TRIANGLE_H
#define RAY_TRACER_TRIANGLE_H

#include <utility>

#include "UnitShape.h"

#include "Vec3f.h"
#include "Point3f.h"

class Triangle : public GeometricPrimitive
{
public:
    const Point3f _p1,_p2,_p3;
    const Vec3f e1,e2;
    const Vec3f _n1,_n2,_n3; // normal for every vertex

    bool isSmooth; // yes => has normals for all vertices

    Triangle(std::shared_ptr<Material> mat, Point3f p1, Point3f p2, Point3f p3) : GeometricPrimitive(std::move(mat)), _p1(p1) , _p2(p2) , _p3(p3) , e1(p2 - p1), e2(p3 - p1)  , _n1(cross(e1, e2).normalize()) , isSmooth(false) {}
    Triangle( std::shared_ptr<Material> mat , Point3f p1 , Point3f p2 , Point3f p3 , Vec3f n1 , Vec3f n2, Vec3f n3 ) :
            GeometricPrimitive(std::move(mat)) , _p1(p1) , _p2(p2) , _p3(p3) , e1(p2-p1) , e2(p3-p1) ,  _n1(n1) , _n2(n2) , _n3(n3) ,  isSmooth(true) {}

    bool intersect(const Ray &ray, Intersection &record) const override ;
    [[nodiscard]] Vec3f normal_at(const Point3f &point) const override ;
    [[nodiscard]] Bounds3f worldBounds() const override;

    virtual ~Triangle();
};


#endif //RAY_TRACER_TRIANGLE_H
