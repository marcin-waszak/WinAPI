#pragma once

#include "Vector2D.h"
#include <vector>

#define D_MIDDLE	0
#define D_TOP		1
#define D_BOTTOM	2
#define D_LEFT		3
#define D_RIGHT		4

class Ball
{
	double radius_;
	Vector2D<double> position_;
	Vector2D<double> velocity_;

public:
	Ball(double radius, Vector2D<double> position, Vector2D<double> velocity);
	const Vector2D<double>& GetPosition() const;
	const Vector2D<double>& GetVelocity() const;
	Vector2D<double> GetCenter(int position = D_MIDDLE) const;
	void SetRadius(double radius);
	void SetPosition(Vector2D<double> position);
	void SetVelocity(Vector2D<double> velocity);
	void SetVelocity(double vx, double vy);
	void HandleCollision(HDC hdc, std::vector<Ball>* balls);
	void Move();
	void Draw(HDC hdc) const;
	~Ball();
};
