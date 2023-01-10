#ifndef GAME_H
#define GAME_H

#include "Utils.h"
#include "Bird.h"
#include "Obstacle.h"
#include <vector>
#include <algorithm>

class Game {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* surface;
    SDL_Texture* texture;
    Bird* bird;
    std::vector<std::pair<Obstacle*, Obstacle*>> obstacles;
    Uint32 obstacle_spawn_timer;
    int score;
    bool running;

public:
    Game();
    virtual ~Game();

    void init(char const* title, int x, int y, int width, int height, bool fullscreen);
    void handleEvents();
    void update(Uint32 current_time);
    void render();
    void cleanUp();
    void displayGameOverMenu();
    void displayPauseMenu();

    inline bool isRunning() const { return running; }
    void setRunning(bool const running) { this->running = running; }
};

#endif // !GAME_H
