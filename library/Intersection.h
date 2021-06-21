#ifndef RAY_TRACER_INTERSECTION_H
#define RAY_TRACER_INTERSECTION_H

#include "Sphere.h"

class Intersection
{
public:
    Intersection( float tt , const Sphere &sphere ) : t(tt) , obj(&sphere) {}

    static std::optional<Intersection> get_hit( const std::vector<Intersection> &list );


    float t; // t value for Ray that intersection with object
    const Sphere *obj; // TODO: change it from sphere to a more general object
};

bool operator == ( const Intersection &lhs , const Intersection &rhs );
bool operator < ( const Intersection &lhs , const Intersection &rhs );
std::ostream& operator << ( std::ostream& os , const Intersection &rhs );

#endif //RAY_TRACER_INTERSECTION_H
