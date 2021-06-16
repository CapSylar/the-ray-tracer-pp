#ifndef RAY_TRACER_TRANSFORMATION_H
#define RAY_TRACER_TRANSFORMATION_H

#include "Mat4.h"

Mat4 getTranslation( float x , float y , float z );
Mat4 getScaling( float x , float y , float z );
Mat4 getRotationX ( float r );
Mat4 getRotationY ( float r );
Mat4 getRotationZ ( float r );
Mat4 getShearing ( float x_to_y , float x_to_z , float y_to_x , float y_to_z , float z_to_x , float z_to_y );


#endif //RAY_TRACER_TRANSFORMATION_H
