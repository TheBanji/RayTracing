#include <iostream>
#include <ctime>

// Materials
#include "lambertian.hpp"
#include "metal.hpp"
#include "dielectric.hpp"
// Textures
#include "colorTexture.hpp"
#include "checkerTexture.hpp"
#include "imageTexture.hpp"
// Objects
#include "sphere.hpp"
#include "triangle.hpp"
// Scene
#include "scene.hpp"
// Utilities
#include "random.hpp"

int main(int argc, char * argv[]) {
    int width = 640, height = 480;
    int nbRaysPerPixel  = 100;
    int maxBouncePerRay = 10;

    double ratio = (double)width/height;
    double coeff = 2.0;

    seed_random(std::time(nullptr));
    PPM img(width, height);

    Texture * t1 = new ImageTexture("image_texture.jpg"); // new ColorTexture(Color(0.8, 0.3, 0.3));
    Texture * t2 = new ColorTexture(Color(0.8, 0.6, 0.2));
    Texture * t3 = new ColorTexture(Color(0.8, 0.8, 0.8));
    Texture * t4 = new CheckerTexture(new ColorTexture(Color(0.5, 0.2, 0.8)), new ColorTexture(Color(0.75, 0.1, 0.625)));

    Point A(-0.5,0,-3.5), B(0.5,0,-5), C(0.5,-0.5,-3.5), D(0.5,0.5,-3.5);

    Scene scene(Point(0.0, 0.0, 0.0), Point(0.0, 0.0, -2.5), Vector(coeff * ratio, 0.0, 0.0), Vector(0.0, coeff, 0.0));
    scene.addObject(new Sphere(new Lambertian(t1),   Point(-0.5, 0.0, -6.0),    1.0));
    scene.addObject(new Sphere(new Metal(t2, 0.0),   Point(1.5, 0.0, -6.0),     1.0));
    scene.addObject(new Sphere(new Metal(t3, 0.0),   Point(0.25, 0.0, -3.0),    0.1));
    scene.addObject(new Sphere(new Dielectric(1.5),  Point(-2.5, 0.0, -6.0),    1.0));
    scene.addObject(new Sphere(new Dielectric(1.5),  Point(0.0, 0.0, -4.0),     0.25));
    scene.addObject(new Sphere(new Dielectric(1.5),  Point(0.0, 0.0, -4.0),    -0.15));
    scene.addObject(new Sphere(new Dielectric(1.0),  Point(1.5, 0.5, -4.0),     0.25));
    scene.addObject(new Sphere(new Dielectric(2.0),  Point(0.75, 0.25, -4.0),   0.25));
    scene.addObject(new Sphere(new Dielectric(1.25), Point(-1.5, 0.0, -4.0),    0.25));
    scene.addObject(new Sphere(new Metal(t4, 0.1),   Point(0.0, -100.0, -4.0),  99.0));
    scene.addObject(new Triangle(new Dielectric(1.5)/*Metal(t4, 0.1)*/, A, B, C));
    scene.addObject(new Triangle(new Dielectric(1.5)/*Metal(t4, 0.1)*/, A, B, D));
    scene.addObject(new Triangle(new Dielectric(1.5)/*Metal(t4, 0.1)*/, B, C, D));
    scene.addObject(new Triangle(new Dielectric(1.5)/*Metal(t4, 0.1)*/, A, C, D));
    scene.addObject(new Sphere(new Metal(t4, 0.1),   Point(0.0, -100.0, -4.0),  99.0));

    scene.render(img, nbRaysPerPixel, maxBouncePerRay);
    img.save("img/test.ppm", false);
    
    return 0;
}