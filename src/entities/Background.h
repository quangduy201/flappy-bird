#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "../util/Utils.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Background
{
private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect frame;
    SDL_FPoint* position;

public:
    Background(SDL_Renderer* renderer);
    virtual ~Background();

    void update(Uint32 current_time);
    void render();
    inline SDL_FPoint* getPosition() const { return position; }
};

#endif // !BACKGROUND_H
