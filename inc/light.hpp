#pragma once

#include "vector.hpp"
#include "color.hpp"

class Light {
    public:
        Light(const Point& origin, const Color& color);

    private:
        Point _origin;
        Color _color;

};