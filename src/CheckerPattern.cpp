#include "CheckerPattern.h"

Color3f CheckerPattern::local_color_at(Point3f local_point) const
{
    return int (std::floor(local_point.x) + std::floor(local_point.y) + std::floor(local_point.z)) % 2 == 0 ? a : b ;
}
