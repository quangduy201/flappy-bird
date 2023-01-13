#ifndef COMPONENT_H
#define COMPONENT_H

#include "Entity.h"

class Component
{
private:
    Entity* entity;
    int id;
    static int next_id;
public:
    Component(Entity* entity) : entity(entity), id(next_id++) {}
    virtual ~Component() {}

    virtual void update() = 0;
};

#endif // !COMPONENT_H
