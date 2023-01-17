#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "../util/Utils.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Obstacle
{
private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect frame;
    Uint32 last_update_time;
    SDL_FPoint* position;
    float velocity;
    SDL_FRect* bounding_box;
    bool is_upper;

public:
    Obstacle(SDL_Renderer* renderer, bool is_upper, int gap_pos, float velocity);
    virtual ~Obstacle();

    void update(Uint32 current_time);
    void render();
    inline SDL_FPoint* getPosition() const { return position; }
    inline SDL_FRect* getBoundingBox() const { return bounding_box; }
    static int constexpr GAP = 150;
};

#endif // !OBSTACLE_H
