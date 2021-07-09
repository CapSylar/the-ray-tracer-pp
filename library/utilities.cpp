#include "utilities.h"

//TODO: make inline
bool isEqual_f (float lhs , float rhs)
{
    return std::abs(lhs-rhs) < eps*100 ; // TODO: remove magick 100
}
