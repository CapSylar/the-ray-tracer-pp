#include <chrono>
#include "Ray.h"
#include "Plane.h"
#include "Material.h"
#include "World.h"
#include "Loader.h"
#include "PlainMaterial.h"
#include "PatternMaterial.h"
#include "CheckerPattern.h"

int main ()
{
    auto begin = std::chrono::steady_clock::now();

    World world ;

    auto modelMaterial = std::make_shared<PlainMaterial>( Color3f(0.1f,0.1f,0.1f) );
    modelMaterial->refractive_index = 1.5f;
    modelMaterial->reflectance = 0.9f;
    modelMaterial->transparency = 0.9f;
    modelMaterial->ambient = 0.1f;
    modelMaterial->shininess = 300;

    load_obj(world, Mat4() ,  modelMaterial ,
             "/home/robin/CLionProjects/the-ray-tracer-pp/models/stanford-dragon.obj");

    auto floor = std::make_unique<Plane>(nullptr , Mat4() );
    floor->setMaterial( std::make_shared<PatternMaterial>( new CheckerPattern( floor->objectToWorld , Mat4().scale(2,2,2).rotate_y(M_PI/5) , Color3f(0.6f,0.6f,0) , Color3f(0 ,0.6f,0.6f))) );
    floor->material->reflectance = 0.5f;

    auto sky = std::make_unique<Plane>(nullptr , Mat4().rotate_x(M_PI).translate(0,15,0) );
    sky->setMaterial( std::make_shared<PlainMaterial>( Color3f(0.4f,0.4f,1) ) );

    auto sphere = std::make_unique<Sphere>( new PlainMaterial( Color3f(0,0.2f,0) ) , Mat4().scale(2,2,2).translate(0,2,3) );
    sphere->getMaterial()->reflectance = 0.9f;
    sphere->getMaterial()->refractive_index = 1.5f;
    sphere->getMaterial()->transparency= 0.9f;


    auto light = std::make_unique<Light>( Color3f(1,1,1) , Point3f(-6,10,-4 ));

    world.add(std::move(light));
    world.add(std::move(floor));
//    world.add( std::move(sphere));
    world.add( std::move(sky)) ;

    Point3f from = Point3f(-1,3,-4.5f);
    Point3f to = Point3f(0,1.5f,0 );
    Vec3f up = Vec3f(0,1,0);

    auto end = std::chrono::steady_clock::now();

    std::cout << "World pre-processing time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;

    // render the frame
    begin = std::chrono::steady_clock::now();

    Camera cam ( 1920/2 , 1080/2 ,M_PI/2 , Mat4::view(from , to , up));
    auto canvas = render(cam , world );

    end = std::chrono::steady_clock::now();

    canvas.save("test_image.ppm");

    std::cout << "Render time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;

    return 0;
}