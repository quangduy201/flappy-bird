#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "../engine/Component.h"
#include "../util/Vector2D.h"

class TransformComponent : public Component
{
public:
    Vector2D position;
    Vector2D velocity;
};

#endif // !TRANSFORM_COMPONENT_H
