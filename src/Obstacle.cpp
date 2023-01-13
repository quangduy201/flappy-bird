#include "entities/Obstacle.h"
#include <iostream>

Obstacle::Obstacle(SDL_Renderer* renderer, bool is_upper, int gap_pos, float velocity) : renderer(renderer), is_upper(is_upper), velocity(velocity)
{
    // Load the texture for the obstacle
    texture = IMG_LoadTexture(renderer, "res/image/flappy-bird-sprite.png");
    if (texture == nullptr)
    {
        std::cerr << "Failed to load obstacle texture: " << SDL_GetError() << std::endl;
        return;
    }
    frame = { 84, 323, OBSTACLE_PIXEL_WIDTH, OBSTACLE_PIXEL_HEIGHT };

    last_update_time = SDL_GetTicks();

    float pos_x, pos_y;
    if (is_upper)
    {
        pos_x = SCREEN_WIDTH;
        pos_y = gap_pos - OBSTACLE_PIXEL_HEIGHT * IMAGE_SCALE;
    }
    else
    {
        pos_x = SCREEN_WIDTH;
        pos_y = gap_pos + Obstacle::GAP;
    }

    position = new SDL_FPoint { pos_x, pos_y };

    bounding_box = new SDL_FRect { position->x, position->y, OBSTACLE_PIXEL_WIDTH * IMAGE_SCALE, OBSTACLE_PIXEL_HEIGHT * IMAGE_SCALE };
    // std::cout << "Obstacle spawned!..." << std::endl;
}

Obstacle::~Obstacle()
{
    SDL_DestroyTexture(texture);
    delete position;
    delete bounding_box;
}

void Obstacle::update(Uint32 current_time)
{
    float elapsed_time = (current_time - last_update_time) / 1000.0f;

    position->x += velocity;
    bounding_box->x = position->x;

    last_update_time = current_time;
}

void Obstacle::render()
{
    SDL_RendererFlip flip = is_upper ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
    SDL_RenderCopyExF(renderer, texture, &frame, bounding_box, 0.0, nullptr, flip);
}
