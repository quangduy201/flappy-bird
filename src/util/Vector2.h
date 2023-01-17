#ifndef VECTOR2_H
#define VECTOR2_H

#include <SDL2/SDL.h>

class Vector2
{
public:
    float x;
    float y;

    Vector2(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

    Vector2 &operator+=(const Vector2 &v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }
    Vector2 &operator-=(const Vector2 &v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }
    Vector2 &operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    Vector2 &operator/=(float scalar)
    {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    Vector2 operator-() const
    {
        return Vector2(-x, -y);
    }
    Vector2 operator+(Vector2 &v) const
    {
        return Vector2(*this) += v;
    }
    Vector2 operator-(Vector2 &v) const
    {
        return Vector2(*this) -= v;
    }
    Vector2 operator*(float scalar) const
    {
        return Vector2(*this) *= scalar;
    }
    Vector2 operator/(float scalar) const
    {
        return Vector2(*this) /= scalar;
    }

    float magnitude() const
    {
        return SDL_sqrtf(x * x + y * y);
    }
    Vector2 normalized() const
    {
        return *this / magnitude();
    }
    void normalize()
    {
        *this /= magnitude();
    }
    float dot(const Vector2 &v) const
    {
        return x * v.x + y * v.y;
    }
    float cross(const Vector2 &v) const
    {
        return x * v.y - y * v.x;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector2& v)
    {
        os << "(" << v.x << "," << v.y << ")";
        return os;
    }
};

#endif // !VECTOR2_H
