#include "GradientPattern.h"

Color3f GradientPattern::local_color_at(Point3f local_point) const
{
    return a + (b-a) * (local_point.x-std::floor(local_point.x)) ; // linear interpolate
}
