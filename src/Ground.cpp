#include "entities/Ground.h"
#include <iostream>

Ground::Ground(SDL_Renderer* renderer, float velocity) : renderer(renderer), velocity(velocity)
{
    // Load the texture for the obstacle
    texture = IMG_LoadTexture(renderer, "res/image/flappy-bird-sprite.png");
    if (texture == nullptr)
    {
        std::cerr << "Failed to load ground texture: " << SDL_GetError() << std::endl;
        return;
    }
    frame = { 292, 0, GROUND_PIXEL_WIDTH, GROUND_PIXEL_HEIGHT };

    last_update_time = SDL_GetTicks();

    position = new SDL_FPoint { 0.0f, SCREEN_HEIGHT * 0.78f };

    bounding_box = new SDL_FRect { position->x, position->y, GROUND_PIXEL_WIDTH * IMAGE_SCALE, GROUND_PIXEL_HEIGHT * IMAGE_SCALE };

    std::cout << "Ground created!..." << std::endl;
}

Ground::~Ground()
{
    SDL_DestroyTexture(texture);
    delete position;
    delete bounding_box;

    std::cout << "Ground destroyed!" << std::endl;
}

void Ground::update(float current_time)
{
    float elapsed_time = (current_time - last_update_time) / 1000.0f;

    position->x += velocity;
    bounding_box->x = position->x;

    last_update_time = current_time;
}

void Ground::render()
{
    SDL_RenderCopyF(renderer, texture, &frame, bounding_box);
}
