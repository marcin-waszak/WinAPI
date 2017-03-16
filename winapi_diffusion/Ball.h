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
	BOOL need_pass_;
	BOOL need_erase_;
	int radius_;
	Vector2D<int> position_;
	Vector2D<int> velocity_;

public:
	Ball(BOOL left_owner, int radius, Vector2D<int> position, Vector2D<int> velocity);
	Ball(BOOL left_owner, int radius, int px, int py, int vx, int vy);
	BOOL GetLeftOwner() const;
	BOOL NeedPass() const;
	BOOL NeedErase() const;
	const Vector2D<int>& GetPosition() const;
	const Vector2D<int>& GetVelocity() const;
	Vector2D<int> GetCenter(int position = D_MIDDLE) const;
	void SetLeftOwner(BOOL left_owner);
	void SetRadius(int radius);
	void SetCenter(Vector2D<int> position);
	void SetVelocity(Vector2D<int> velocity);
	void HandleCollision(HWND hWnd, HDC hdc, BOOL bLeft, std::vector<Ball>* balls);
	void Move();
	void Draw(HDC hdc) const;
	~Ball();
};
