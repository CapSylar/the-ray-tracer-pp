#include "Shape.h"
#include "Material.h"
#include "Ray.h"

Shape::~Shape()
{
    delete material;
}

void Shape::intersect(const Ray &ray, std::vector<Intersection> &list) const
{
    local_intersect( ray , list );
}

Vector Shape::normal_at(const Point &surface_point) const
{
    return local_normal_at(surface_point);
}
