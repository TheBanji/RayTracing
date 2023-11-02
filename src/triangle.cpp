////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "sphere.hpp"
#include "triangle.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Triangle::Triangle(Material * material, const Point& A, const Point& B, const Point& C) : Object(material), _A(A), _B(B), _C(C), _AB(B-A), _BC(C-B), _CA(A-C) {
    _normal = (_AB ^ _CA).normalize();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Object* Triangle::clone() const {
    return new Triangle(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double Triangle::intersect(const Ray& ray) const {
    double hasIntersection = _normal.dot(ray.getDir());
    if(hasIntersection == 0.0) { // The normal and the ray are orthogonal
       return -1.0; 
    }
    double t = - _normal.dot(ray.getOrigin() - _A) / hasIntersection;
    if(t <= 0.0) {
        return -1.0;
    }
    Point intersectionPoint = ray(t); // intersectionPoint P
    Vector AP = intersectionPoint -_A;
    Vector BP = intersectionPoint -_B;
    Vector CP = intersectionPoint -_C;
    Vector u  = _AB ^ AP;
    Vector v  = _BC ^ BP;
    Vector w  = _CA ^ CP;
    double ps_uv = u.dot(v), ps_vw = v.dot(w);
    bool is_same_sign = (ps_uv > 0.0) && (ps_vw > 0.0);
    return  (is_same_sign ? t : -1.0);
}

Vector Triangle::normal(const Point& point) const {
    return _normal;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Triangle::uv_projection(const Point& point, double& u, double& v) const {
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Color Triangle::getColor(const Ray& ray, const Point& intersectionPoint, Ray& scatteredRay) const {
    Color attenuation;
    if(_material != nullptr && _material->scatter(ray, intersectionPoint, this->normal(intersectionPoint), scatteredRay, attenuation, *this)) {
        return attenuation;
    }
    return Color::Black;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::ostream& Triangle::print(std::ostream& stream) const {
    stream << "A : "      << _A      << std::endl;
    stream << "B : "      << _B      << std::endl;
    stream << "C : "      << _C      << std::endl;
    stream << "Normal : " << _normal << std::endl;
    return stream;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////