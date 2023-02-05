#ifndef CAMERA_H
#define CAMERA_H

#include "../util/Vector2.h"

class Camera
{
public:
    Vector2 position;
    float width, height;

    Camera() {}
    Camera(float width, float height) : width(width), height(height) {}
    void follow(Vector2 target)
    {
        position = target;
    }
};

#endif // !CAMERA_H
