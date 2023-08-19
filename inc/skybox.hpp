#pragma once

#include "color.hpp"

class SkyBox {
    public:
        SkyBox(const Color& color1 = Color::White, const Color& color2 = Color(0.4980, 0.6938, 1.000));

        Color operator()(double t) const;

    private:
        Color _color1;
        Color _color2;
};