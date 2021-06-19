#include "Ray.h"

std::ostream& operator << ( std::ostream& os , const Ray &rhs )
{
    os << "[" << rhs.origin << " " << rhs.direction << "]";

    return os;
}
