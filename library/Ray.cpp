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
