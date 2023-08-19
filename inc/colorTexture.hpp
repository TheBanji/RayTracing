#pragma once

#include "texture.hpp"

class ColorTexture : public Texture {
    public:
        ColorTexture(const Color& color);

        Color operator()(double u, double v, const Point& intersectionPoint) const;

    private:
        Color _color;
};