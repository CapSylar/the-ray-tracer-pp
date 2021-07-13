#ifndef RAY_TRACER_INTERSECTION_H
#define RAY_TRACER_INTERSECTION_H

#include <optional>
#include <vector>
#include <fstream>

class Primitive;

class Intersection
{
public:
    Intersection( float tt , const Primitive *shape ) : t(tt) , obj(shape) {}

    //TODO: an initializer for a delegating constructor must appear once
    Intersection ( float tt , const Primitive *shape , float u , float v ) : t(tt) , obj(shape) , _u(u) , _v(v) {}

    static std::optional<Intersection> get_hit( const std::vector<Intersection> &list );

    float t; // t value for Ray that intersection with object
    const Primitive *obj;
    float _u = 0  ,_v = 0   ; // for triangles

    //TODO: generalize the intersection record since primitives other than triangles won't use the u and v values
    //TODO: i should also pass std::vector<Intersection *> and not std::vector<Intersection> which might help performance and is needed above
};

bool operator == ( const Intersection &lhs , const Intersection &rhs );
bool operator < ( const Intersection &lhs , const Intersection &rhs );
std::ostream& operator << ( std::ostream& os , const Intersection &rhs );

#endif //RAY_TRACER_INTERSECTION_H
