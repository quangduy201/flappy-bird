#include "Obstacle.h"
#include <iostream>

Obstacle::Obstacle(SDL_Renderer* renderer, bool is_upper, int gap_pos, float velocity) : renderer(renderer), is_upper(is_upper)
{
    // Load the texture for the obstacle
    texture = IMG_LoadTexture(renderer, "res/image/pipe-green.png");
    if (texture == nullptr)
    {
        std::cerr << "Failed to load obstacle texture: " << SDL_GetError() << std::endl;
        return;
    }
    // std::cout << "Obstacle spawned!..." << std::endl;

    last_update_time = SDL_GetTicks();

    float pos_x, pos_y;
    if (is_upper)
    {
        pos_x = SCREEN_WIDTH;
        pos_y = gap_pos - 320 * IMAGE_SCALE;
    }
    else
    {
        pos_x = SCREEN_WIDTH;
        pos_y = gap_pos + Obstacle::GAP;
    }

    position = new SDL_FPoint { pos_x, pos_y };
    this->velocity = velocity;

    int w, h;
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    bounding_box = new SDL_FRect { position->x, position->y, w * IMAGE_SCALE, h * IMAGE_SCALE };
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
    SDL_FRect dest_rect = { position->x, position->y, bounding_box->w, bounding_box->h };
    SDL_RendererFlip flip = is_upper ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
    SDL_RenderCopyExF(renderer, texture, nullptr, &dest_rect, 0.0, nullptr, flip);
}
