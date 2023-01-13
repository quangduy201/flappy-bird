#ifndef GROUND_H
#define GROUND_H

#include "../util/Utils.h"

class Ground
{
private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect frame;
    Uint32 last_update_time;
    SDL_FPoint* position;
    float velocity;
    SDL_FRect* bounding_box;

public:
    Ground(SDL_Renderer* renderer, float velocity);
    virtual ~Ground();

    void update(Uint32 current_time);
    void render();
    inline SDL_FPoint* getPosition() const { return position; }
    inline SDL_FRect* getBoundingBox() const { return bounding_box; }
};

#endif // !GROUND_H
