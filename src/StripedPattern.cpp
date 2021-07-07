#include <Vec4.h>
#include "StripedPattern.h"
#include "Color.h"

Color StripedPattern::local_color_at(Point local_point) const
{
    // local_point must be a point in "pattern" space not world space, nor object space
    return ( int ) std::floor(local_point.x) % 2 == 0 ? a : b;
}
