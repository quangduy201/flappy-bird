#ifndef GAME_H
#define GAME_H

#include "Window.h"
#include "Scene.h"
#include "MainMenuScene.h"
#include "PlayScene.h"
#include "../util/Utils.h"

class Game
{
public:
    Window window;
    std::unique_ptr<Scene> current_scene;
    bool running;

    Game();
    ~Game();
    void init();
    void handleEvents();
    void update(float delta_time);
    void render();
    void cleanUp();
    void changeScene(std::unique_ptr<Scene> new_scene);
    inline bool isRunning();
    void run();
};

#endif // !GAME_H
