#ifndef RAY_TRACER_RAY_H
#define RAY_TRACER_RAY_H

#include "Vec4.h"
#include "Mat4.h"

struct Ray
{
    Ray ( Point orig , Vector dir ): origin(orig) , direction(dir) {}

    Point position( float t )
    {
        return origin + direction * t ;
    }

    void transform (const Mat4& trans_matrix )
    {
        // transform the ray by the matrix
        origin = trans_matrix * origin ;
        direction = trans_matrix * direction ;
    }

    Point origin;
    Vector direction;
};

std::ostream& operator << ( std::ostream& os , const Ray &rhs );


#endif //RAY_TRACER_RAY_H
