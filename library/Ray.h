#ifndef RAY_TRACER_RAY_H
#define RAY_TRACER_RAY_H

#include "Mat4.h"

#include "Vec3f.h"
#include "Point3f.h"

class Ray
{
public:
    Ray ( Point3f orig , Vec3f dir , float tMax = INFINITY ): origin(orig) , direction(dir) , tMax(tMax) {}

    [[nodiscard]] Point3f position( float t ) const ;
    void transform (const Mat4& trans_matrix );
    static Vec3f reflect ( const Vec3f &in , const Vec3f &normal );

    Point3f origin;
    Vec3f direction;
    mutable float tMax;
};

Vec3f reflect ( const Vec3f &in , const Vec3f &normal );
std::ostream& operator << ( std::ostream& os , const Ray &rhs );


#endif //RAY_TRACER_RAY_H
