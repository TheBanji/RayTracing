#pragma once

#include "material.hpp"
#include "texture.hpp"
#include "sphere.hpp"

class Lambertian : public Material {
    public:
        Lambertian(Texture * texture);//const Color& albedo);

        bool scatter(const Ray& shotRay, const Point& intersectionPoint, const Vector& normalVector, Ray& scatteredRay, Color& attenuation, const Object& object) const;
    
    private:
        Texture* _texture;//Color _albedo;
};