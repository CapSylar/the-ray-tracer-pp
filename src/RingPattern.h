#ifndef RAY_TRACER_RINGPATTERN_H
#define RAY_TRACER_RINGPATTERN_H

#include "ColorPattern.h"
#include "Color.h"
#include "Shape.h"

class RingPattern : public ColorPattern
{
public:
    Color a;
    Color b;

    explicit RingPattern( Color colorA = Color(1,1,1) , Color colorB = Color(0,0,0) ) : a(colorA) , b(colorB) {}
    explicit RingPattern ( const Shape &obj , Mat4 pattern_trans = Mat4::IDENTITY() , Color colorA = Color(1,1,1) ,
                              Color colorB = Color(0,0,0)) : ColorPattern( obj.inverse_trans , pattern_trans ), a(colorA) , b(colorB) {}

    [[nodiscard]] Color local_color_at(Point local_point) const override;
};


#endif //RAY_TRACER_RINGPATTERN_H
