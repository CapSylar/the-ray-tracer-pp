#include "RingPattern.h"

Color RingPattern::local_color_at(Point local_point) const
{
    return (int) std::floor(std::sqrt(local_point.x*local_point.x + local_point.z*local_point.z)) % 2 == 0 ? a : b ;
}
