#ifndef RAY_TRACER_UTILITIES_H
#define RAY_TRACER_UTILITIES_H

#include <limits>
#include <cmath>

constexpr auto eps = 0.00001f ; // 20 to increase the eps a bit, some calculations lose accuracy, but this isn't an issue
bool isEqualF (float lhs , float rhs);

#endif //RAY_TRACER_UTILITIES_H
