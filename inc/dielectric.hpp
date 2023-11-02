#pragma once

#include "material.hpp"
#include "sphere.hpp"

class Dielectric : public Material {
    public:
        Dielectric(double n);

        virtual bool scatter(const Ray& shotRay, const Point& intersectionPoint, const Vector& normalVector, Ray& scatteredRay, Color& attenuation, const Object& object) const;

    private:
        double _n;

        static double schlick(double cosine, double n);
};