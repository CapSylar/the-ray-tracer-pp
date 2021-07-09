#include <chrono>

#include "Ray.h"
#include "Sphere.h"
#include "Plane.h"
#include "Material.h"
#include "World.h"
#include "Cube.h"
#include "PatternMaterial.h"
#include "PlainMaterial.h"
#include "CheckerPattern.h"
#include "Triangle.h"
#include "Loader.h"

int main ()
{
    World world ;
    load_obj( world , "/home/robin/CLionProjects/the-ray-tracer-pp/models/teapot.obj");

    Plane floor (nullptr , Mat4::IDENTITY() ) ;
    floor.material = new PatternMaterial( new CheckerPattern(  floor , Mat4::IDENTITY().scale(0.5f,0.5f,0.5f).rotate_y(M_PI/5) , Color(1,0,0) , Color(0,0,1))  );

    Light light( Color(1,1,1) , Vec4::getPoint(0,30,-4 ));

    world.add(light);
    world.add(floor );

    Point from = Vec4::getPoint(10,5,-2);
    Point to = Vec4::getPoint(0,1,0 );
    Vector up = Vec4::getVector(0,1,0);

    // render the frame
    auto begin = std::chrono::steady_clock::now();

    Camera cam ( 1920 , 1080 , M_PI/3, Mat4::view(from , to , up ) );
    auto canvas = render(cam , world );

    auto end = std::chrono::steady_clock::now();

    canvas.save("test_image.ppm");

    std::cout << "Render time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;

    return 0;
}