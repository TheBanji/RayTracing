#pragma once

#include "texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.hpp>

class ImageTexture : public Texture {
    public:
        ImageTexture(const std::string& imageName);
        ~ImageTexture();

        Color operator()(double u, double v, const Point& intersectionPoint) const;

    private:
        unsigned char* _image;
        int _width;
        int _height;
        int _comp;
};