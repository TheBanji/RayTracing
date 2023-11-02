#pragma once

#include "material.hpp"
#include "texture.hpp"
#include "sphere.hpp"

class Metal : public Material {
    public:
        Metal(Texture * texture, double fuzz); //const Color& albedo, double fuzz);

        bool scatter(const Ray& shotRay, const Point& intersectionPoint, const Vector& normalVector, Ray& scatteredRay, Color& attenuation, const Object& object) const;
    
    private:
        Texture* _texture;//Color _albedo;
        double _fuzz;
};