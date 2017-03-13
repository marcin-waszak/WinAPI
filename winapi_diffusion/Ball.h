#pragma once

#include "Vector2D.h"

class Ball
{
	double radius_;
	Vector2D<double> position_;
	Vector2D<double> velocity_;

public:
	Ball(double radius, Vector2D<double> position, Vector2D<double> velocity);
	const Vector2D<double>& GetPosition() const;
	const Vector2D<double>& GetVelocity() const;
	Vector2D<double> GetCenter() const;
	void SetRadius(double radius);
	void SetPosition(Vector2D<double> position);
	void SetVelocity(Vector2D<double> velocity);
	void Tick();
	void Draw(HDC hdc) const;
	~Ball();
};
