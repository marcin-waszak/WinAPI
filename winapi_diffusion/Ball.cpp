#include "stdafx.h"
#include "Ball.h"

Ball::Ball(double radius, Vector2D<double> position, Vector2D<double> velocity)
	: radius_(radius), position_(position), velocity_(velocity)
{

}

const Vector2D<double>& Ball::GetPosition() const
{
	return position_;
}

const Vector2D<double>& Ball::GetVelocity() const
{
	return velocity_;
}

Vector2D<double> Ball::GetCenter(int position) const
{
	switch (position) {
	case D_TOP:
		return position_ + Vector2D<double>(radius_, 2*radius_);

	case D_BOTTOM:
		return position_ + Vector2D<double>(radius_, 0.0);

	case D_LEFT:
		return position_ + Vector2D<double>(0.0, radius_);

	case D_RIGHT:
		return position_ + Vector2D<double>(2 * radius_, radius_);

	case D_MIDDLE:
	default:
		return position_ + Vector2D<double>(radius_, radius_);
	}

	return Vector2D<double>(0.0, 0.0);
}

void Ball::SetRadius(double radius)
{
	radius_ = radius;
}

void Ball::SetPosition(Vector2D<double> position)
{
	position_ = position;
}

void Ball::SetVelocity(Vector2D<double> velocity)
{
	velocity_ = velocity;
}

void Ball::HandleCollision(HWND hWnd, std::vector<Ball>* balls)
{
	HDC hdc = (HDC)GetWindowLongPtr(hWnd, 0x02);
	RECT rectangle;
	SetMapMode(hdc, MM_LOMETRIC);
	GetClientRect(WindowFromDC(hdc), &rectangle);
	DPtoLP(hdc, (LPPOINT)&rectangle, 2);

	if (GetCenter(D_LEFT).x < rectangle.left)
		velocity_.x *= -1.0;

	if (GetCenter(D_RIGHT).x > rectangle.right)
		velocity_.x *= -1.0;

	if (GetCenter(D_TOP).y > rectangle.top)
		velocity_.y *= -1.0;

	if (GetCenter(D_BOTTOM).y < rectangle.bottom)
		velocity_.y *= -1.0;
}

void Ball::Move()
{
	position_ += velocity_;
}

void Ball::Draw(HDC hdc) const
{
	double x = position_.x;
	double y = position_.y;
	Ellipse(hdc, x, y, x + 2.0 * radius_, y + 2.0 * radius_);
}

Ball::~Ball()
{

}
