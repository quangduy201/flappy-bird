#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define GAME_TITLE "Flappy Bird"
#define SCREEN_WIDTH 400.0f
#define SCREEN_HEIGHT 700.0f
#define FULLSCREEN_MODE false
#define FPS 60

#define BACKGROUND_PIXEL_WIDTH  144
#define BACKGROUND_PIXEL_HEIGHT 256

#define GROUND_PIXEL_WIDTH  168
#define GROUND_PIXEL_HEIGHT 56

#define BIRD_PIXEL_WIDTH  17
#define BIRD_PIXEL_HEIGHT 12

#define OBSTACLE_PIXEL_WIDTH  26
#define OBSTACLE_PIXEL_HEIGHT 160

#define IMAGE_SCALE 2 * 1.6f

Uint32 constexpr frame_time = 1000 / FPS;

#endif // !UTILS_H
