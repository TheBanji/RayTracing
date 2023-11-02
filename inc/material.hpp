#pragma once

#include "color.hpp"
#include "ray.hpp"

class Object;

class Material {
    public:
        virtual ~Material();

        virtual bool scatter(const Ray& shotRay, const Point& intersectPoint, const Vector& normalVector, Ray& scatteredRay, Color& attenuation, const Object& object) const = 0;
};