#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "ECS.h"
#include "../components/Components.h"

class EntityManager : public Manager
{
public:
    EntityMap entities;
    EntityID next_id = 0;

    EntityManager() : next_id(0) {}
    virtual ~EntityManager() {}

    void init()
    {
        next_id = 0;
    }

    // Function to create a new entity
    EntityID createEntity()
    {
        EntityID id = next_id;
        next_id++;
        entities[id] = std::make_unique<Entity>();
        entities[id]->id = id;
        return id;
    }

    void update(float delta_time)
    {
        for (auto &[entityID, entity] : entities)
        {
            if (!entity->active) continue;
            if (!entity->hasComponents<TransformComponent>()) continue;
            if (!entity->hasComponents<SpriteComponent>()) continue;

            for (std::size_t i = 0; i < MAX_COMPONENTS; ++i)
                if (entity->components_mask[i]) {
                    entity->components_array[i]->update(delta_time);
                }
        }
    }

    void render()
    {
        for (auto &[entityID, entity] : entities)
        {
            if (!entity->active) continue;
            if (!entity->hasComponents<TransformComponent>()) continue;
            if (!entity->hasComponents<SpriteComponent>()) continue;

            for (std::size_t i = 0; i < MAX_COMPONENTS; ++i)
                if (entity->components_mask[i])
                    entity->components_array[i]->render();
        }
    }

    void destroyEntity(EntityID id)
    {
        entities.erase(id);
    }

    void destroyAllEntities()
    {
        entities.clear();
    }
};

#endif // !ENTITY_MANAGER_H
