#pragma once

#include "color.hpp"
#include "ray.hpp"

class Material {
    public:
        virtual ~Material();

        virtual bool scatter(const Ray& shotRay, const Point& intersectPoint, const Vector& normalVector, Ray& scatteredRay, Color& attenuation, const Point& sphereCenter, double sphereRadius) const = 0;
};