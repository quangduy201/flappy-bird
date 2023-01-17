#include "util/Utils.h"
#include "engine/Game.h"
#include <iostream>

Game *game = nullptr;

auto main(int argc, char** argv) -> int
{
    srand(time(NULL));
    Uint32 previous_time, current_time, elapsed_time;
    float delta_time;

    game = new Game();
    game->init();
    // while (game->isRunning())
    // {
    //     game->handleEvents();

    //     current_time = SDL_GetTicks();
    //     delta_time = (current_time - previous_time) / 1000.0f;

    //     game->update(delta_time);
    //     game->render();

    //     previous_time = current_time;
    //     elapsed_time = SDL_GetTicks() - previous_time;
    //     SDL_Delay(std::max(0, (int)(FRAME_TIME - elapsed_time)));
    // }
    game->run();

    game->cleanUp();
    delete game;
    return EXIT_SUCCESS;
}
