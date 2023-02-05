#include "engine/Game.h"

#include <SDL2/SDL.h>

Window Game::window;
std::unique_ptr<Scene> Game::current_scene;
bool Game::running = true;

Game::Game() {}
Game::~Game() {}

void Game::init()
{
    window.init(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_FLAG);
    current_scene = std::make_unique<MainMenuScene>("main menu");
    current_scene->init();
}

void Game::handleEvents()
{
    auto &bird = current_scene->entity_manager.entities[1];
    // window.handleEvents();
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        // current_scene->handleEvents(event);
        switch (event.type)
        {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    running = false;
                if (event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_UP)
                {
                    if (current_scene->name.compare("main menu") == 0)
                    {
                        std::unique_ptr<Scene> new_scene = std::make_unique<PlayScene>("play");
                        changeScene(new_scene);
                    }
                    else
                    {
                        auto &bird_rigidbody = bird->getComponent<RigidBodyComponent>();
                        bird_rigidbody.velocity.y = -180.0f;
                    }
                }
                break;
            case SDL_QUIT:
                running = false;
                break;
            default:
            // std::cout << current_scene->name << std::endl;
                break;
        }
    }
}

void Game::update(float delta_time)
{
    window.update(delta_time);
    current_scene->update(delta_time);
}

void Game::render()
{
    SDL_RenderClear(window.renderer);

    window.render();
    current_scene->render();

    SDL_RenderPresent(window.renderer);
}

void Game::cleanUp()
{
    window.cleanUp();
    current_scene->cleanUp();
    current_scene.reset(nullptr);
}

void Game::changeScene(std::unique_ptr<Scene> &new_scene)
{
    current_scene->cleanUp();
    current_scene = std::move(new_scene);
    current_scene->init();
}

bool Game::isRunning()
{
    return running && window.running && current_scene->running;
}

void Game::run()
{
    Uint32 previous_time, current_time, elapsed_time;
    float delta_time;
    while (isRunning())
    {
        handleEvents();

        current_time = SDL_GetTicks();
        delta_time = (current_time - previous_time) / 1000.0f;

        update(delta_time);
        render();

        previous_time = current_time;
        elapsed_time = SDL_GetTicks() - previous_time;
        SDL_Delay(std::max(0, (int)(FRAME_TIME - elapsed_time)));
    }
}
