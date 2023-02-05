#ifndef PLAY_SCENE_H
#define PLAY_SCENE_H

#include "ECS.h"
#include "Scene.h"
#include "../components/Components.h"
#include "../entities/Entities.h"
#include <SDL2/SDL.h>
#include <queue>

class PlayScene : public Scene
{
public:
    EntityID birdID;
    EntityID backgroundID;
    std::queue<EntityID> groundIDs;
    std::queue<std::pair<EntityID, EntityID>> obstacleIDs;

    PlayScene(std::string name) : Scene(name) {}
    ~PlayScene() {}

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
        auto &bird_transform = bird->addComponent<TransformComponent>(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 - 2 * BIRD_PIXEL_HEIGHT * IMAGE_SCALE);
        auto & bird_rigidbody = bird->addComponent<RigidBodyComponent>(0.0f, 0.0f);
        bird_transform.speed = 3.0f;
        bird_rigidbody.gravity_scale = 9.8f;
        auto &bird_sprite = bird->addComponent<SpriteComponent>("res/image/flappy-bird-sprite.png");

        std::vector<SDL_Rect> bird_frames;
        bird_frames.push_back({ 59, 491, BIRD_PIXEL_WIDTH, BIRD_PIXEL_HEIGHT });
        bird_frames.push_back({ 31, 491, BIRD_PIXEL_WIDTH, BIRD_PIXEL_HEIGHT });
        bird_frames.push_back({ 3, 491, BIRD_PIXEL_WIDTH, BIRD_PIXEL_HEIGHT });
        bird_sprite.play("flap");
        bird_sprite.addAnimation("flap", bird_frames, 0.1f);
        bird_sprite.width = BIRD_PIXEL_WIDTH * IMAGE_SCALE;
        bird_sprite.height = BIRD_PIXEL_HEIGHT * IMAGE_SCALE;

        auto &bird_collider = bird->addComponent<ColliderComponent>();

        // Grounds
        // for (int i = 0; i < 5; ++i)
        // {
        //     auto groundID = entity_manager.createEntity();
        //     auto &ground = entity_manager.entities[groundID];
        //     auto &ground_transform = ground->addComponent<TransformComponent>(i * GROUND_PIXEL_WIDTH * IMAGE_SCALE, 600.0f);
        //     ground->getComponent<TransformComponent>().speed = 1;
        //     auto &ground_rigidbody = ground->addComponent<RigidBodyComponent>(-150.0f, 0.0f);
        //     auto &ground_sprite = ground->addComponent<SpriteComponent>("res/image/flappy-bird-sprite.png");

