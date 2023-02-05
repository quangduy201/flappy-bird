#include "engine/TextureManager.h"

// #include "engine/Window.h"
#include "engine/Game.h"

SDL_Texture *TextureManager::LoadTexture(const std::string path)
{
    SDL_Texture *texture = IMG_LoadTexture(Game::window.renderer, path.c_str());
    return texture;
}

void TextureManager::Draw(SDL_Texture *texture, SDL_Rect src_rect, SDL_FRect dst_rect, double angle, SDL_FPoint *center, SDL_RendererFlip flip)
{
    SDL_RenderCopyExF(Game::window.renderer, texture, &src_rect, &dst_rect, angle, center, flip);
}
