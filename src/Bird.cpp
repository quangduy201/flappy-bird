#include "entities/Bird.h"
#include <iostream>

Bird::Bird(SDL_Renderer* renderer) : renderer(renderer)
{
    // Load the texture for the bird
    texture = IMG_LoadTexture(renderer, "res/image/flappy-bird-sprite.png");
    if (texture == nullptr)
    {
        std::cerr << "Failed to load bird texture: " << SDL_GetError() << std::endl;
        return;
    }
    frames.push_back({ 3, 491, BIRD_PIXEL_WIDTH, BIRD_PIXEL_HEIGHT });
    frames.push_back({ 31, 491, BIRD_PIXEL_WIDTH, BIRD_PIXEL_HEIGHT });
    frames.push_back({ 59, 491, BIRD_PIXEL_WIDTH, BIRD_PIXEL_HEIGHT });

    current_frame = 0;
    angle = 0.0;
    animation_timer = SDL_GetTicks();

    position = new SDL_FPoint { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4 };
    velocity = new SDL_FPoint { 0, 0 };

    bounding_box = new SDL_FRect { position->x, position->y, BIRD_PIXEL_WIDTH * IMAGE_SCALE, BIRD_PIXEL_HEIGHT * IMAGE_SCALE };

    std::cout << "Bird created!..." << std::endl;
}

Bird::~Bird()
{
    SDL_DestroyTexture(texture);
    delete position;
    delete velocity;
    delete bounding_box;

    std::cout << "Bird detroyed!" << std::endl;
}

void Bird::flap()
{
    velocity->y = -8.0f;
    current_frame = 2;
    animation_timer = SDL_GetTicks();
}

void Bird::update(Uint32 current_time)
{
    if (current_time - animation_timer > 100)
    {
        current_frame = (current_frame + 1) % frames.size();
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
    SDL_RenderCopyExF(renderer, texture, &frames[current_frame], bounding_box, angle, nullptr, SDL_FLIP_NONE);
}

bool Bird::isColliding(Obstacle* obstacle)
{
    return SDL_HasIntersectionF(bounding_box, obstacle->getBoundingBox());
}

bool Bird::isColliding(Ground* ground)
{
    return SDL_HasIntersectionF(bounding_box, ground->getBoundingBox());
}
