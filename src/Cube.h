#ifndef RAY_TRACER_CUBE_H
#define RAY_TRACER_CUBE_H

#include "Shape.h"
#include <utility>
#include <cmath>
#include "utilities.h"

class Cube : public Shape
{
public:
    explicit Cube ( Material *mat , Mat4 trans = Mat4()  ): Shape ( trans , mat ) {}

private:
    static std::pair<float,float> get_axis_intersections( float origin , float direction ) ;

public:
    void local_intersect(const Ray &ray, std::vector<Intersection> &list) const override;
    [[nodiscard]] Vector local_normal_at(const Point &point) const override;
};


#endif //RAY_TRACER_CUBE_H
