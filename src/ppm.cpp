////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "ppm.hpp"
#include "utils.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PPM::PPM(const std::string& filename) {
    int r, g, b;
    char header[3];
    int intensity;
    std::FILE * file = std::fopen(filename.c_str(), "r");
    if(file == NULL) {
        std::fprintf(stderr, "Unable to open %s\n", filename.c_str());
        std::exit(EXIT_FAILURE);
    }
    if(std::fscanf(file, "%s\n%d\n%d %d", header, &_width, &_height, &intensity)) {
        std::fprintf(stderr, "Unable to read from %s\n", filename.c_str());
        std::exit(EXIT_FAILURE);
    }
    _img = new Color*[_height];
    for(int j(0); j < _height; j++) {
        _img[j] = new Color[_width];
        for(int i(0); i < _width; i++) {
            if(std::fscanf(file, "%d %d %d", &r, &g, &b) != 3) {
                std::fprintf(stderr, "Unable to read from %s\n", filename.c_str());
                std::exit(EXIT_FAILURE);
            }
            _img[j][i].setColor(r, g, b);
        }
    }
    std::fclose(file);
}

PPM::PPM(int width, int height) : _width(width), _height(height) {
    _img = new Color*[_height];
    for(int j(0); j < _height; j++)
        _img[j] = new Color[_width];
}

PPM::PPM(const PPM& ppm) : _width(ppm._width), _height(ppm._height) {
    allocate_copy((const Color**)ppm._img);
}

PPM::~PPM() {
    for(int j(0); j < _height; j++)
        delete [] _img[j];
    delete [] _img;
}

void PPM::fill(const Color& color) {
    *this = color;
}

void PPM::save(const std::string& filename, bool gammaCorrection) const {
    if(_width <= 0 || _height <= 0) {
        std::fprintf(stderr, "Image has a size of zero. (width = %d, height = %d)\n", _width, _height);
        std::exit(EXIT_FAILURE);
    }
    std::FILE * file = std::fopen(filename.c_str(), "w");
    if(file == NULL) {
        std::fprintf(stderr, "Unable to open %s\n", filename.c_str());
        std::exit(EXIT_FAILURE);
    }

    std::fprintf(file, "P3\n%d %d\n255\n", _width, _height);

    int i, j;
    /*// Recovers the max intensity
    double maxIntensity = MAX_DOUBLE;
    for(j = 0; j < _height; j++) {
        for(i = 0; i < _width; i++) {
            Color& color = _img[j][i];
            if(color.getR() > maxIntensity) {
                maxIntensity  = color.getR();
            } else if(color.getG() > maxIntensity) {
                maxIntensity = color.getG();
            } else if(color.getB() > maxIntensity) {
                maxIntensity  = color.getB();
            }
        }
    }*/

    for(j = 0; j < _height; j++) {
        for(i = 0; i < _width; i++) {
            if(gammaCorrection) {
                std::fprintf(file, "%d %d %d\n", (int)(255*std::sqrt(_img[j][i].getR()/*/maxIntensity*/)),
                                                 (int)(255*std::sqrt(_img[j][i].getG()/*/maxIntensity*/)),
                                                 (int)(255*std::sqrt(_img[j][i].getB()/*/maxIntensity*/))
                );
            } else {
                std::fprintf(file, "%d %d %d\n", (int)(255*_img[j][i].getR()/*/maxIntensity*/),
                                                 (int)(255*_img[j][i].getG()/*/maxIntensity*/),
                                                 (int)(255*_img[j][i].getB()/*/maxIntensity*/)
                );
            }
        }
    }
    std::fclose(file);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int PPM::getWidth() const {
    return _width;
}

int PPM::getHeight() const {
    return _height;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PPM& PPM::operator=(const PPM& ppm) {
    if(this != &ppm) {
        delete [] _img;
        _width  = ppm._width;
        _height = ppm._height;
        allocate_copy((const Color**)ppm._img);
    }
    return *this;
}

PPM& PPM::operator=(const Color& color) {
    for(int j(0); j < _height; j++) {
        for(int i(0); i < _width; i++) {
            _img[j][i] = color;
        }
    }
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Color* PPM::operator[](int j) const {
    return _img[j];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PPM::allocate_copy(const Color ** img) {
    _img = new Color*[_height];
    for(int j(0); j < _height; j++) {
        _img[j] = new Color[_width];
        for(int i(0); i < _width; i++) {
            _img[j][i] = img[j][i];
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////