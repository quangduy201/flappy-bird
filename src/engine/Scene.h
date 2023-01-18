#ifndef SCENE_H
#define SCENE_H

#include "Camera.h"
#include "EntityManager.h"
#include <SDL2/SDL.h>

class Scene
{
public:
    std::string name;
    Camera camera;
    EntityManager entity_manager;
    bool running;

    Scene(std::string name) : name(name), running(true) {}
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
