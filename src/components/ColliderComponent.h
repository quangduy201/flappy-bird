#ifndef COLLIDER_COMPONENT_H
#define COLLIDER_COMPONENT_H

#include "../engine/ECS.h"
#include "../util/Vector2.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

class ColliderComponent: public Component
{
public:
    Vector2 position;
    Vector2 size;

    ColliderComponent() {}

    void init() override
    {
        position = entity->getComponent<TransformComponent>().position;
        auto &sprite = entity->getComponent<SpriteComponent>();
        size = { sprite.width * 1.0f, sprite.height * 1.0f };
    }

    void update(float delta_time) override
    {
        position = entity->getComponent<TransformComponent>().position;
        auto &sprite = entity->getComponent<SpriteComponent>();
        size = { sprite.width * 1.0f, sprite.height * 1.0f };
    }

    void render() override
    {

    }
};

#endif // !COLLIDER_COMPONENT_H

