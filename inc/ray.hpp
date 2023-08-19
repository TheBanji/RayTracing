#pragma once

#include "vector.hpp"

class Ray {
    public:
        Ray();
        Ray(const Point& origin, const Vector& dir);

        Point getOrigin() const;
        Vector getDir() const;

        Point operator()(double t) const;
        
        friend std::ostream& operator<<(std::ostream& stream, const Ray& ray);

    private:
        Point _origin;
        Vector _dir;
};