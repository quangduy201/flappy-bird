#include <util/Vector2D.h>

Vector2D::Vector2D() : x(0.0f), y(0.0f) {}
Vector2D::Vector2D(float x, float y) : x(x), y(y) {}
Vector2D::~Vector2D() {}

Vector2D &Vector2D::add(Vector2D const &v)
{
	this->x += v.x;
	this->y += v.y;
	return *this;
}
Vector2D &Vector2D::subtract(Vector2D const &v)
{
	this->x -= v.x;
	this->y -= v.y;
	return *this;
}
Vector2D &Vector2D::multiply(Vector2D const &v)
{
	this->x *= v.x;
	this->y *= v.y;
	return *this;
}
Vector2D &Vector2D::divide(Vector2D const &v)
{
	this->x /= v.x;
	this->y /= v.y;
	return *this;
}

Vector2D &operator+(Vector2D &v1, Vector2D const &v2)
{
	return v1.add(v2);
}
Vector2D &operator-(Vector2D &v1, Vector2D const &v2)
{
	return v1.subtract(v2);
}
Vector2D &operator*(Vector2D &v1, Vector2D const &v2)
{
	return v1.multiply(v2);
}
Vector2D &operator/(Vector2D &v1, Vector2D const &v2)
{
	return v1.divide(v2);
}

Vector2D &Vector2D::operator+=(Vector2D const &v)
{
	return this->add(v);
}
Vector2D &Vector2D::operator-=(Vector2D const &v)
{
	return this->subtract(v);
}
Vector2D &Vector2D::operator*=(Vector2D const &v)
{
	return this->multiply(v);
}
Vector2D &Vector2D::operator/=(Vector2D const &v)
{
	return this->divide(v);
}

Vector2D &Vector2D::operator*(int const &i)
{
	this->x *= i;
	this->y *= i;
	return *this;
}
Vector2D &Vector2D::zero()
{
	this->x = 0.0f;
	this->y = 0.0f;
	return *this;
}

std::ostream &operator<<(std::ostream &stream, Vector2D const &v)
{
	stream << "(" << v.x << "," << v.y << ")";
	return stream;
}
