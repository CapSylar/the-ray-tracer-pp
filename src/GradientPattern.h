#ifndef RAY_TRACER_GRADIENTPATTERN_H
#define RAY_TRACER_GRADIENTPATTERN_H

#include "DualColorPattern.h"
 #include "Color3f.h"
#include "UnitShape.h"

class GradientPattern : public DualColorPattern
{
    using DualColorPattern::DualColorPattern;
public:
    [[nodiscard]] Color3f local_color_at(Point3f local_point) const override;
};


#endif //RAY_TRACER_GRADIENTPATTERN_H
