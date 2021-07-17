#include "Intersection.h"
#include <algorithm>
#include "Sphere.h"

std::ostream& operator << ( std::ostream& os , const Intersection &rhs )
{
    os << "[" << rhs.obj << " " << rhs._u << " " << rhs._v << "]" ;

    return os;
}