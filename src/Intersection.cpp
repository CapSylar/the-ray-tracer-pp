#include "Intersection.h"
#include <algorithm>
#include "Sphere.h"

//std::optional<Intersection> Intersection::get_hit(const std::vector<Intersection> &list)
//{
//    // assume the list is sorted
//    auto ret = std::lower_bound( list.begin() , list.end() , Intersection( 0 , nullptr ) );
//    if ( ret != list.end() )
//        return *ret;
//    return std::nullopt;
//}

bool operator == ( const Intersection &lhs , const Intersection &rhs )
{
    return ( lhs.t == rhs.t && lhs.obj == rhs.obj);
}

bool operator < ( const Intersection &lhs , const Intersection &rhs )
{
    return lhs.t < rhs.t;
}

std::ostream& operator << ( std::ostream& os , const Intersection &rhs )
{
    os << "[" << rhs.t << " " << rhs.obj << "]" ;

    return os;
}

Intersection::Intersection() : t(INFINITY) , obj(nullptr) {}
