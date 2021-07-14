#include "Ray.h"

std::ostream& operator << ( std::ostream& os , const Ray &rhs )
{
    os << "[" << rhs.origin << " " << rhs.direction << "]";
    return os;
}

Vec3f Ray::reflect(const Vec3f &in, const Vec3f &normal)
{
    // link to proof: http://paulbourke.net/geometry/reflected/#:~:text=If%20Ri%20is%20parallel,this%20is%20a%20glancing%20ray
    return in - normal * 2 * ( in * normal );
}

Point3f Ray::position( float t ) const
{
    const auto  x = origin + direction * t ;
    return x;
}

void Ray::transform (const Mat4& trans_matrix )
{
    // worldToObject the ray by the matrix
    origin = trans_matrix * origin ;
    direction = trans_matrix * direction ;
}


