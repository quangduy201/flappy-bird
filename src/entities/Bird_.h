#ifndef BIRD__H
#define BIRD__H

#include "../engine/ECS.h"
#include "../components/Components.h"

class Bird : public Entity
{
private:


public:
    Bird() {}
    virtual ~Bird() {}

    // void update(float delta_time) override
    // {
    //     getComponent<TransformComponent>().position += getComponent<RigidBodyComponent>().velocity * delta_time;
    // }

    // void render() override
    // {

    // }
};

#endif // !BIRD__H
