#include "engine/CollisionManager.h"

bool CollisionManager::checkCollision(Entity e1, Entity e2)
{
    auto& collider1 = e1.getComponent<ColliderComponent>();
    auto& collider2 = e2.getComponent<ColliderComponent>();

    return (collider1.position.x < collider2.position.x + collider2.size.x &&
            collider1.position.x + collider1.size.x > collider2.position.x &&
            collider1.position.y < collider2.position.y + collider2.size.y &&
            collider1.position.y + collider1.size.y > collider2.position.y);
}

bool CollisionManager::checkCollision(const ColliderComponent &collider1, const ColliderComponent &collider2)
{
    return (collider1.position.x < collider2.position.x + collider2.size.x &&
            collider1.position.x + collider1.size.x > collider2.position.x &&
            collider1.position.y < collider2.position.y + collider2.size.y &&
            collider1.position.y + collider1.size.y > collider2.position.y);
}

bool CollisionManager::checkCollision(const SDL_Rect &rect1, const SDL_Rect &rect2)
{
    return (rect1.x < rect2.x + rect2.w &&
            rect1.x + rect1.w > rect2.x &&
            rect1.y < rect2.y + rect2.h &&
            rect1.y + rect1.h > rect2.y);
}
