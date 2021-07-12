#include "StripedPattern.h"
#include "Color3f.h"

#include "Point3f.h"


Color3f StripedPattern::local_color_at(Point3f local_point) const
{
    // local_point must be a point in "pattern" space not world space, nor object space
    return ( int ) std::floor(local_point.x) % 2 == 0 ? a : b;
}
