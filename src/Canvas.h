#ifndef RAY_TRACER_CANVAS_H
#define RAY_TRACER_CANVAS_H

#include <memory>
#include <fstream>
#include "Color.h"

#include "Vec4.h"

class Canvas
{
public:
    Canvas ( int r , int c ) : row(r) , col(c)
    {
        mem = alloc.allocate( row * col );
    }

    void write ( const Color &color , int x , int y )
    {
        // check bounds
        if ( x < 0 || x >= col || y < 0 || y >= row )
        {
            fprintf( stderr , "ignored write\n") ;
            return;
        }
        Color copy = color;
        alloc.construct( mem + x+y*row , copy );
    }

    void save ( const std::string& filename )
    {
        std::ofstream file;
        file.open(filename);

        // write width then height to PPM header
        file << "P3\n" << col << " " << row << "\n255\n" ;

        for ( int i = 0 ; i < col * row ; ++i )
        {
            const auto &color = mem[i];
            file << int (color.r * 255)  << " " << int (color.g * 255) <<
            " " << int (color.b * 255) << '\n' ;
        }

        file.close();
    }

private:
    int row;
    int col;
    Color *mem;
    std::allocator<Color> alloc;
};


#endif //RAY_TRACER_CANVAS_H
