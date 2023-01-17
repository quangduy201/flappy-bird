#ifndef MAINMENU_SCENE_H
#define MAINMENU_SCENE_H

#include "../util/Utils.h"
#include "ECS.h"
#include "Scene.h"
#include "../components/Components.h"
// #include "../entities/Entities.h"
#include <SDL2/SDL.h>

class MainMenuScene : public Scene
{
public:
    EntityID birdID;
    EntityID backgroundID;
    EntityID groundID;

    MainMenuScene(std::string name, SDL_Renderer *renderer) : Scene(name, renderer) {}
    ~MainMenuScene() {}

    void init() override
    {
        // Bird
        birdID = entity_manager.createEntity();
        auto &bird = entity_manager.entities[birdID];
        bird->addComponent<TransformComponent>(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
        bird->addComponent<RigidBodyComponent>(1.0f, 0.5f);
        auto &bird_sprite = bird->addComponent<SpriteComponent>("../../res/image/flappy-bird-sprite.png");

        std::vector<SDL_Rect> bird_frames;
        bird_frames.push_back({ 3, 491, 17, 12 });
        bird_frames.push_back({ 31, 491, 17, 12 });
        bird_frames.push_back({ 59, 491, 17, 12 });
        bird_sprite.addAnimation("flap", bird_frames, 0.1f);
        bird_sprite.play("flap");

        // Background
        backgroundID = entity_manager.createEntity();
        auto &background = entity_manager.entities[backgroundID];
        background->addComponent<TransformComponent>(0.0f, 0.0f);
        background->addComponent<RigidBodyComponent>(1.0f, 0.0f);
        auto &background_sprite = background->addComponent<SpriteComponent>("../../res/image/flappy-bird-sprite.png");

        std::vector<SDL_Rect> background_frames;
        background_frames.push_back({ 0, 0, 144, 256 });
        background_sprite.addAnimation("background", background_frames, 0.1f);
        background_sprite.play("background");

        // Ground
        groundID = entity_manager.createEntity();
        auto &ground = entity_manager.entities[groundID];
        ground->addComponent<TransformComponent>(0, 500);
        auto &ground_sprite = ground->addComponent<SpriteComponent>("../../res/image/flappy-bird-sprite.png");

        std::vector<SDL_Rect> ground_frames;
        ground_frames.push_back({ 292, 0, 168, 56 });
        ground_sprite.addAnimation("ground", ground_frames, 0.1f);
        ground_sprite.play("ground");
    }

    void update(float delta_time) override
    {
        // Update any necessary systems for the main menu scene
        auto &bird = entity_manager.entities[birdID];
        auto &background = entity_manager.entities[backgroundID];

        bird->getComponent<RigidBodyComponent>().velocity.y += (-9.8f) * bird->getComponent<RigidBodyComponent>().gravity_scale;
        bird->getComponent<TransformComponent>().position += bird->getComponent<RigidBodyComponent>().velocity * delta_time;
        background->getComponent<TransformComponent>().position += background->getComponent<RigidBodyComponent>().velocity * delta_time;
        camera.setPosition(background->getComponent<TransformComponent>().position);

        std::cout << bird->getComponent<TransformComponent>().position << std::endl;
        std::cout << bird->getComponent<RigidBodyComponent>().velocity << std::endl;

        entity_manager.update(delta_time);
    }

    void render() override
    {
        // Render the main menu scene
        entity_manager.render();
    }

    void handleEvents() override
    {
        // Cleanup any resources used by the main menu scene
    }
};

#endif // !MAINMENU_SCENE_H
