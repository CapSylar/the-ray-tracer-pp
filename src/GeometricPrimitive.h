#ifndef RAY_TRACER_GEOMETRICPRIMITIVE_H
#define RAY_TRACER_GEOMETRICPRIMITIVE_H

#include "Primitive.h"
#include <memory>
#include <utility>

class GeometricPrimitive : public Primitive
{
public:
    explicit GeometricPrimitive( Material *mat ) : material(mat) {}
    explicit GeometricPrimitive ( std::shared_ptr<Material> mat ) : material(std::move(mat)) {}

    [[nodiscard]] std::shared_ptr<const Material> getMaterial() const override;
    std::shared_ptr<Material> getMaterial() override;

    void setMaterial(std::shared_ptr<Material> mat) override;

    // we would want to share material between primitive
    // we would want to create a new material for each triangle in a model with 1,500,000 triangles ? No
    std::shared_ptr<Material> material;
};

#endif //RAY_TRACER_GEOMETRICPRIMITIVE_H
