#ifndef RIGIDBODY_COMPONENT_H
#define RIGIDBODY_COMPONENT_H

#include "../engine/ECS.h"
#include "../util/Vector2.h"

class RigidBodyComponent : public Component
{
public:
    Vector2 velocity;
    float mass;
    float gravity_scale;

    RigidBodyComponent() : velocity({ 0.0f, 0.0f }), mass(0.0f), gravity_scale(0.0f) {}
    RigidBodyComponent(float const &x, float const &y) : velocity({ x, y }) {}
    RigidBodyComponent(const Vector2 &velocity) : velocity(velocity) {}
    RigidBodyComponent(const Vector2 &velocity, const float &mass, const float &gravity_scale)
        : velocity(velocity), mass(mass), gravity_scale(gravity_scale) {}
    ~RigidBodyComponent() {}

    void init() override
    {
    }

    void update(float delta_time) override
    {

    }

    void render() override
    {

    }
};

#endif // !RIGIDBODY_COMPONENT_H
