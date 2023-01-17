#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Window
{
public:
    SDL_Window *window;
    static SDL_Renderer *renderer;
    // SDL_Texture *texture;
    static bool running;

    Window();
    virtual ~Window();

    void init(const char *title, int x, int y, int width, int height, bool fullscreen);

    void update(float delta_time);

    void render();

    void handleEvents();

    void cleanUp();
};

#endif // !WINDOW_H
