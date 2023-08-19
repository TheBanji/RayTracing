////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include "vector.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Vector::Vector() : _x(0.0), _y(0.0), _z(0.0) {}

Vector::Vector(double x, double y, double z) : _x(x), _y(y), _z(z) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double Vector::norm() const {
    return std::sqrt(norm_sq());
}


double Vector::norm_sq() const {
    return this->dot(*this);
}


Vector& Vector::normalize() {
    double n = norm();
    return *this *= (n > 0.0 ? 1.0/n : 0.0);
}


double Vector::distance(const Point& point) const {
    return Vector(*this - point).norm();
}


double Vector::dot(const Vector& vec) const {
    return _x*vec._x + _y*vec._y + _z*vec._z;
}

Vector Vector::reflect(const Vector& normalVec) const {
    return *this - 2*Vector::dot(normalVec)*normalVec;
}

bool Vector::refract(const Vector& normalVec, double n, Vector& refractedVec) const {
    double norm_vec     = Vector::norm();
    Vector vec          = (norm_vec > 0.0 ? 1.0/norm_vec : 0.0) * (*this);
    double prod         = Vector::dot(normalVec);
    double discriminant = 1.0 - n*n*(1 - prod*prod);
    if(discriminant > 0.0) {
        refractedVec = n*(vec - prod*normalVec) - std::sqrt(discriminant)*normalVec;
        return true;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Vector Vector::operator+(const Vector& vec) const {
    return Vector(_x + vec._x,
                  _y + vec._y,
                  _z + vec._z);
}


Vector Vector::operator-(const Vector& vec) const {
    return Vector(_x - vec._x,
                  _y - vec._y,
                  _z - vec._z);
}


Vector Vector::operator^(const Vector& vec) const {
    return Vector(_y * vec._z    -    vec._y * _z, 
                  _z * vec._x    -    vec._z * _x,
                  _x * vec._y    -    vec._x * _y);
}


Vector Vector::operator*(double a) const {
    return Vector(_x*a, _y*a, _z*a);
}


Vector operator*(double a, const Vector& vec) {
    return vec * a;
}


Vector& Vector::operator+=(const Vector& vec) {
    //return *this = *this + vec;
    _x += vec._x;
    _y += vec._y;
    _z += vec._z;
    return *this;
}


Vector& Vector::operator-=(const Vector& vec) {
    //return *this = *this - vec;
    _x -= vec._x;
    _y -= vec._y;
    _z -= vec._z;
    return *this;
}


Vector& Vector::operator*=(double a) {
    //return *this = *this * a;
    _x *= a;
    _y *= a;
    _z *= a;
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double Vector::getX() const {
    return _x;
}

double Vector::getY() const {
    return _y;
}

double Vector::getZ() const {
    return _z;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream& stream, const Vector& vec) {
    return stream << "(" << vec._x << ", " << vec._y << ", " << vec._z << ")"; 
}

std::istream& operator>>(std::istream& stream, Vector& vec) {
    return stream >> vec._x >> vec._y >> vec._z;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////