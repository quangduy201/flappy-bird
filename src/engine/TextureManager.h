#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class TextureManager
{
public:
    static SDL_Texture *LoadTexture(const std::string path);
    static void Draw(SDL_Texture *texture, SDL_Rect src_rect, SDL_Rect dst_rect, double angle, SDL_Point *center, SDL_RendererFlip flip);
};

#endif // !TEXTURE_MANAGER_H
