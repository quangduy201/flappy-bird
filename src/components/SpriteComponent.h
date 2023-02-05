#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "../engine/ECS.h"
#include "../engine/Animation.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include "../engine/TextureManager.h"
#include "../components/TransformComponent.h"

class SpriteComponent : public Component
{
public:
    SDL_Texture *texture;
    int width;
    int height;
    std::unordered_map<std::string, Animation> animations;
    std::string current_animation;
    bool is_animated;

    SpriteComponent() {}
    SpriteComponent(const std::string &path)
    {
        texture = TextureManager::LoadTexture(path);
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    }
    ~SpriteComponent() {}

    void addAnimation(const std::string &name, std::vector<SDL_Rect> frames, float time)
    {
        animations[name] = Animation(frames, time);
    }

    void play(const std::string &name)
    {
        current_animation = name;
    }

    void init() override
    {

    }

    void update(float delta_time) override
    {
        animations[current_animation].update(delta_time);
    }

    void render() override
    {
        if (!entity->hasComponents<TransformComponent>())
            return;
        auto &transform = entity->getComponent<TransformComponent>();
        SDL_FRect dst_rect = { transform.position.x, transform.position.y, width * 1.0f, height * 1.0f };
        TextureManager::Draw(texture, animations[current_animation].getCurrentFrame(), dst_rect, transform.rotation, nullptr, SDL_FLIP_NONE);
    }
};

#endif // !SPRITE_COMPONENT_H
