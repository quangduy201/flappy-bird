#include "Obstacle.h"
#include <iostream>

Obstacle::Obstacle(SDL_Renderer* renderer) : renderer(renderer)
{
    // Load the texture for the obstacle
    texture = IMG_LoadTexture(renderer, "res/image/pipe-green.png");
    if (texture == nullptr)
    {
        std::cerr << "Failed to load obstacle texture: " << SDL_GetError() << std::endl;
        return;
    }
    std::cout << "Obstacle created!..." << std::endl;


}

Obstacle::~Obstacle()
{
    SDL_DestroyTexture(texture);
}

void Obstacle::update()
{

}

void Obstacle::render()
{

}
