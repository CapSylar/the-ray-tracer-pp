#ifndef RAY_TRACER_TRIANGLE_H
#define RAY_TRACER_TRIANGLE_H

#include "UnitShape.h"

class Triangle : public Shape
{
public:
    const Vec4 _p1,_p2,_p3;
    const Vec4 e1,e2;
    const Vec4 normal;

    Triangle(Material *mat, Vec4 p1, Vec4 p2, Vec4 p3) : Shape(mat), _p1(p1) , _p2(p2) , _p3(p3) , e1(p2 - p1), e2(p3 - p1) , normal(Vec4::cross(e2,e1).normalize()) {}

    void local_intersect(const Ray &ray, std::vector<Intersection> &list) const override;
    [[nodiscard]] Vector local_normal_at(const Point &point) const override;
};


#endif //RAY_TRACER_TRIANGLE_H
