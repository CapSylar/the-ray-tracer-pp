#include "Transformation.h"
#include "Mat4.h"

Mat4 getTranslation( float x , float y , float z )
{
    return {1,0,0,x  ,0,1,0,y  ,0,0,1,z  ,0,0,0,1};
}

Mat4 getScaling( float x , float y , float z )
{
    return {x,0,0,0   ,0,y,0,0,  0,0,z,0  ,0,0,0,1};
}

Mat4 getRotationX ( float r )
{
    float cos = cosf(r);
    float sin = sinf(r);
    return {1,0,0,0  ,0,cos,-sin,0,   0,sin,cos,0    ,0,0,0,1};
}

Mat4 getRotationY ( float r )
{
    float cos = cosf(r);
    float sin = sinf(r);
    return {cos,0, sin,0,   0,1,0,0,  -sin,0,cos,0,   0,0,0,1};
}

Mat4 getRotationZ ( float r )
{
    float cos = cosf(r);
    float sin = sinf(r);
    return {cos,-sin,0,0,   sin,cos,0,0,   0,0,1,0,   0,0,0,1};
}

Mat4 getShearing ( float x_to_y , float x_to_z , float y_to_x , float y_to_z , float z_to_x , float z_to_y )
{
    return {1,x_to_y,x_to_z,0,   y_to_x,1,y_to_z,0,   z_to_x,z_to_y,1,0,    0,0,0,1};
}


