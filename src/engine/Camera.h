#ifndef CAMERA_H
#define CAMERA_H

#include "../util/Vector2.h"

class Camera
{
public:
    Vector2 position;
    int w, h;

    Camera() {}
    Camera(int width, int height) : w(width), h(height) {}
    void setPosition(Vector2 pos) { position = pos; }
};

#endif // !CAMERA_H
