////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "imageTexture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.hpp>

#include <cstdio>
#include <cstdlib>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ImageTexture::ImageTexture(const std::string& imageName) : _image(nullptr), _width(0), _height(0), _comp(0) {
    _image = stbi_load(imageName.c_str(), &_width, &_height, &_comp, 0);
    if(!_image) {
        fprintf(stderr, "Unable to load the image %s.\n", imageName.c_str());
        std::exit(EXIT_FAILURE);
    }
}

ImageTexture::~ImageTexture() {
    if(!_image) {
        delete _image;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Color ImageTexture::operator()(double u, double v, const Point& intersectionPoint) const {
    int i = u * _width;
    int j = (1 - v) * _height - 0.001;
    if(i < 0) {
        i = 0;
    }
    if(i > _width-1) {
        i = _width-1;
    }
    if(j < 0) {
        j = 0;
    }
    if(j > _height-1) {
        j = _height-1;
    }
    return Color((double)_image[3*i + 3*_width*j]/255.0,
                 (double)_image[3*i + 3*_width*j + 1]/255.0,
                 (double)_image[3*i + 3*_width*j + 2]/255.0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////