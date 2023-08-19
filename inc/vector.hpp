#pragma once

#include <iostream>

#define Point Vector

class Vector {
    public:
        Vector();
        Vector(double x, double y, double z);
    
        double norm() const;
        double norm_sq() const; 

        Vector& normalize();

        double distance(const Point& point) const;
        double dot(const Vector& vec) const;

        double getX() const;
        double getY() const;
        double getZ() const;

        Vector operator+(const Vector& vec) const;
        Vector operator-(const Vector& vec) const;
        friend Vector operator-(const Vector& vec);
        Vector operator^(const Vector& vec) const;
        Vector operator*(double a) const;
        friend Vector operator*(double a, const Vector& vec);

        Vector reflect(const Vector& normalVec) const;
        bool refract(const Vector& normalVec, double n, Vector& refractedVec) const;

        Vector& operator+=(const Vector& vec);
        Vector& operator-=(const Vector& vec);
        Vector& operator*=(double a);

        friend std::ostream& operator<<(std::ostream& stream, const Vector& vec);
        friend std::istream& operator>>(std::istream& stream, Vector& vec);

    private:
        double _x;
        double _y;
        double _z;
};