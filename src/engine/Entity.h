#ifndef ENTITY_H
#define ENTITY_H

#include "Component.h"
#include <vector>
#include <memory>

class Entity
{
private:
    std::vector<std::unique_ptr<Component>> components;
    int id;
    static int next_id;
public:
    Entity() : id(next_id++) {}
    virtual ~Entity() {}

    template <typename T>
    T* get()
    {
        for (auto& component : components)
        {
            if (T* result = dynamic_cast<T*>(component.get()))
            {
                return result;
            }
        }
        return nullptr;
    }

    template <typename T, typename... Args>
    void add(Args&&... args)
    {
        components.emplace_back(std::make_unique<T>(this, std::forward<Args>(args)...));
    }
};

#endif // !ENTITY_H
