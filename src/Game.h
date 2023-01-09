#ifndef GAME_H
#define GAME_H

#include "Utils.h"
#include "Bird.h"
#include "Obstacle.h"
#include <vector>

class Game {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    Bird* bird;
    std::vector<Obstacle*> obstacles;
    int score;
    bool running;

public:
    Game();
    virtual ~Game();

    void init(char const* title, int x, int y, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void cleanUp();
    void displayGameOverMenu();
    void displayPauseMenu();

    inline bool isRunning() const { return running; }
    void setRunning(bool const running) { this->running = running; }
};

#endif // !GAME_H
