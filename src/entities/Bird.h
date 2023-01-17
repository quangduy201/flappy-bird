#ifndef BIRD_H
#define BIRD_H

#include "../util/Utils.h"
#include "../entities/Obstacle.h"
#include "../entities/Ground.h"
#include <vector>

class Bird
{
private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    std::vector<SDL_Rect> frames;
    int current_frame;
    double angle;
    float animation_timer;
    SDL_FPoint* position;
    SDL_FPoint* velocity;
    SDL_FRect* bounding_box;

public:
    Bird(SDL_Renderer* renderer);
    virtual ~Bird();

    void flap();
    void update(float current_time);
    void render();
    bool isColliding(Obstacle* obstacle);
    bool isColliding(Ground* ground);

    inline SDL_FPoint* getPosition() const { return position; }
    void setPosition(SDL_FPoint* position) { this->position = position; }
    inline SDL_FPoint* getVelocity() const { return velocity; }
    void setVelocity(SDL_FPoint* velocity) { this->velocity = velocity; }
};

#endif // !BIRD_H
