#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../components/Components.h"
#include "../engine/EntityManager.h"
#include "../engine/Window.h"

class RenderSystem
{
public:
    void update(EntityManager& entities, float delta_time)
    {
        for (auto& [entity_id, entity] : entities.entities)
        {
            if (!entity->hasComponents<SpriteComponent>()) continue;
            if (!entity->hasComponents<TransformComponent>()) continue;

            auto &sprite = entity->getComponent<SpriteComponent>();
            auto &transform = entity->getComponent<TransformComponent>();

            // render the entity's sprite at its position
            SDL_Rect dst = { transform.position.x, transform.position.y, sprite.width, sprite.height };
            SDL_RenderCopy(Window::renderer, sprite.texture, &sprite.animations[sprite.current_animation].getCurrentFrame(), &dst);
        }
    }
};

#endif // !RENDER_SYSTEM_H
