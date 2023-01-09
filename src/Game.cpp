#include "Game.h"
#include <iostream>

Game::Game()
{
    running = true;
    score = 0;
}
Game::~Game()
{
    for (auto& obstacle : obstacles)
        delete obstacle;
    obstacles.clear();
    delete bird;
}

void Game::init(char const* title, int x, int y, int width, int height, bool fullscreen)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        running = false;
        return;
    }
    std::cout << "SDL initialized!..." << std::endl;

    // Initialize SDL_image
    int img_flags = IMG_INIT_PNG;
    if (!(IMG_Init(img_flags) & img_flags))
    {
        std::cerr << "SDL_image initialization failed: " << IMG_GetError() << std::endl;
        running = false;
        return;
    }
    std::cout << "SDL_image initialized!..." << std::endl;

    // Create a window
    int flags = 0;
    if (fullscreen)
    {
        flags |= SDL_WINDOW_FULLSCREEN;
    }
    window = SDL_CreateWindow(title, x, y, width, height, flags);
    if (window == nullptr)
    {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        running = false;
        return;
    }
    std::cout << "Window created!..." << std::endl;

    // Create a renderer for the window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        running = false;
        return;
    }
    std::cout << "Renderer created!..." << std::endl;
    SDL_SetRenderDrawColor(renderer, 255, 255, 100, 0);

    // Create the bird
    bird = new Bird(renderer);

    // Create the obstacles
    int const NUM_OBSTACLES = 10;
    obstacles.resize(NUM_OBSTACLES);
    for (auto& obstacle : obstacles)
    {
        obstacle = new Obstacle(renderer);
    }
}

void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    displayPauseMenu();
                    running = false;
                }
                if (event.key.keysym.sym == SDLK_SPACE)
                {
                    bird->flap();
                    std::cout << "p(" << bird->getPosition()->x << ", " << bird->getPosition()->y << ")" << std::endl;
                    std::cout << "v(" << bird->getVelocity()->x << ", " << bird->getVelocity()->y << ")" << std::endl;
                }
                break;
            default:
                break;
        }
    }
}

void Game::update()
{
    bird->update();

    for (auto& obstacle : obstacles)
    {
        obstacle->update();
    }

    for (auto& obstacle : obstacles)
    {
        if (bird->isColliding(obstacle))
        {
            running = false;
            return;
        }
    }
}

void Game::render()
{
    SDL_RenderClear(renderer);

    bird->render();

    for (auto& obstacle : obstacles)
    {
        obstacle->render();
    }

    SDL_RenderPresent(renderer);
}

void Game::cleanUp()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "Game cleaned up!" << std::endl;
}

void Game::displayGameOverMenu()
{

}

void Game::displayPauseMenu()
{

}
