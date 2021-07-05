#ifndef RAY_TRACER_UTILITIES_H
#define RAY_TRACER_UTILITIES_H

#include <limits>
#include <cmath>

constexpr auto eps = 25 * std::numeric_limits<float>::epsilon(); // 20 to increase the eps a bit, some calculations lose accuracy, but this isn't an issue
bool isEqual_f (float lhs , float rhs);

#endif //RAY_TRACER_UTILITIES_H
