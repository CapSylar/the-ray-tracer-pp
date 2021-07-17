#ifndef RAY_TRACER_DUALCOLORPATTERN_H
#define RAY_TRACER_DUALCOLORPATTERN_H

#include "ColorPattern.h"
#include "Color3f.h"
#include "UnitShape.h"

class DualColorPattern : public ColorPattern
{
public:
    Color3f a;
    Color3f b;

    explicit DualColorPattern( Color3f colorA = Color3f(1,1,1) , Color3f colorB = Color3f(0,0,0) ) : a(colorA) , b(colorB) {}
    explicit DualColorPattern (const Mat4 &objectWorldToObject , Mat4 pattern_trans = Mat4(), Color3f colorA = Color3f(
            1, 1, 1),
                               Color3f colorB = Color3f(0, 0, 0)) : ColorPattern(objectWorldToObject , pattern_trans ), a(colorA) , b(colorB) {}
};

#endif //RAY_TRACER_DUALCOLORPATTERN_H
