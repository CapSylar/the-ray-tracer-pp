#ifndef RAY_TRACER_RINGPATTERN_H
#define RAY_TRACER_RINGPATTERN_H

#include "ColorPattern.h"
#include "Color3f.h"
#include "UnitShape.h"

class RingPattern : public ColorPattern
{
public:
    Color3f a;
    Color3f b;

    explicit RingPattern( Color3f colorA = Color3f(1,1,1) , Color3f colorB = Color3f(0,0,0) ) : a(colorA) , b(colorB) {}
    explicit RingPattern ( const UnitShape &obj , Mat4 pattern_trans = Mat4::IDENTITY() , Color3f colorA = Color3f(1,1,1) ,
                              Color3f colorB = Color3f(0,0,0)) : ColorPattern( obj.inverse_trans , pattern_trans ), a(colorA) , b(colorB) {}

    [[nodiscard]] Color3f local_color_at(Point3f local_point) const override;
};


#endif //RAY_TRACER_RINGPATTERN_H
