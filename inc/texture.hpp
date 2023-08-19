#pragma once

#include "color.hpp"

class Texture {
    public:
        virtual ~Texture();

        virtual Color operator()(double u, double v, const Point& intersectionPoint) const = 0;
};