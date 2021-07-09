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

int main ()
{
    World cornell_box ;

    Plane floor (nullptr , Mat4::IDENTITY() ) ;
    floor.material = new PatternMaterial( new CheckerPattern(  floor , Mat4::IDENTITY().scale(0.5f,0.5f,0.5f).rotate_y(M_PI/5) , Color(1,0,0) , Color(0,0,1))  );

    Plane back_wall (nullptr , Mat4::IDENTITY().rotate_x(-M_PI/2).translate(0,0,100 ) ) ;
    back_wall.material = new PatternMaterial ( new CheckerPattern( back_wall , Mat4::IDENTITY().scale(0.7f,0.7f,0.7f)) );
    back_wall.material->specular = 0.4f;
    back_wall.material->shininess = 300 ;

    Light light( Color(1,1,1) , Vec4::getPoint(0,2.5f,1 ));

    // objects

    Sphere glass_ball ( PlainMaterial::getGlassMaterial() , Mat4::IDENTITY().scale(1,1,1).translate(-1,1,0)  );
//    glass_ball.material->albedo = Color(0.2f ,0.2f,0.2f);
    glass_ball.material->reflectance = 1 ;
    glass_ball.material->diffuse = 0.4f;
    glass_ball.material->specular = 1;
    glass_ball.material->shininess = 300 ;

    Sphere air_ball (nullptr, Mat4::IDENTITY().scale(0.3f,0.3f,0.3f).translate(-1 ,1 ,0 ) );
    air_ball.material = new PatternMaterial ( new CheckerPattern( air_ball , Mat4::IDENTITY().scale(0.1f,0.1f,0.1f) , Color(0,1,1) , Color(1,0,1) )  );
    air_ball.material->ambient = 1;

    Cube mirror_ball (  new PlainMaterial( Color(0.1f,0.1f,0.1f)) ,  Mat4::IDENTITY().scale(0.5f,0.5f,0.5f).rotate_y(M_PI/4).translate(1,0.5f ,-0.2f)  );
    mirror_ball.material->reflectance = 1;
//    mirror_ball.material->refractive_index = 1.5f;
//    mirror_ball.material->transparency = 1;

    Triangle testTri ( new PlainMaterial(Color(1,0,1)) , Vec4::getPoint(-1,2,3) , Vec4::getPoint(0.5f,2.5f,3.5f)  , Vec4::getPoint(1,1.5f,2.5f)   );

    cornell_box.add(light);
    cornell_box.add( floor );
    cornell_box.add( back_wall );

//    cornell_box.add( glass_ball );
//    cornell_box.add ( mirror_ball );
//    cornell_box.add ( air_ball );

    cornell_box.add(testTri);

    Point from = Vec4::getPoint(0,1,-4);
    Point to = Vec4::getPoint(0,1,-1);
    Vector up = Vec4::getVector(0,1,0);

    // render the frame
    auto begin = std::chrono::steady_clock::now();

    Camera cam ( 1920/3 , 1080/3 , M_PI/2, Mat4::view(from , to , up ) );
    auto canvas = render( cam , cornell_box );

    auto end = std::chrono::steady_clock::now();

    canvas.save("test_image.ppm");

    std::cout << "Render time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;

    return 0;
}