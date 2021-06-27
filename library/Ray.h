#ifndef RAY_TRACER_RAY_H
#define RAY_TRACER_RAY_H

#include "Vec4.h"
#include "Mat4.h"

class Ray
{
public:
    Ray ( Point orig , Vector dir ): origin(orig) , direction(dir) {}

    Point position( float t ) const ;
    void transform (const Mat4& trans_matrix );
    static Vector reflect ( const Vector &in , const Vector &normal );

    Point origin;
    Vector direction;
};

Vector reflect ( const Vector &in , const Vector &normal );
std::ostream& operator << ( std::ostream& os , const Ray &rhs );


#endif //RAY_TRACER_RAY_H
