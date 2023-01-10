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
    {
        delete obstacle.first;
        delete obstacle.second;
    }
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

    // Create surface for the window
    surface = IMG_Load("res/image/background-day.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    // Create the bird
    bird = new Bird(renderer);

    // Create the null obstacle
    obstacles.push_back(std::make_pair(new Obstacle(renderer, true, -1000, -2.5f), new Obstacle(renderer, false, -1000, -2.5f)));
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
                    // std::cout << "p(" << bird->getPosition()->x << ", " << bird->getPosition()->y << ")" << std::endl;
                    // std::cout << "v(" << bird->getVelocity()->x << ", " << bird->getVelocity()->y << ")" << std::endl;
                }
                break;
            default:
                break;
        }
    }
}

void Game::update(Uint32 current_time)
{
    if (current_time - obstacle_spawn_timer > 1750)
    {
        int gap = rand() % (int)(SCREEN_HEIGHT - Obstacle::GAP - 200) + 100;

        Obstacle* upper = new Obstacle(renderer, true, gap, -2.5f);
        Obstacle* lower = new Obstacle(renderer, false, gap, -2.5f);
        obstacles.push_back({ upper, lower });
        obstacle_spawn_timer = current_time;

        // Update score
        if (bird->getPosition()->x > obstacles[1].first->getPosition()->x)
        {
            std::cout << ++score << std::endl;
        }

        // If the first column of obstacles pass the screen, delete it
        if (obstacles.size() > 2)
        {
            delete obstacles[0].first;
            delete obstacles[0].second;
            obstacles.erase(obstacles.begin());
            // std::cout << "Deleted the first obstacles" << std::endl;
        }
    }
    bird->update(current_time);

    for (auto& obstacle : obstacles)
    {
        obstacle.first->update(current_time);
        obstacle.second->update(current_time);
    }

    for (auto& obstacle : obstacles)
    {
        if (bird->isColliding(obstacle.first) || bird->isColliding(obstacle.second))
        {
            running = false;
            return;
        }
    }
}

void Game::render()
{
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, texture, nullptr, nullptr);

    bird->render();

    for (auto& obstacle : obstacles)
    {
        obstacle.first->render();
        obstacle.second->render();
    }

    SDL_RenderPresent(renderer);
}

void Game::cleanUp()
{
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
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
