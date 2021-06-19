#include "Intersection.h"

#include <algorithm>
//#include <optional>

std::optional<Intersection> Intersection::get_hit(const std::vector<Intersection> &list)
{
    // assume the list is sorted
    auto ret = std::lower_bound( list.begin() , list.end() , Intersection( 0 , Sphere() ) ,
                                 []( const Intersection &inter , const Intersection &inter2 ) -> bool { return inter.t < inter2.t; } );
    if ( ret != list.end() )
        return *ret;
    return std::nullopt;
}

bool operator == ( const Intersection &lhs , const Intersection &rhs )
{
    return ( lhs.t == rhs.t && &(lhs.obj) == &(rhs.obj));
}
