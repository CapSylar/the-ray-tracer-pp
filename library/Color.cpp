#include "Color.h"

Color operator * ( const Color &lhs , const Color &rhs )
{
    return Color( lhs.r * rhs.r , lhs.g * rhs.g , lhs.b * rhs.b );
}

bool operator == ( const Color &lhs , const Color &rhs )
{
    return (isEqual_f(lhs.r,rhs.r) && isEqual_f(lhs.g,rhs.g) && isEqual_f(rhs.b,lhs.b)) ;
}

bool operator != ( const Color &lhs , const Color &rhs )
{
    return !(lhs == rhs);
}

Color operator * ( const Color &lhs , float scalar )
{
    return Color(lhs.r * scalar , lhs.g * scalar , lhs.b * scalar);
}

Color operator + ( const Color &lhs , const Color &rhs )
{
    return Color ( lhs.r + rhs.r , lhs.g + rhs.g , lhs.b + rhs.b );
}

std::ostream& operator << ( std::ostream& os , const Color& rhs )
{
    os << "[" << rhs.r << " " << rhs.g << " " << rhs.b << "]" ;

    return os;
}

