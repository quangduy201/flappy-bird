#ifndef PLAY_SCENE_H
#define PLAY_SCENE_H

#include "ECS.h"
#include "Scene.h"
#include "../components/Components.h"
#include "../entities/Entities.h"

class PlayScene : public Scene
{
public:
    EntityID birdID;
    EntityID backgroundID;
    EntityID groundID;
    EntityID obstacleID;

    PlayScene(std::string name) : Scene(name) {}
    ~PlayScene() {}

    void init() override
    {
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
        bird_sprite.addAnimation("flap", bird_frames, 0.05f);
        bird_sprite.play("flap");
        bird_sprite.width = 17;
        bird_sprite.height = 12;

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
        background_sprite.width = 144;
        background_sprite.height = 256;

        // Ground
        groundID = entity_manager.createEntity();
        auto &ground = entity_manager.entities[groundID];
        ground->addComponent<TransformComponent>(0, 500);
        auto &ground_sprite = ground->addComponent<SpriteComponent>("res/image/flappy-bird-sprite.png");

        std::vector<SDL_Rect> ground_frames;
        ground_frames.push_back({ 292, 0, GROUND_PIXEL_WIDTH, GROUND_PIXEL_HEIGHT });
        ground_sprite.addAnimation("ground", ground_frames, 0.05f);
        ground_sprite.play("ground");
        ground_sprite.width = 168;
        ground_sprite.height = 56;

        // Obstacle
        obstacleID = entity_manager.createEntity();
        auto &obstacle = entity_manager.entities[obstacleID];

    }

    void update(float delta_time) override
    {
        auto &bird = entity_manager.entities[0];
        auto &background = entity_manager.entities[1];

        bird->getComponent<RigidBodyComponent>().velocity.y += (-9.8f) * bird->getComponent<RigidBodyComponent>().gravity_scale;
        bird->getComponent<TransformComponent>().position += bird->getComponent<RigidBodyComponent>().velocity * delta_time;
        background->getComponent<TransformComponent>().position += background->getComponent<RigidBodyComponent>().velocity * delta_time;
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

    void cleanUp() override
    {
    }
};

#endif // !PLAY_SCENE_H
