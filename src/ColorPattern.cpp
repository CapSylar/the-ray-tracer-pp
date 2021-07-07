#include "ColorPattern.h"

#include "Color.h"
#include "Shape.h"

Color ColorPattern::color_at( const Point world_point ) const
{
    // transform from world frame to pattern frame
    const auto local_point = inverse_trans * world_point ;
    return local_color_at( local_point );
}
