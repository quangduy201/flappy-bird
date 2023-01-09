#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int constexpr SCREEN_WIDTH = 640;
int constexpr SCREEN_HEIGHT = 480;
int constexpr FULLSCREEN_MODE = false;
int constexpr FPS = 60;
Uint32 constexpr frame_time = 1000 / FPS;

#endif // !UTILS_H
