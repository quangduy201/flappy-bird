#include "engine/Window.h"

SDL_Renderer *Window::renderer = nullptr;
bool Window::running = true;

Window::Window() {}
Window::~Window() {}

void Window::init(const char *title, int x, int y, int width, int height, bool fullscreen)
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

    // Create a renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        running = false;
        return;
    }
    std::cout << "Renderer created!..." << std::endl;
    // SDL_SetRenderDrawColor(renderer, 100, 0, 255, 1);

    // // Get the texture of the game
    // texture = IMG_LoadTexture(renderer, "res/image/flappy-bird-sprite.png");
    // if (texture == nullptr)
    // {
    //     std::cerr << "Failed to load the texture: " << SDL_GetError() << std::endl;
    //     running = false;
    //     return;
    // }
    // std::cout << "Texture loaded!..." << std::endl;
}

void Window::handleEvents()
{

}

void Window::update(float delta_time)
{

}

void Window::render()
{

}

void Window::cleanUp()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << "Window cleaned up!" << std::endl;
}

