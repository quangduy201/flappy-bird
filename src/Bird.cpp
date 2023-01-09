#include "Bird.h"
#include <iostream>

Bird::Bird(SDL_Renderer* renderer) : renderer(renderer)
{
    // Load the texture for the bird
    texture = IMG_LoadTexture(renderer, "res/image/yellowbird-upflap.png");
    if (texture == nullptr)
    {
        std::cerr << "Failed to load bird texture: " << SDL_GetError() << std::endl;
        return;
    }
    std::cout << "Bird created!..." << std::endl;
    position = new SDL_Point { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
    velocity = new SDL_Point { 0, 0 };

    int w, h;
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    bounding_box = new SDL_Rect { position->x, position->y, w, h };
}

Bird::~Bird()
{
    SDL_DestroyTexture(texture);
}

void Bird::flap()
{
    velocity->y = -10;
}

void Bird::update()
{
    position->x += velocity->x;
    position->y += velocity->y;

    velocity->y += 1;

    bounding_box->x = position->x;
    bounding_box->y = position->y;
}

void Bird::render()
{
    SDL_Rect dest_rect = { position->x, position->y, bounding_box->w, bounding_box->h };
    SDL_RenderCopy(renderer, texture, nullptr, &dest_rect);
}

bool Bird::isColliding(Obstacle* obstacle)
{
    return SDL_HasIntersection(bounding_box, obstacle->getBoundingBox());
}
