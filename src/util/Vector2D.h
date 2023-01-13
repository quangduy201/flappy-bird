#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <ostream>

class Vector2D
{
public:
    float x;
    float y;

    Vector2D();
    Vector2D(float x, float y);
    virtual ~Vector2D();

    Vector2D &add(Vector2D const &v);
    Vector2D &subtract(Vector2D const &v);
    Vector2D &multiply(Vector2D const &v);
    Vector2D &divide(Vector2D const &v);

    friend Vector2D &operator+(Vector2D &v1, Vector2D const &v2);
    friend Vector2D &operator-(Vector2D &v1, Vector2D const &v2);
    friend Vector2D &operator*(Vector2D &v1, Vector2D const &v2);
    friend Vector2D &operator/(Vector2D &v1, Vector2D const &v2);

    Vector2D &operator+=(Vector2D const &vec);
    Vector2D &operator-=(Vector2D const &vec);
    Vector2D &operator*=(Vector2D const &vec);
    Vector2D &operator/=(Vector2D const &vec);

    Vector2D& operator*(const int& i);
	Vector2D& zero();

	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);
};

#endif // !VECTOR2D_H
