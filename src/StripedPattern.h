#ifndef RAY_TRACER_STRIPEDPATTERN_H
#define RAY_TRACER_STRIPEDPATTERN_H

#include "DualColorPattern.h"
#include "Color3f.h"
#include "UnitShape.h"

class StripedPattern : public DualColorPattern
{
    using DualColorPattern::DualColorPattern;
public:
    [[nodiscard]] Color3f local_color_at(Point3f local_point) const override;
};

#endif //RAY_TRACER_STRIPEDPATTERN_H
