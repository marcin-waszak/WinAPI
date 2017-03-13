#include "stdafx.h"
#include "Ball.h"

Ball::Ball(Vector2D<double> position, Vector2D<double> velocity)
	: position_(position), velocity_(velocity)
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
	position_ += Vector2D<double>(1.0, 1.0);
}

Ball::~Ball()
{
}
