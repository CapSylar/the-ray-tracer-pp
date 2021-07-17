#ifndef RAY_TRACER_AGGREGATE_H
#define RAY_TRACER_AGGREGATE_H

#include "Primitive.h"

class Aggregate : public Primitive
{
public:
    //TODO: flag some error or throw some exception when some of these methods are called

    [[nodiscard]] std::shared_ptr<const Material> getMaterial() const override; // should never be called
    std::shared_ptr<Material> getMaterial() override;

    void setMaterial(std::shared_ptr<Material> material) override;

    [[nodiscard]] Vec3f normal_at(const Point3f &surface_point) const override; // should never be called
};


#endif //RAY_TRACER_AGGREGATE_H
