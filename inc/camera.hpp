/*
    Camera from which the scene should be rendered.
*/

#pragma once

#include "vector.hpp"

class Camera {
    public:
        Camera(const Point& origin, const Point& screenCenter, const Vector& screenWidth, const Vector& screenHeight);
        virtual ~Camera();
        
    protected:
        Point _origin;
        Point _screenCenter;
        Vector _screenWidth;
        Vector _screenHeight;
        Point _bottom_left_corner;
};