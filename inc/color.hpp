#pragma once

#include <iostream>

#include "vector.hpp"

class Color {
    public:
        Color();
        Color(double r, double g, double b);
        Color(const Vector& vec);

        double getR() const;
        double getG() const;
        double getB() const;

        void setColor(double r, double g, double b);

        friend std::ostream& operator<<(std::ostream& stream, const Color& color);

        static Color Red;
        static Color Green;
        static Color Blue;
        static Color Purple;
        static Color Yellow;
        static Color White;
        static Color Black;

        Color operator*(const Color& color);

        Color& operator+=(const Color& color);
        Color& operator/=(double n);

    private:
        double _r;
        double _g;
        double _b;
};