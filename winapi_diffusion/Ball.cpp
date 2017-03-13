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

Vector2D<double> Ball::GetCenter() const
{
	return position_ + Vector2D<double>(0.5 * radius_, 0.5 * radius_);
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

void Ball::Tick()
{
	position_ += velocity_;
}

void Ball::Draw(HDC hdc) const
{
	double x = position_.x;
	double y = position_.y;
	Ellipse(hdc, x, y, x + radius_, y + radius_);
}

Ball::~Ball()
{

}
