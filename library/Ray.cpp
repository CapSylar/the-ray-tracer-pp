#include "Ray.h"

std::ostream& operator << ( std::ostream& os , const Ray &rhs )
{
    os << "[" << rhs.origin << " " << rhs.direction << "]";
    return os;
}

Vector Ray::reflect(const Vector &in, const Vector &normal)
{
    // link to proof: http://paulbourke.net/geometry/reflected/#:~:text=If%20Ri%20is%20parallel,this%20is%20a%20glancing%20ray
    return in - normal * 2 * ( in * normal );
}

Point Ray::position( float t ) const
{
    return origin + direction * t ;
}

void Ray::transform (const Mat4& trans_matrix )
{
    // inverse_trans the ray by the matrix
    origin = trans_matrix * origin ;
    direction = trans_matrix * direction ;
}


