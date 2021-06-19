#ifndef RAY_TRACER_COLOR_H
#define RAY_TRACER_COLOR_H

#include <iostream>
#include "utilities.h"

struct Color
{
    float r,g,b;

    explicit Color ( float red = 1 , float green = 1 , float blue = 1 ):r(red) , g(green) , b(blue) {}
};

Color operator * ( const Color &lhs , const Color &rhs );
bool operator == ( const Color &lhs , const Color &rhs );
bool operator != ( const Color &lhs , const Color &rhs );
Color operator * ( const Color &lhs , float scalar );
Color operator + ( const Color &lhs , const Color &rhs );
std::ostream& operator << ( std::ostream& os , const Color& rhs );

#endif //RAY_TRACER_COLOR_H
