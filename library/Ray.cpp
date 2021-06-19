#include "Ray.h"

std::ostream& operator << ( std::ostream& os , const Ray &rhs )
{
    os << "[" << rhs.origin << " " << rhs.direction << "]";
    return os;
}

Vector Ray::reflect(const Vector &in, const Vector &normal)
{
    return in - normal * 2 * ( in * normal );
}
