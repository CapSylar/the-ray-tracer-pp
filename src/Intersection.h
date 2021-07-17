#ifndef RAY_TRACER_INTERSECTION_H
#define RAY_TRACER_INTERSECTION_H

#include <optional>
#include <vector>
#include <fstream>

class Primitive;

class Intersection
{
public:
    Intersection() = default;
    explicit Intersection(const Primitive *shape) : obj(shape) {}
    Intersection(const Primitive *shape, float u, float v) : obj(shape) , _u(u) , _v(v) {}

    const Primitive *obj = nullptr ;
    float _u = 0  ,_v = 0   ; // for triangles
};

std::ostream& operator << ( std::ostream& os , const Intersection &rhs );

#endif //RAY_TRACER_INTERSECTION_H
