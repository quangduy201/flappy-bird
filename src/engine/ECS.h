#ifndef ECS_H
#define ECS_H

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <set>
#include <unordered_map>

using ComponentID = std::size_t;
using Group = std::size_t;

class Component;
class Entity;

class Component
{
public:
    Entity* entity;
    virtual ~Component() = default;

    virtual void init() {}
    virtual void update() {}

};

inline ComponentID getNewComponentTypeID()
{
    static ComponentID lastID = 0u;
    return lastID++;
}

template <typename T>
inline ComponentID getComponentTypeID() noexcept
{
    static_assert (std::is_base_of<Component, T>::value, "");
    static ComponentID typeID{ getNewComponentTypeID() };
    return typeID;
}

class Entity
{
private:
    std::unordered_map<ComponentID, std::unique_ptr<Component>> components;

public:
    void update()
    {
        for (auto& [id, component] : components)
        {
            component->update();
        }
    }

    template <typename T, typename... TArgs>
    T& addComponent(TArgs&&... args)
    {
        T* c = new T(std::forward<TArgs>(args)...);
        components[getComponentTypeID<T>()].reset(c);
        return *c;
    }

    template <typename T>
    T& getComponent() const
    {
        auto ptr = components[getComponentTypeID<T>()].get();
        return *static_cast<T*>(ptr);
    }
};

class System
{
public:
    virtual void update() = 0;
};

class Manager
{
private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::set<std::unique_ptr<System>> systems;

public:
    void update()
    {
        for (auto& system : systems)
        {
            system->update();
        }
    }

    void addSystem(std::unique_ptr<System> system)
    {
        systems.insert(std::move(system));
    }

    std::unique_ptr<Entity> &addEntity()
    {
        auto e = std::make_unique<Entity>();
        entities.emplace_back(std::move(e));
        return entities.back();
    }
};

#endif // !ECS_H
