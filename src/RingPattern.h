#ifndef RAY_TRACER_RINGPATTERN_H
#define RAY_TRACER_RINGPATTERN_H

#include "DualColorPattern.h"
#include "ColorPattern.h"
#include "Color3f.h"
#include "UnitShape.h"

class RingPattern : public DualColorPattern
{
    using DualColorPattern::DualColorPattern;
public:
    [[nodiscard]] Color3f local_color_at(Point3f local_point) const override;
};


#endif //RAY_TRACER_RINGPATTERN_H
