#include "ColorPattern.h"

#include "Color3f.h"
#include "UnitShape.h"

Color3f ColorPattern::color_at( const Point3f world_point ) const
{
    // transform from world frame to pattern frame
    const auto local_point = inverse_trans * world_point ;
    return local_color_at( local_point );
}
