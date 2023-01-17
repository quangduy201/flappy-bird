#ifndef SCENE_H
#define SCENE_H

#include "Camera.h"
#include "EntityManager.h"
#include <SDL2/SDL.h>

class Scene
{
public:
    std::string name;
    SDL_Renderer *renderer;
    Camera camera;
    EntityManager entity_manager;
    bool running;

    Scene(std::string name, SDL_Renderer* renderer) : name(name), renderer(renderer), running(true) {}
    virtual ~Scene() = default;

    virtual void init() = 0;
    virtual void update(float delta_time) = 0;
    virtual void render() = 0;
    virtual void handleEvents() = 0;
    virtual void cleanUp()
    {
        entity_manager.destroyAllEntities();
    }
};

#endif // !SCENE_H
