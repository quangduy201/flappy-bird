#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL2/SDL.h>
#include <vector>

class Animation
{
public:
    std::vector<SDL_Rect> frames;
    float current_frame;
    float time;

    Animation() {}
    Animation(std::vector<SDL_Rect> frames, float time) : frames(frames), time(time), current_frame(0) {}

    void update(float delta_time)
    {
        current_frame += delta_time / time;
        if (current_frame >= frames.size())
            current_frame = 0;
    }

    SDL_Rect getCurrentFrame()
    {
        return frames[(int)current_frame];
    }
};

#endif // !ANIMATION_H
