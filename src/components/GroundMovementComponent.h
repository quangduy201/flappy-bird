#ifndef GROUNDMOVEMENT_COMPONENT_H
#define GROUNDMOVEMENT_COMPONENT_H

#include "../engine/ECS.h"

#include "../engine/Game.h"

class Game;

class GroundMovementComponent : public Component
{
public:
    EntityID current_groundID;
    std::shared_ptr<Entity> current_ground;

    GroundMovementComponent() {}

    void init() override
    {
    }

    void update(float delta_time) override
    {
        if (current_ground->getComponent<TransformComponent>().position.x + current_ground->getComponent<SpriteComponent>().width <= 0)
        {
            spawnNewGround();
        }
    }

    void render() override
    {

    }

    void spawnNewGround()
    {
        current_groundID = Game::current_scene->entity_manager.createEntity();
        current_ground = Game::current_scene->entity_manager.entities[current_groundID];
        current_ground->addComponent<TransformComponent>(SCREEN_WIDTH, 0.0f);
    }
};

#endif // !GROUNDMOVEMENT_COMPONENT_H
