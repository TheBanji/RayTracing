/*
    Scene class performing the rendering of
    3-dimensional objects using ray-tracing.
    Contains all the objects and some
    information such as the scene geometry.
*/

#pragma once

#include <vector>
#include "ppm.hpp"
#include "object.hpp"
#include "light.hpp"
#include "skybox.hpp"
#include "camera.hpp"

void * render_chunk(void * args);

class Scene : public Camera {
    public:
        Scene(const Point& origin, const Point& screenCenter, const Vector& screenWidth, const Vector& screenHeight);
        Scene(const Scene& scene);
        ~Scene();

        void render(PPM& image, int nbSamplesAliasing, int recursionLimit) const;
        friend void * render_chunk(void * args);
        Color cast_ray(const Ray& shotRay, int recursionLimit) const;

        void addObject(Object * object);
        void popObject();
        void deleteObjects();

        void addLight(Light * light);
        void popLight();
        void deleteLights();

    private:
        SkyBox _skybox;
        std::vector<Object*> _objects;
        std::vector<Light*> _lights;
};