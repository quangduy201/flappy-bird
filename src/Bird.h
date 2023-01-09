#ifndef BIRD_H
#define BIRD_H

#include "Utils.h"
#include "Obstacle.h"

class Bird
{
private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Point* position;
    SDL_Point* velocity;
    SDL_Rect* bounding_box;
public:
    Bird(SDL_Renderer* renderer);
    virtual ~Bird();

    void flap();
    void update();
    void render();
    bool isColliding(Obstacle* obstacle);

    inline SDL_Point* getPosition() const { return position; }
    void setPosition(SDL_Point* position) { this->position = position; }
    inline SDL_Point* getVelocity() const { return velocity; }
    void setVelocity(SDL_Point* velocity) { this->velocity = velocity; }
};

#endif // !BIRD_H
