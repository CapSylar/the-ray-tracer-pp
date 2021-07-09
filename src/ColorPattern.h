#ifndef RAY_TRACER_COLORPATTERN_H
#define RAY_TRACER_COLORPATTERN_H

#include "Vec4.h" // TODO: check this again
#include "Mat4.h"

struct Color;
class UnitShape ;

struct ColorPattern
{
    Mat4 inverse_trans;

    ColorPattern() = default;
    explicit ColorPattern( Mat4 object_trans , Mat4 pattern_trans ) : inverse_trans(pattern_trans.invert() * object_trans) {}

    [[nodiscard]] virtual Color local_color_at (Point local_point ) const  = 0 ;
    [[nodiscard]] Color color_at ( Point world_point ) const ;
};


#endif //RAY_TRACER_COLORPATTERN_H
