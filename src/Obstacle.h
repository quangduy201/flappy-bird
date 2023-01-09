#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Utils.h"

class Obstacle
{
private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Point* position;
    SDL_Rect* bounding_box;

public:
    Obstacle(SDL_Renderer* renderer);
    virtual ~Obstacle();

    void update();
    void render();
    SDL_Rect* getBoundingBox() const { return bounding_box; }

};

#endif // !OBSTACLE_H
