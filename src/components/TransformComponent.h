#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "../engine/ECS.h"
#include "../util/Vector2.h"

class TransformComponent : public Component
{
public:
    Vector2 position;
    Vector2 scale;
    float scale_speed;
    float rotation;
    float rotation_speed;
    float speed;

    TransformComponent() : position({ 0.0f, 0.0f }), scale({ 0.0f, 0.0f }), rotation(0.0f), speed(0.0f) {}
    TransformComponent(const float &x, const float &y) : position({ x, y }) {}
    TransformComponent(const Vector2 &position) : position(position) {}
    TransformComponent(const Vector2 &position, const float &rotation, const Vector2 &scale)
        : position(position), rotation(rotation), scale(scale) {}
    ~TransformComponent() {}

    void init() override
    {
    }

    void update(float delta_time) override
    {
        // Update position based on velocity and speed
        if (entity->hasComponents<RigidBodyComponent>())
        {
            auto &rigidBody = entity->getComponent<RigidBodyComponent>();
            position += rigidBody.velocity * delta_time * speed;
        }
        // Update rotation based on rotation speed
        rotation += rotation_speed * delta_time;
        // Update scale based on scale speed
        scale += scale_speed * delta_time;
    }

    void render() override
    {

    }
};

#endif // !TRANSFORM_COMPONENT_H
