#pragma once

#include "Vector2D.h"

class Ball
{
	Vector2D<double> position_;
	Vector2D<double> velocity_;

public:
	Ball(Vector2D<double> position, Vector2D<double> velocity);
	const Vector2D<double>& GetPosition() const;
	const Vector2D<double>& GetVelocity() const;
	void SetPosition(Vector2D<double> position);
	void SetVelocity(Vector2D<double> velocity);
	void Tick();
	~Ball();
};
