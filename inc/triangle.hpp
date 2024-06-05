/*
    Triangle model in a 3-dimensional space.
*/

#pragma once

#include "object.hpp"

class Triangle : public Object {
    public:
        Triangle(Material * material, const Point& A, const Point& B, const Point& C);
        
        Object* clone() const;

        double intersect(const Ray& ray) const;
        Vector normal(const Point& point) const;

        void uv_projection(const Point& point, double& u, double& v) const; // Needs to be implemented.

        Color getColor(const Ray& ray, const Point& intersectionPoint, Ray& scatteredRay) const;
        
    private:
        std::ostream& print(std::ostream& stream) const;

        Point _A;
        Point _B;
        Point _C;
        Vector _AB;
        Vector _BC;
        Vector _CA;
        Vector _normal;
};