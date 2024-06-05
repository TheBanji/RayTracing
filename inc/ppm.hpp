/*
    PPM file format implementation.
*/

#pragma once

#include <string>
#include "color.hpp"

class PPM {
    public:
        PPM(const std::string& filename);
        PPM(int width, int height);
        PPM(const PPM& ppm);
        ~PPM();

        void fill(const Color& color);
        void save(const std::string& filename, bool gammaCorrection) const;

        int getWidth() const;
        int getHeight() const;

        PPM& operator=(const PPM& ppm);
        PPM& operator=(const Color& color);

        Color* operator[](int j) const;

    private:
        void allocate_copy(const Color ** img);
        
        int _width;
        int _height;
        Color ** _img;
};