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
	BOOL left_owner_;
	double radius_;
	Vector2D<double> position_;
	Vector2D<double> velocity_;

public:
	Ball(BOOL left_owner, double radius, Vector2D<double> position, Vector2D<double> velocity);
	Ball(BOOL left_owner, double radius, double px, double py, double vx, double vy);
	BOOL GetLeftOwner() const;
	const Vector2D<double>& GetPosition() const;
	const Vector2D<double>& GetVelocity() const;
	Vector2D<double> GetCenter(int position = D_MIDDLE) const;
	void SetLeftOwner(BOOL left_owner);
	void SetRadius(double radius);
	void SetCenter(Vector2D<double> position);
	void SetVelocity(Vector2D<double> velocity);
	BOOL HandleCollision(HWND hWnd, HDC hdc, BOOL bLeft, std::vector<Ball>* balls);
	void Move();
	void Draw(HDC hdc) const;
	~Ball();
};
