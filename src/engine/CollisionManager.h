#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "ECS.h"
#include "../components/ColliderComponent.h"

class CollisionManager
{
public:
    static bool checkCollision(Entity entt1, Entity entt2);
    static bool checkCollision(const ColliderComponent &col1, const ColliderComponent &col2);
    static bool checkCollision(const SDL_Rect &rect1, const SDL_Rect &rect2);
};

#endif // !COLLISION_MANAGER_H
