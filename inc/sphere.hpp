#pragma once

#include "object.hpp"

class Sphere : public Object {
    public:
        Sphere(Material * material, const Point& center, double radius = 1.0);
        
        Object* clone() const;

        double intersect(const Ray& ray) const;
        Vector normal(const Point& point) const;

        Color getColor(const Ray& ray, const Point& intersectionPoint, Ray& scatteredRay) const;

        Point getCenter() const;
        double getRadius() const;

        friend std::ostream& operator<<(std::ostream& stream, const Sphere& sphere);

        static Point random_point(double radius = 1.0);
        static void uv_projection(const Point& point, double& u, double& v);
        
    private:
        Point _center;
        double _radius;
};