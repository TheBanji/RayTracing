/*
    3-dimensional objects base class.
*/

#pragma once

#include "ray.hpp"
#include "color.hpp"
#include "material.hpp"

class Object {
    public:
        Object(Material * material);
        virtual ~Object();

        virtual Object * clone() const = 0;

        virtual double intersect(const Ray& ray) const = 0;
        virtual Vector normal(const Point& point) const = 0;

        virtual void uv_projection(const Point& point, double& u, double& v) const = 0;

        virtual Color getColor(const Ray& ray, const Point& intersectionPoint, Ray& scatteredRay) const = 0;

        friend std::ostream& operator<<(std::ostream& stream, const Object& object);

    protected:
        virtual std::ostream& print(std::ostream& stream) const = 0;

        Material * _material;
};