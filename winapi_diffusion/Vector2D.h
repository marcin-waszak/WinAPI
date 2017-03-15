#pragma once

template <typename T>
struct Vector2D
{
	T x;
	T y;

	Vector2D()
	{
		this->x = 0;
		this->y = 0;
	}

	Vector2D(T x, T y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2D<T>& operator+=(const Vector2D<T>& other)
	{
		this->x += other.x;
		this->y += other.y;

		return *this;
	}

	Vector2D<T> operator+(const Vector2D<T>& rhs)
	{
		return *this += rhs;
	}

	Vector2D<T> operator+(const Vector2D<T>& rhs) const
	{
		return Vector2D<T>(this->x + rhs.x, this->y + rhs.y);
	}
};