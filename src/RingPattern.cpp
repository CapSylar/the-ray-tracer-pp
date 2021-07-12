#include "RingPattern.h"

Color3f RingPattern::local_color_at(Point3f local_point) const
{
    return (int) std::floor(std::sqrt(local_point.x*local_point.x + local_point.z*local_point.z)) % 2 == 0 ? a : b ;
}
