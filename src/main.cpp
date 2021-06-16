#include <iostream>
#include "Canvas.h"

int main ()
{
    Canvas myCanvas(100,100);

    Color x = Vec4::getColor(0.8,0.5,0.5);

    for ( int i = 0 ; i < 100 ; ++i )
    {
        for ( int j = 0 ; j < 100 ; ++j )
        {
            myCanvas.write(x, i , j );
        }
    }

    myCanvas.save("test_image.ppm");

    return 0;
}