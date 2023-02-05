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
    game->run();
    game->cleanUp();
    delete game;
    return EXIT_SUCCESS;
}
