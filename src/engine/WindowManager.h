#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "ECS.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class WindowManager : public Manager
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool quit;
public:
    WindowManager() : window(nullptr), renderer(nullptr) {}
    virtual ~WindowManager() {}

    inline bool isQuit() const { return quit; }
    void setQuit(bool const quit) { this->quit = quit; }

    void init(char const* title, int x, int y, int width, int height, bool fullscreen)
    {
        // Initialize SDL
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
            quit = false;
            return;
        }
        std::cout << "SDL initialized!..." << std::endl;

        // Initialize SDL_image
        int img_flags = IMG_INIT_PNG;
        if (!(IMG_Init(img_flags) & img_flags))
        {
            std::cerr << "SDL_image initialization failed: " << IMG_GetError() << std::endl;
            quit = false;
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
            quit = false;
            return;
        }
        std::cout << "Window created!..." << std::endl;

        // Create a renderer for the window
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == nullptr)
        {
            std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
            quit = false;
            return;
        }
        std::cout << "Renderer created!..." << std::endl;
    }

    void handleEvents()
    {
        // Handle input events here
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_SPACE) {
                        // Handle space bar key down event here
                        // You can call a function or set a flag to notify other classes that the event has been handled.
                    }
                    break;
                case SDL_QUIT:
                    quit = true;
                    break;
                default:
                    break;
            }
        }
    }

    void update(float delta_time) override
    {

    }

    void cleanup()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

        std::cout << "Window cleaned up!" << std::endl;
    }
};

#endif // !WINDOW_MANAGER_H
