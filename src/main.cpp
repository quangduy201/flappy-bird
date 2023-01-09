#include "Utils.h"
#include "Game.h"
#include <iostream>

auto main(int argc, char** argv) -> int
{
    Uint32 last_time, elapsed_time;

    Game* game = new Game();
    game->init("Flappy Bird", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, FULLSCREEN_MODE);
    while (game->isRunning())
    {
        last_time = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        elapsed_time = SDL_GetTicks() - last_time;
        if (elapsed_time < frame_time)
            SDL_Delay(frame_time - elapsed_time);
    }

    game->cleanUp();
    delete game;
    return EXIT_SUCCESS;
}
