#ifndef RAY_TRACER_LOADER_H
#define RAY_TRACER_LOADER_H

#include "World.h"

void load_obj(World &world, const Mat4 &trans, const std::shared_ptr<Material> &material, const std::string &filename);

#endif //RAY_TRACER_LOADER_H
