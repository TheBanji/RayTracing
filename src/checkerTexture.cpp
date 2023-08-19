////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include "checkerTexture.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CheckerTexture::CheckerTexture(Texture * texture1, Texture * texture2, double freq) : _texture1(texture1), _texture2(texture2), _freq(freq) {}

CheckerTexture::~CheckerTexture() {
    if(_texture1 != nullptr) {
        delete _texture1;
    }

    if(_texture2 != nullptr) {
        delete _texture2;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Color CheckerTexture::operator()(double u, double v, const Point& intersectionPoint) const {
    double sine = std::sin(_freq * intersectionPoint.getX()) *
                  std::sin(_freq * intersectionPoint.getY()) *
                  std::sin(_freq * intersectionPoint.getZ());
    if(sine >= 0.0) {
        return (*_texture1)(u, v, intersectionPoint);
    } else {
        return (*_texture2)(u, v, intersectionPoint);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////