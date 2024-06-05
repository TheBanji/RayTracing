/*
    Light-ray modelled as semi-line.
*/

#pragma once

#include "vector.hpp"

class Ray {
    public:
        Ray();
        Ray(const Point& origin, const Vector& dir);

        Point getOrigin() const;
        Vector getDir() const;

        void setDir(const Vector& dir);

        Point operator()(double t) const;
        
        friend std::ostream& operator<<(std::ostream& stream, const Ray& ray);

    private:
        Point _origin;
        Vector _dir;
};