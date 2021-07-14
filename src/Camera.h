#ifndef RAY_TRACER_CAMERA_H
#define RAY_TRACER_CAMERA_H

#include "Mat4.h"
#include "Ray.h"

class Camera
{
    int h_size , v_size ;
    float fov ; // horizontal size, vertical size , field of inverse_view
    float half_width , half_height , pixel_size ; // used to worldToObject the rays
    Mat4 inverse_view; // default matrix is the identity matrix

public:

    [[nodiscard]] int getHSize() const
    {
        return h_size;
    }

    [[nodiscard]] int getVSize() const
    {
        return v_size;
    }

    Camera ( int h , int v , float field , Mat4 trans = Mat4::IDENTITY() ) : h_size(h) , v_size(v) , fov(field) , inverse_view(trans.invert())
    {
        float half_view = tanf( fov/2 );
        float aspect_ratio = h_size / ( float ) v_size ;

        if ( aspect_ratio >= 1 ) // h_size > v_size
        {
            half_width = half_view;
            half_height = half_view / aspect_ratio ;
        }
        else
        {
            half_width = half_view * aspect_ratio ;
            half_height = half_view;
        }

        pixel_size = (half_width * 2) / h_size ;
    }


    [[nodiscard]] Ray getRayForPixel( float px , float py ) const
    {
        // first calculate the offsets
        float offset_x = (px + 0.5f) * pixel_size; // 0.5 to put it at the center of the pixel
        float offset_y = (py + 0.5f) * pixel_size;

        float world_x = half_width - offset_x;
        float world_y = half_height - offset_y;

        Point3f pixel = inverse_view * Point3f(world_x, world_y, -1); // TODO: invert_copy every time no no!! fine for now
        Point3f origin = inverse_view * Point3f();

        Vec3f direction = pixel - origin;
        return Ray( origin , direction );
    }
};


#endif //RAY_TRACER_CAMERA_H
