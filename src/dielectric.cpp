////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include "dielectric.hpp"
#include "random.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Dielectric::Dielectric(double n) : _n(n) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Dielectric::scatter(const Ray& shotRay, const Point& intersectionPoint, const Vector& normalVector, Ray& scatteredRay, Color& attenuation, const Object& Object) const {
    attenuation            = Color::White;
    Vector shotRayDir      = shotRay.getDir();
    Vector reflectedVector = shotRayDir.reflect(normalVector);
    Vector outwardNormal;
    Vector refractedVector;
    double ni, cosine, reflect_prob;
    double dotProd = shotRayDir.dot(normalVector);
    if(dotProd > 0.0) {
        outwardNormal = -1 * normalVector;
        ni            = _n;
        cosine        = _n * dotProd / shotRayDir.norm();
    } else {
        outwardNormal = normalVector;
        ni            = 1 / _n;
        cosine        = -dotProd / shotRayDir.norm();
    }

    if(shotRayDir.refract(outwardNormal, ni, refractedVector)) {
        reflect_prob = Dielectric::schlick(cosine, _n);
    } else {
        reflect_prob = 1.0;
    }

    if(uniform_random() < reflect_prob) {
        scatteredRay = Ray(intersectionPoint, reflectedVector);
    } else {
        scatteredRay = Ray(intersectionPoint, refractedVector);
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double Dielectric::schlick(double cosine, double n) {
    double r0 = (1-n) / (1+n);
    r0 *= r0;
    return r0 + (1-r0) * std::pow(1 - cosine, 5);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////