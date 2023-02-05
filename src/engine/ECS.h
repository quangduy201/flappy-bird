#ifndef ECS_H
#define ECS_H

#include <iostream>
#include <memory>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <bitset>
#include <array>
#include <vector>

class Component;
class Entity;

using ComponentID = std::uint32_t;
using EntityID = std::uint32_t;
using GroupID = std::uint32_t;

constexpr std::size_t MAX_COMPONENTS = 32;
constexpr std::size_t MAX_ENTITIES = 32;
constexpr std::size_t MAX_GROUP = 32;

using ComponentBitset = std::bitset<MAX_COMPONENTS>;
using ComponentArray = std::array<Component*, MAX_COMPONENTS>;
using ComponentUPtr = std::vector<std::unique_ptr<Component>>;
using EntityMap = std::map<EntityID, std::shared_ptr<Entity>>;
using GroupMap = std::unordered_map<GroupID, std::vector<Entity*>>;

class Component
{
public:
    Entity* entity;

    virtual void init() {}
    virtual void update(float delta_time) {}
    virtual void render() {}

    static ComponentID getComponentType()
    {
        static ComponentID id = 0u;
        return id++;
    }

    template <typename T>
    static inline ComponentID getComponentTypeID() noexcept
    {
        static_assert (std::is_base_of<Component, T>::value, "");
        static ComponentID type_id{ getComponentType() };
        return type_id;
    }

    virtual ~Component() = default;
};

class Entity
{
public:
    EntityID id;
    GroupID group_id;
    ComponentUPtr components;
    ComponentArray components_array;
    ComponentBitset components_mask;
    bool active = true;

    Entity() : id(id), active(true) {}

    template <typename T>
    bool hasComponents() const
    {
        return components_mask[Component::getComponentTypeID<T>()];
    }

    template <typename T, typename... TArgs>
    T &addComponent(TArgs&&... args)
    {
        T *new_component(new T(std::forward<TArgs>(args)...));
        new_component->entity = this;
        std::unique_ptr<Component> unique_ptr{ new_component };
        components.emplace_back(std::move(unique_ptr));

        ComponentID component_type_id = Component::getComponentTypeID<T>();
        components_array[component_type_id] = new_component;
        components_mask[component_type_id] = true;

		new_component->init();
		return *new_component;
	}

    template <typename T>
    T &getComponent() const
    {
        ComponentID component_type_id = Component::getComponentTypeID<T>();
		return *static_cast<T*>(components_array[component_type_id]);
	}

    template <typename T>
    void removeComponent()
    {
        ComponentID component_type_id = Component::getComponentTypeID<T>();
        components.erase(std::remove_if(components.begin(), components.end(),
                            [component_type_id](const std::unique_ptr<Component> &c)
                            {
                                return Component::getComponentTypeID<T>() == component_type_id;
                            }),
                         components.end());
        components_array[component_type_id] = nullptr;
        components_mask[component_type_id] = false;
    }
};

class System
{
public:
    virtual ~System() {}

    virtual void init() = 0;
    virtual void update(float delta_time) = 0;
};

class Manager
{
public:
    virtual ~Manager() {}

    virtual void update(float delta_time) = 0;
};

#endif // !ECS_H
