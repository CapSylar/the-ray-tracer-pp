#include "Point3f.h"

float Point3f::operator[](int i) const
{
    // 0 => x , 1 => y , 2 => z
    if ( i == 0 ) return x;
    else if ( i == 1 ) return y;
    return z;
}

float &Point3f::operator[](int i)
{
    // 0 => x , 1 => y , 2 => z
    if ( i == 0 ) return x;
    else if ( i == 1 ) return y;
    return z;
}
