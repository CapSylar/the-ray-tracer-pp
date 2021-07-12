#ifndef RAY_TRACER_COLORPATTERN_H
#define RAY_TRACER_COLORPATTERN_H

#include "Mat4.h"

struct Color3f;
class UnitShape ;

struct ColorPattern
{
    Mat4 inverse_trans;

    ColorPattern() = default;
    explicit ColorPattern( Mat4 object_trans , Mat4 pattern_trans ) : inverse_trans(pattern_trans.invert() * object_trans) {}

    [[nodiscard]] virtual Color3f local_color_at (Point3f local_point ) const  = 0 ;
    [[nodiscard]] Color3f color_at ( Point3f world_point ) const ;
};


#endif //RAY_TRACER_COLORPATTERN_H
