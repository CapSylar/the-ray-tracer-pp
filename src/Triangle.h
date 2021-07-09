#ifndef RAY_TRACER_TRIANGLE_H
#define RAY_TRACER_TRIANGLE_H

#include "UnitShape.h"

class Triangle : public Shape
{
public:
    const Vec4 _p1,_p2,_p3;
    const Vec4 e1,e2;
    const Vec4 _n1,_n2,_n3; // normal for every vertex

    bool isSmooth; // yes => has normals for all vertices

    Triangle(Material *mat, Vec4 p1, Vec4 p2, Vec4 p3) : Shape(mat), _p1(p1) , _p2(p2) , _p3(p3) , e1(p2 - p1), e2(p3 - p1)  , _n1(Vec4::cross(e1,e2).normalize()) , isSmooth(false) {}
    Triangle( Material *mat , Vec4 p1 , Vec4 p2 , Vec4 p3 , Vec4 n1 , Vec4 n2, Vec4 n3 ) :
        Shape(mat) , _p1(p1) , _p2(p2) , _p3(p3) , _n1(n1) , _n2(n2) , _n3(n3) , e1(p2-p1) , e2(p3-p1) , isSmooth(true) {}

    void local_intersect(const Ray &ray, std::vector<Intersection> &list) const override;
    [[nodiscard]] Vector local_normal_at(const Point &point) const override;
};


#endif //RAY_TRACER_TRIANGLE_H
