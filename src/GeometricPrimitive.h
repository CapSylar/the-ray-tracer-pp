#ifndef RAY_TRACER_GEOMETRICPRIMITIVE_H
#define RAY_TRACER_GEOMETRICPRIMITIVE_H

#include "Primitive.h"

class GeometricPrimitive : public Primitive
{
public:
    explicit GeometricPrimitive( Material *mat ) : material(mat) {}

    [[nodiscard]] const Material *getMaterial() const override;

    Material *getMaterial() override;

    Material* material;

    virtual ~GeometricPrimitive() ;
};

#endif //RAY_TRACER_GEOMETRICPRIMITIVE_H
