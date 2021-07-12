#ifndef RAY_TRACER_COLOR3F_H
#define RAY_TRACER_COLOR3F_H

#include <iostream>
#include "utilities.h"

struct Color3f
{
    float r,g,b;

    explicit Color3f ( float red = 1 , float green = 1 , float blue = 1 ):r(red) , g(green) , b(blue) {}
};


inline Color3f operator * ( const Color3f &lhs , const Color3f &rhs )
{
    return Color3f( lhs.r * rhs.r , lhs.g * rhs.g , lhs.b * rhs.b );
}

inline bool operator == ( const Color3f &lhs , const Color3f &rhs )
{
    return (isEqualF(lhs.r, rhs.r) && isEqualF(lhs.g, rhs.g) && isEqualF(rhs.b, lhs.b)) ;
}

inline bool operator != ( const Color3f &lhs , const Color3f &rhs )
{
    return !(lhs == rhs);
}

inline Color3f operator * ( const Color3f &lhs , float scalar )
{
    return Color3f(lhs.r * scalar , lhs.g * scalar , lhs.b * scalar);
}

inline Color3f operator + ( const Color3f &lhs , const Color3f &rhs )
{
    return Color3f ( lhs.r + rhs.r , lhs.g + rhs.g , lhs.b + rhs.b );
}

inline Color3f operator - ( const Color3f &lhs , const Color3f &rhs )
{
    return Color3f ( lhs.r - rhs.r , lhs.g - rhs.g , lhs.b - rhs.b );
}

inline std::ostream& operator << ( std::ostream& os , const Color3f& rhs )
{
    os << "[" << rhs.r << " " << rhs.g << " " << rhs.b << "]" ;

    return os;
}



#endif //RAY_TRACER_COLOR3F_H
