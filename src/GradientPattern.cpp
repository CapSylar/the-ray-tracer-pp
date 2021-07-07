#include "GradientPattern.h"

Color GradientPattern::local_color_at(Point local_point) const
{
    return a + (b-a) * (local_point.x-std::floor(local_point.x)) ; // linear interpolate
}
