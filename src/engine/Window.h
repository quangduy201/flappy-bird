#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Window
{
public:
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool running;

    Window();
    virtual ~Window();

    void init(const char *title, int x, int y, int width, int height, Uint32 flags);

    void update(float delta_time);

    void render();

    void handleEvents();

    void cleanUp();
};

#endif // !WINDOW_H
