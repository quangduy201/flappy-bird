#include "entities/Background.h"
#include <iostream>

Background::Background(SDL_Renderer* renderer) : renderer(renderer)
{
    // Load the texture for the background
    texture = IMG_LoadTexture(renderer, "res/image/flappy-bird-sprite.png");
    if (texture == nullptr)
    {
        std::cerr << "Failed to load background texture: " << SDL_GetError() << std::endl;
        return;
    }
    frame = { 0, 0, BACKGROUND_PIXEL_WIDTH, BACKGROUND_PIXEL_HEIGHT };


    position = new SDL_FPoint { 0.0f, 0.0f };

    std::cout << "Ground created!..." << std::endl;
}

Background::~Background()
{
    SDL_DestroyTexture(texture);
    delete position;

    std::cout << "Ground destroyed!" << std::endl;
}

void Background::update(Uint32 current_time)
{

}

void Background::render()
{
    SDL_RenderCopyF(renderer, texture, &frame, nullptr);
}

