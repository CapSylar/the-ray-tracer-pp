
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

#define NDEBUG

int main ()
{
    World world ;
   load_obj( world , "/home/robin/CLionProjects/the-ray-tracer-pp/models/teapot-lowpoly.obj");

    Plane floor (nullptr , Mat4::IDENTITY() ) ;
    floor.material = new PatternMaterial( new CheckerPattern(  floor , Mat4::IDENTITY().scale(0.5f,0.5f,0.5f).rotate_y(M_PI/5) , Color3f(1,0,0) , Color3f(0,0,1))  );

    Light light( Color3f(1,1,1) , Point3f(0,30,-4 ));

    world.add(light);
    world.add(floor );

    Point3f from = Point3f(5,4,-3);
    Point3f to = Point3f(-1.7f,1,0 );
    Vec3f up = Vec3f(0,1,0);

    // render the frame
    auto begin = std::chrono::steady_clock::now();

    Camera cam ( 1920/3, 1080/3 , M_PI/2, Mat4::view(from , to , up ) );
    auto canvas = render(cam , world );

    auto end = std::chrono::steady_clock::now();

    canvas.save("test_image.ppm");

    std::cout << "Render time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;

    return 0;
}