        //     std::vector<SDL_Rect> ground_frames;
        //     ground_frames.push_back({ 292, 0, GROUND_PIXEL_WIDTH, GROUND_PIXEL_HEIGHT });
        //     ground_sprite.addAnimation("ground", ground_frames, 0.01f);
        //     ground_sprite.play("ground");
        //     ground_sprite.width = GROUND_PIXEL_WIDTH * IMAGE_SCALE;
        //     ground_sprite.height = GROUND_PIXEL_HEIGHT * IMAGE_SCALE;
        //     groundIDs.push(groundID);
        // }
        spawnNewObstacle(0, 5);
        spawnNewGround(0, 2);
    }

    void update(float delta_time) override
    {
        auto &bird = entity_manager.entities[birdID];
        auto &background = entity_manager.entities[backgroundID];
        auto &ground = entity_manager.entities[groundIDs.front()];
        auto &obstacle_first = entity_manager.entities[obstacleIDs.front().first];
        auto &bird_rigidbody = bird->getComponent<RigidBodyComponent>();
        auto &ground_transform = ground->getComponent<TransformComponent>();
        auto &ground_sprite = ground->getComponent<SpriteComponent>();
        auto &obstacle_first_transform = obstacle_first->getComponent<TransformComponent>();
        auto &obstacle_first_sprite = obstacle_first->getComponent<SpriteComponent>();

        if (obstacle_first_transform.position.x + obstacle_first_sprite.width <= 0)
        {
            spawnNewObstacle(1, 1);
        }

        if (ground_transform.position.x + ground_sprite.width <= 0)
        {
            moveGround();
        }


        bird_rigidbody.velocity.y += bird_rigidbody.gravity_scale;

        entity_manager.update(delta_time);
    }

    void render() override
    {
        entity_manager.render();
        entity_manager.entities[groundIDs.front()]->getComponent<SpriteComponent>().render();
        entity_manager.entities[groundIDs.back()]->getComponent<SpriteComponent>().render();
    }

    void handleEvents(SDL_Event &event) override
    {
        auto &bird = entity_manager.entities[birdID];
        auto &bird_rigidbody = bird->getComponent<RigidBodyComponent>();
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        running = false;
                    if (event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_UP)
                        bird_rigidbody.velocity.y = -180.0f;
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
            // if (!groundIDs.empty())
            // {
            //     auto &last_ground_first = entity_manager.entities[groundIDs.back()];
            //     auto &last_ground_first_transform = last_ground_first->getComponent<TransformComponent>();
            //     auto &last_ground_first_sprite = last_ground_first->getComponent<SpriteComponent>();
            //     ground_position_x = last_ground_first_transform.position.x + last_ground_first_sprite.width;
            // }

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

            auto &ground_collider = ground->addComponent<ColliderComponent>();
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

    void spawnNewObstacle(int pop_obstacle, int push_obstacle)
    {
        for (int i = 0; i < pop_obstacle; ++i)
        {
            auto obstacle_pairID = obstacleIDs.front();
            obstacleIDs.pop();
            entity_manager.destroyEntity(obstacle_pairID.first);
            entity_manager.destroyEntity(obstacle_pairID.second);
        }
        float obstacle_position_x = 750.0f;
        for (int i = 0; i < push_obstacle; ++i)
        {
            if (!obstacleIDs.empty())
            {
                auto &last_obstacle_first = entity_manager.entities[obstacleIDs.back().first];
                auto &last_obstacle_first_transform = last_obstacle_first->getComponent<TransformComponent>();
                auto &last_obstacle_first_sprite = last_obstacle_first->getComponent<SpriteComponent>();
                obstacle_position_x = last_obstacle_first_transform.position.x + 250.0f;
            }
            float gap_y_position = rand() % (int)(SCREEN_HEIGHT - (GROUND_PIXEL_HEIGHT * IMAGE_SCALE) - GAP - 200) + 50;

            auto obstacle_firstID = entity_manager.createEntity();
            auto &obstacle_first = entity_manager.entities[obstacle_firstID];
            auto &obstacle_first_transform = obstacle_first->addComponent<TransformComponent>(obstacle_position_x, gap_y_position - OBSTACLE_PIXEL_HEIGHT * IMAGE_SCALE);
            obstacle_first->getComponent<TransformComponent>().speed = 1;
            auto &obstacle_first_rigidbody = obstacle_first->addComponent<RigidBodyComponent>(-150.0f, 0.0f);
            auto &obstacle_first_sprite = obstacle_first->addComponent<SpriteComponent>("res/image/flappy-bird-sprite.png");

            std::vector<SDL_Rect> obstacle_first_frames;
            obstacle_first_frames.push_back({ 56, 323, OBSTACLE_PIXEL_WIDTH, OBSTACLE_PIXEL_HEIGHT });
            obstacle_first_sprite.addAnimation("ground", obstacle_first_frames, 0.01f);
            obstacle_first_sprite.play("ground");
            obstacle_first_sprite.width = OBSTACLE_PIXEL_WIDTH * IMAGE_SCALE;
            obstacle_first_sprite.height = OBSTACLE_PIXEL_HEIGHT * IMAGE_SCALE;

            auto &obstacle_first_collider = obstacle_first->addComponent<ColliderComponent>();

            auto obstacle_secondID = entity_manager.createEntity();
            auto &obstacle_second = entity_manager.entities[obstacle_secondID];
            auto &obstacle_second_transform = obstacle_second->addComponent<TransformComponent>(obstacle_position_x, gap_y_position + GAP);
            obstacle_second->getComponent<TransformComponent>().speed = 1;
            auto &obstacle_second_rigidbody = obstacle_second->addComponent<RigidBodyComponent>(-150.0f, 0.0f);
            auto &obstacle_second_sprite = obstacle_second->addComponent<SpriteComponent>("res/image/flappy-bird-sprite.png");

            std::vector<SDL_Rect> obstacle_second_frames;
            obstacle_second_frames.push_back({ 84, 323, OBSTACLE_PIXEL_WIDTH, OBSTACLE_PIXEL_HEIGHT });
            obstacle_second_sprite.addAnimation("ground", obstacle_second_frames, 0.01f);
            obstacle_second_sprite.play("ground");
            obstacle_second_sprite.width = OBSTACLE_PIXEL_WIDTH * IMAGE_SCALE;
            obstacle_second_sprite.height = OBSTACLE_PIXEL_HEIGHT * IMAGE_SCALE;

            auto &obstacle_second_collider = obstacle_second->addComponent<ColliderComponent>();

            obstacleIDs.push(std::make_pair(obstacle_firstID, obstacle_secondID));
        }
    }
};

#endif // !PLAY_SCENE_H
