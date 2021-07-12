#ifndef RAY_TRACER_TRIANGLE_H
#define RAY_TRACER_TRIANGLE_H

#include "UnitShape.h"

#include "Vec3f.h"
#include "Point3f.h"

class Triangle : public Shape
{
public:
    const Point3f _p1,_p2,_p3;
    const Vec3f e1,e2;
    const Vec3f _n1,_n2,_n3; // normal for every vertex

    bool isSmooth; // yes => has normals for all vertices

    Triangle(Material *mat, Point3f p1, Point3f p2, Point3f p3) : Shape(mat), _p1(p1) , _p2(p2) , _p3(p3) , e1(p2 - p1), e2(p3 - p1)  , _n1(cross(e1,e2).normalize()) , isSmooth(false) {}
    Triangle( Material *mat , Point3f p1 , Point3f p2 , Point3f p3 , Vec3f n1 , Vec3f n2, Vec3f n3 ) :
        Shape(mat) , _p1(p1) , _p2(p2) , _p3(p3) , _n1(n1) , _n2(n2) , _n3(n3) , e1(p2-p1) , e2(p3-p1) , isSmooth(true) {}

    void local_intersect(const Ray &ray, std::vector<Intersection> &list) const override;
    [[nodiscard]] Vec3f local_normal_at(const Point3f &point) const override;
};


#endif //RAY_TRACER_TRIANGLE_H
