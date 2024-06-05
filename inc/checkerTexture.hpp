/*
    Texture modelling a checker-board-like
    pattern of texture that can be applied
    onto a material.
*/

#pragma once

#include "colorTexture.hpp"

class CheckerTexture : public Texture {
    public:
        CheckerTexture(Texture * texture1, Texture * texture2, double freq = 10.0);
        ~CheckerTexture();

        Color operator()(double u, double v, const Point& intersectionPoint) const;

    private:
        Texture* _texture1;
        Texture* _texture2;
        double _freq;
};