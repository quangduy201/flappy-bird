#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define GAME_TITLE "Flappy Bird"
#define SCREEN_WIDTH 400.0f
#define SCREEN_HEIGHT 700.0f
#define FULLSCREEN_MODE false
#define FPS 60
#define IMAGE_SCALE 1.4f

Uint32 constexpr frame_time = 1000 / FPS;

#endif // !UTILS_H
