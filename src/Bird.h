#ifndef BIRD_H
#define BIRD_H

#include "Utils.h"
#include "Obstacle.h"
#include <vector>

class Bird
{
private:
    SDL_Renderer* renderer;
    std::vector<SDL_Texture*> textures;
    int current_frame;
    Uint32 animation_timer;
    SDL_FPoint* position;
    SDL_FPoint* velocity;
    SDL_FRect* bounding_box;

public:
    Bird(SDL_Renderer* renderer);
    virtual ~Bird();

    void flap();
    void update(Uint32 current_time);
    void render();
    bool isColliding(Obstacle* obstacle);

    inline SDL_FPoint* getPosition() const { return position; }
    void setPosition(SDL_FPoint* position) { this->position = position; }
    inline SDL_FPoint* getVelocity() const { return velocity; }
    void setVelocity(SDL_FPoint* velocity) { this->velocity = velocity; }
};

#endif // !BIRD_H
