#include "PatternMaterial.h"

#include "ColorPattern.h"

Color3f PatternMaterial::get_albedo(Point3f point_on_surface)
{
    return pattern->color_at(point_on_surface);
}
