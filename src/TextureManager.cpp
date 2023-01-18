#include "engine/TextureManager.h"

#include "engine/Window.h"

SDL_Texture *TextureManager::LoadTexture(const std::string path)
{
    SDL_Texture *texture = IMG_LoadTexture(Window::renderer, path.c_str());
    return texture;
}

void TextureManager::Draw(SDL_Texture *texture, SDL_Rect src_rect, SDL_Rect dst_rect, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(Window::renderer, texture, &src_rect, &dst_rect, angle, center, flip);
}
