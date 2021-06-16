#ifndef RAY_TRACER_UTILITIES_H
#define RAY_TRACER_UTILITIES_H

#include <limits>
#include <cmath>

constexpr auto eps = std::numeric_limits<float>::epsilon();

bool isEqual_f (float lhs , float rhs);

#endif //RAY_TRACER_UTILITIES_H
