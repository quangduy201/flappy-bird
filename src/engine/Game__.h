#ifndef GAME__H
#define GAME__H

#include "../util/Utils.h"
#include "../entities/Bird.h"
#include "../entities/Obstacle.h"
#include "../entities/Ground.h"
#include "../entities/Background.h"
#include <vector>
#include <algorithm>

// class Game
// {
// private:
//     SDL_Window* window;
//     SDL_Renderer* renderer;
//     SDL_Texture* texture;
//     Background* background;
//     Bird* bird;
//     std::vector<std::pair<Obstacle*, Obstacle*>> obstacles;
//     Ground* ground;
//     float obstacle_spawn_timer;
//     int score;
//     bool running;

// public:
//     Game();
//     virtual ~Game();

//     void init(char const* title, int x, int y, int width, int height, bool fullscreen);
//     void handleEvents();
//     void update(float delta_time);
//     void render();
//     void cleanUp();
//     void displayGameOverMenu();
//     void displayPauseMenu();

//     inline bool isRunning() const { return running; }
//     void setRunning(bool const running) { this->running = running; }
// };

#endif // !GAME__H
