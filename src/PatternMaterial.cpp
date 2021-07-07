#include "PatternMaterial.h"

#include "ColorPattern.h"

Color PatternMaterial::get_albedo(Point point_on_surface)
{
    return pattern->color_at(point_on_surface);
}
