#ifndef PLAY_SCENE_H
#define PLAY_SCENE_H

#include "ECS.h"
#include "Scene.h"
#include "../components/Components.h"
#include "../entities/Entities.h"

class PlayScene : public Scene
{
public:
    PlayScene(std::string name, SDL_Renderer *renderer) : Scene(name, renderer) {}
    ~PlayScene() {}

    void init() override
    {
        // Initialize any necessary resources for the main menu scene
        auto bird = entity_manager.createEntity();
        entity_manager.entities[bird]->addComponent<TransformComponent>();
        entity_manager.entities[bird]->addComponent<SpriteComponent>();

        auto background = entity_manager.createEntity();
        entity_manager.entities[background]->addComponent<TransformComponent>();
        entity_manager.entities[background]->addComponent<SpriteComponent>();

        auto ground = entity_manager.createEntity();
        entity_manager.entities[ground]->addComponent<TransformComponent>();
        entity_manager.entities[ground]->addComponent<SpriteComponent>();

        auto obstacle = entity_manager.createEntity();
        entity_manager.entities[obstacle]->addComponent<TransformComponent>();
        entity_manager.entities[obstacle]->addComponent<SpriteComponent>();
    }

    void update(float delta_time) override
    {
        // Update any necessary systems for the main menu scene
        auto &bird = entity_manager.entities[0];
        auto &background = entity_manager.entities[1];

        bird->getComponent<RigidBodyComponent>().velocity.y += (-9.8f) * bird->getComponent<RigidBodyComponent>().gravity_scale;
        bird->getComponent<TransformComponent>().position += bird->getComponent<RigidBodyComponent>().velocity * delta_time;
        background->getComponent<TransformComponent>().position += background->getComponent<RigidBodyComponent>().velocity * delta_time;
        camera.setPosition(background->getComponent<TransformComponent>().position);

        entity_manager.update(delta_time);
    }

    void render() override
    {
        // Render the main menu scene
    }

    void handleEvents() override
    {
        // Cleanup any resources used by the main menu scene
    }

    void cleanUp() override
    {
    }
};

#endif // !PLAY_SCENE_H
