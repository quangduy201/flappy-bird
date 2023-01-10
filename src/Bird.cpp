#include "Bird.h"
#include <iostream>

Bird::Bird(SDL_Renderer* renderer) : renderer(renderer)
{
    // Load the texture for the bird
    textures.push_back(IMG_LoadTexture(renderer, "res/image/yellowbird-upflap.png"));
    textures.push_back(IMG_LoadTexture(renderer, "res/image/yellowbird-midflap.png"));
    textures.push_back(IMG_LoadTexture(renderer, "res/image/yellowbird-downflap.png"));
    for (auto& texture : textures)
    {
        if (texture == nullptr)
        {
            std::cerr << "Failed to load bird texture: " << SDL_GetError() << std::endl;
            return;
        }
    }
    std::cout << "Bird created!..." << std::endl;

    current_frame = 0;
    animation_timer = SDL_GetTicks();

    position = new SDL_FPoint { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4 };
    velocity = new SDL_FPoint { 0, 0 };

    int w, h;
    for (auto& texture : textures)
    {
        SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    }
    bounding_box = new SDL_FRect { position->x, position->y, w * IMAGE_SCALE, h * IMAGE_SCALE};
}

Bird::~Bird()
{
    for (auto& texture : textures)
    {
        SDL_DestroyTexture(texture);
    }
    textures.clear();
    delete bounding_box;
}

void Bird::flap()
{
    velocity->y = -8.0f;
    current_frame = 2;
    animation_timer = SDL_GetTicks();
}

void Bird::update(Uint32 current_time)
{
    if (current_time - animation_timer > 150)
    {
        current_frame = (current_frame + 1) % textures.size();
        animation_timer = current_time;
    }
    position->x += velocity->x;
    position->y += velocity->y;

    velocity->y += 0.5f;

    bounding_box->x = position->x;
    bounding_box->y = position->y;
}

void Bird::render()
{
    SDL_FRect dest_rect = { position->x, position->y, bounding_box->w, bounding_box->h };
    SDL_RenderCopyF(renderer, textures[current_frame], nullptr, &dest_rect);
}

bool Bird::isColliding(Obstacle* obstacle)
{
    return SDL_HasIntersectionF(bounding_box, obstacle->getBoundingBox());
}
