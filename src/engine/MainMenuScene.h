#ifndef MAINMENU_SCENE_H
#define MAINMENU_SCENE_H

#include "../util/Utils.h"
#include "ECS.h"
#include "Scene.h"
#include "../components/Components.h"
#include <SDL2/SDL.h>

class MainMenuScene : public Scene
{
public:
    EntityID birdID;
    EntityID backgroundID;
    EntityID groundID;

    MainMenuScene(std::string name) : Scene(name) {}
    ~MainMenuScene() {}

    void init() override
    {
        // Camera
        camera.w = BACKGROUND_PIXEL_WIDTH;
        camera.h = BACKGROUND_PIXEL_HEIGHT;

        // Background
        backgroundID = entity_manager.createEntity();
        auto &background = entity_manager.entities[backgroundID];
        background->addComponent<TransformComponent>(0.0f, 0.0f);
        background->addComponent<RigidBodyComponent>(1.0f, 0.0f);
        auto &background_sprite = background->addComponent<SpriteComponent>("res/image/flappy-bird-sprite.png");

        std::vector<SDL_Rect> background_frames;
        background_frames.push_back({ 0, 0, BACKGROUND_PIXEL_WIDTH, BACKGROUND_PIXEL_HEIGHT });
        background_sprite.addAnimation("background", background_frames, 0.05f);
        background_sprite.play("background");
        background_sprite.width = BACKGROUND_PIXEL_WIDTH * IMAGE_SCALE;
        background_sprite.height = BACKGROUND_PIXEL_HEIGHT * IMAGE_SCALE;

        // Bird
        birdID = entity_manager.createEntity();
        auto &bird = entity_manager.entities[birdID];
        bird->addComponent<TransformComponent>(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
        bird->addComponent<RigidBodyComponent>(1.0f, 0.5f);
        auto &bird_sprite = bird->addComponent<SpriteComponent>("res/image/flappy-bird-sprite.png");

        std::vector<SDL_Rect> bird_frames;
        bird_frames.push_back({ 3, 491, BIRD_PIXEL_WIDTH, BIRD_PIXEL_HEIGHT });
        bird_frames.push_back({ 31, 491, BIRD_PIXEL_WIDTH, BIRD_PIXEL_HEIGHT });
        bird_frames.push_back({ 59, 491, BIRD_PIXEL_WIDTH, BIRD_PIXEL_HEIGHT });
        bird_sprite.addAnimation("flap", bird_frames, 0.0175f);
        bird_sprite.play("flap");
        bird_sprite.width = BIRD_PIXEL_WIDTH * IMAGE_SCALE;
        bird_sprite.height = BIRD_PIXEL_HEIGHT * IMAGE_SCALE;

        // Ground
        groundID = entity_manager.createEntity();
        auto &ground = entity_manager.entities[groundID];
        ground->addComponent<TransformComponent>(0, 550);
        auto &ground_sprite = ground->addComponent<SpriteComponent>("res/image/flappy-bird-sprite.png");

        std::vector<SDL_Rect> ground_frames;
        ground_frames.push_back({ 292, 0, GROUND_PIXEL_WIDTH, GROUND_PIXEL_HEIGHT });
        ground_sprite.addAnimation("ground", ground_frames, 0.05f);
        ground_sprite.play("ground");
        ground_sprite.width = GROUND_PIXEL_WIDTH * IMAGE_SCALE;
        ground_sprite.height = GROUND_PIXEL_HEIGHT * IMAGE_SCALE;
    }

    void update(float delta_time) override
    {
        auto &bird = entity_manager.entities[birdID];
        auto &background = entity_manager.entities[backgroundID];
        bird->getComponent<TransformComponent>().speed = 1;
        background->getComponent<TransformComponent>().speed = 1;

        // bird->getComponent<RigidBodyComponent>().velocity.y += (-9.8f) * bird->getComponent<RigidBodyComponent>().gravity_scale;
        // bird->getComponent<TransformComponent>().position += bird->getComponent<RigidBodyComponent>().velocity * delta_time;
        // background->getComponent<TransformComponent>().position += background->getComponent<RigidBodyComponent>().velocity * delta_time;
        camera.setPosition(background->getComponent<TransformComponent>().position);

        entity_manager.update(delta_time);
    }

    void render() override
    {
        entity_manager.render();
    }

    void handleEvents() override
    {
    }
};

#endif // !MAINMENU_SCENE_H
