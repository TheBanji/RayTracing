////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include "random.hpp"
#include "sphere.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Sphere::Sphere(Material * material, const Point& center, double radius) : Object(material), _center(center), _radius(radius) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Object* Sphere::clone() const {
    return new Sphere(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double Sphere::intersect(const Ray& ray) const {
    Vector OC    = ray.getOrigin() - _center;
    double a     = 1;
    double b     = 2 * OC.dot(ray.getDir());
    double c     = OC.norm_sq() - _radius*_radius;
    double delta = b*b - 4*a*c;
    return (delta >= 0 ? (-b-std::sqrt(delta))/(2*a) : -1.0);
}

Vector Sphere::normal(const Point& point) const {
    return (point - _center).normalize();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Color Sphere::getColor(const Ray& ray, const Point& intersectionPoint, Ray& scatteredRay) const {
    Color attenuation;
    if(_material != nullptr && _material->scatter(ray, intersectionPoint, this->normal(intersectionPoint), scatteredRay, attenuation, *this)) {
        return attenuation;
    }
    return Color::Black;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Point Sphere::getCenter() const {
    return _center;
}

double Sphere::getRadius() const {
    return _radius;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Point Sphere::random_point(double radius) {
    double theta = 2 * M_PI * uniform_random();
    double phi   = 2 * M_PI * uniform_random();
    return radius * Point(std::cos(phi)*std::cos(theta), std::cos(phi)*std::sin(theta), std::sin(phi));
}

void Sphere::uv_projection(const Point& point, double& u, double& v) {
    double phi   = std::atan2(point.getZ(), point.getX());
    double theta = std::asin(point.getY());
    u            = 1 - (phi+M_PI)/(2*M_PI);
    v            = (theta+M_PI/2)/M_PI;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream& stream, const Sphere& sphere) {
    stream << "Center : " << sphere._center << std::endl;
    stream << "Radius : " << sphere._radius << std::endl;
    return stream;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////