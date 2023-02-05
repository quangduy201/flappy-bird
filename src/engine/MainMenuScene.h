#ifndef MAINMENU_SCENE_H
#define MAINMENU_SCENE_H

#include "../util/Utils.h"
#include "ECS.h"
#include "Scene.h"
#include "../components/Components.h"
#include <SDL2/SDL.h>
#include <queue>

class MainMenuScene : public Scene
{
public:
    EntityID birdID;
    EntityID backgroundID;
    std::queue<EntityID> groundIDs;

    MainMenuScene(std::string name) : Scene(name) {}
    ~MainMenuScene() {}

    void init() override
    {
        // Camera
        camera = { SCREEN_WIDTH, SCREEN_HEIGHT };

        // Background
        backgroundID = entity_manager.createEntity();
        auto &background = entity_manager.entities[backgroundID];
        auto &background_transform = background->addComponent<TransformComponent>(0.0f, 0.0f);
        auto &background_sprite = background->addComponent<SpriteComponent>("res/image/flappy-bird-sprite.png");

        std::vector<SDL_Rect> background_frames;
        background_frames.push_back({ 0, 0, BACKGROUND_PIXEL_WIDTH, BACKGROUND_PIXEL_HEIGHT });
        background_sprite.addAnimation("background", background_frames, 0.1f);
        background_sprite.play("background");
        background_sprite.width = BACKGROUND_PIXEL_WIDTH * IMAGE_SCALE;
        background_sprite.height = BACKGROUND_PIXEL_HEIGHT * IMAGE_SCALE;

        // Bird
        birdID = entity_manager.createEntity();
        auto &bird = entity_manager.entities[birdID];
        auto &bird_transform = bird->addComponent<TransformComponent>(SCREEN_WIDTH / 2 - BIRD_PIXEL_WIDTH * IMAGE_SCALE / 2.001f, SCREEN_HEIGHT / 2 - BIRD_PIXEL_HEIGHT * IMAGE_SCALE);
        // auto & bird_rigidbody = bird->addComponent<RigidBodyComponent>(0.0f, 0.0f);
        bird_transform.speed = 3.0f;
        // bird_rigidbody.gravity_scale = 9.8f;
        auto &bird_sprite = bird->addComponent<SpriteComponent>("res/image/flappy-bird-sprite.png");

        std::vector<SDL_Rect> bird_frames;
        bird_frames.push_back({ 59, 491, BIRD_PIXEL_WIDTH, BIRD_PIXEL_HEIGHT });
        bird_frames.push_back({ 31, 491, BIRD_PIXEL_WIDTH, BIRD_PIXEL_HEIGHT });
        bird_frames.push_back({ 3, 491, BIRD_PIXEL_WIDTH, BIRD_PIXEL_HEIGHT });
        bird_sprite.play("flap");
        bird_sprite.addAnimation("flap", bird_frames, 0.1f);
        bird_sprite.width = BIRD_PIXEL_WIDTH * IMAGE_SCALE;
        bird_sprite.height = BIRD_PIXEL_HEIGHT * IMAGE_SCALE;

        // Ground
        spawnNewGround(0, 2);
    }

    void update(float delta_time) override
    {
        auto &bird = entity_manager.entities[birdID];
        auto &background = entity_manager.entities[backgroundID];
        auto &ground = entity_manager.entities[groundIDs.front()];
        auto &ground_transform = ground->getComponent<TransformComponent>();
        auto &ground_sprite = ground->getComponent<SpriteComponent>();

        if (ground_transform.position.x + ground_sprite.width <= 0)
        {
            moveGround();
        }

        // bird_rigidbody.velocity.y += bird_rigidbody.gravity_scale;

        entity_manager.update(delta_time);
    }

    void render() override
    {
        entity_manager.render();
    }

    void handleEvents(SDL_Event &event) override
    {
        // auto &bird = entity_manager.entities[birdID];
        // auto &bird_rigidbody = bird->getComponent<RigidBodyComponent>();
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        running = false;
                    // if (event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_UP)
                    // {

                    // }
                    break;
                case SDL_QUIT:
                    running = false;
                    break;
                default:
                    break;
            }
        }
    }

    void spawnNewGround(int pop_ground, int push_ground)
    {
        for (int i = 0; i < pop_ground; ++i)
        {
            auto groundID = groundIDs.front();
            groundIDs.pop();
            entity_manager.destroyEntity(groundID);
        }
        float ground_position_x = 0.0f;
        for (int i = 0; i < push_ground; ++i)
        {
            auto groundID = entity_manager.createEntity();
            auto &ground = entity_manager.entities[groundID];
            auto &ground_transform = ground->addComponent<TransformComponent>(ground_position_x, 600.0f);
            ground->getComponent<TransformComponent>().speed = 1;
            auto &ground_rigidbody = ground->addComponent<RigidBodyComponent>(-150.0f, 0.0f);
            auto &ground_sprite = ground->addComponent<SpriteComponent>("res/image/flappy-bird-sprite.png");

            std::vector<SDL_Rect> ground_frames;
            ground_frames.push_back({ 292, 0, GROUND_PIXEL_WIDTH, GROUND_PIXEL_HEIGHT });
            ground_sprite.addAnimation("ground", ground_frames, 0.01f);
            ground_sprite.play("ground");
            ground_sprite.width = GROUND_PIXEL_WIDTH * IMAGE_SCALE;
            ground_sprite.height = GROUND_PIXEL_HEIGHT * IMAGE_SCALE;
            groundIDs.push(groundID);
            ground_position_x += ground_sprite.width;
        }
    }

    void moveGround()
    {
        auto groundID = groundIDs.front();
        groundIDs.pop();

        auto &last_ground = entity_manager.entities[groundIDs.back()];
        auto &last_ground_transform = last_ground->getComponent<TransformComponent>();
        auto &last_ground_sprite = last_ground->getComponent<SpriteComponent>();

        auto &new_ground = entity_manager.entities[groundID];
        auto &new_ground_transform = new_ground->getComponent<TransformComponent>();
        new_ground_transform.position.x = last_ground_transform.position.x + last_ground_sprite.width;

        groundIDs.push(groundID);
    }
};

#endif // !MAINMENU_SCENE_H
