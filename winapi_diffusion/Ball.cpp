#include "stdafx.h"
#include "Ball.h"

Ball::Ball(BOOL left_owner, int radius, Vector2D<int> position, Vector2D<int> velocity)
	: left_owner_(left_owner), radius_(radius), velocity_(velocity)
{
	SetCenter(position);
	need_pass_ = FALSE;
	need_erase_ = FALSE;
}

Ball::Ball(BOOL left_owner, int radius, int px, int py, int vx, int vy)
	: left_owner_(left_owner), radius_(radius), velocity_(Vector2D<int>(vx, vy))
{
	SetCenter(Vector2D<int>(px, py));
	need_pass_ = FALSE;
	need_erase_ = FALSE;
}

BOOL Ball::GetLeftOwner() const
{
	return left_owner_;
}

BOOL Ball::NeedPass() const
{
	return need_pass_;
}

BOOL Ball::NeedErase() const
{
	return need_erase_;
}

const Vector2D<int>& Ball::GetPosition() const
{
	return position_;
}

const Vector2D<int>& Ball::GetVelocity() const
{
	return velocity_;
}

Vector2D<int> Ball::GetCenter(int position) const
{
	switch (position) {
	case D_TOP:
		return position_ + Vector2D<int>(radius_, 2*radius_);

	case D_BOTTOM:
		return position_ + Vector2D<int>(radius_, 0);

	case D_LEFT:
		return position_ + Vector2D<int>(0, radius_);

	case D_RIGHT:
		return position_ + Vector2D<int>(2 * radius_, radius_);

	case D_MIDDLE:
	default:
		return position_ + Vector2D<int>(radius_, radius_);
	}

	return Vector2D<int>();
}

void Ball::SetLeftOwner(BOOL left_owner)
{
	left_owner_ = left_owner;
}

void Ball::SetRadius(int radius)
{
	radius_ = radius;
}

void Ball::SetCenter(Vector2D<int> position)
{
	position_ = position + Vector2D<int>(-radius_, -radius_);
}

void Ball::SetVelocity(Vector2D<int> velocity)
{
	velocity_ = velocity;
}

void Ball::HandleCollision(HWND hWnd, HDC hdc, BOOL bLeft, std::vector<Ball>* balls)
{
	RECT rectangle;
	SetMapMode(hdc, MM_LOMETRIC);
	GetClientRect(WindowFromDC(hdc), &rectangle);
	DPtoLP(hdc, (LPPOINT)&rectangle, 2);

	if (GetCenter(D_TOP).y > rectangle.top)
		velocity_.y *= -1;

	if (GetCenter(D_BOTTOM).y < rectangle.bottom)
		velocity_.y *= -1;

	if (bLeft)
	{
		if (GetCenter(D_MIDDLE).x > rectangle.right)
		{
			need_pass_ = TRUE;
//			return;
		}

		if (GetCenter(D_LEFT).x < rectangle.left)
			velocity_.x *= -1;
	}
	else
	{
		if (GetCenter(D_RIGHT).x > rectangle.right)
			velocity_.x *= -1;

		if (GetCenter(D_MIDDLE).x < rectangle.left)
		{
			need_pass_ = TRUE;
//			return;
		}
	}

	if (!need_pass_)
		return;

	if (bLeft)
	{
		if (GetCenter(D_LEFT).x > rectangle.right)
		{
			need_erase_ = TRUE;
			return;
		}
	}
	else
	{
		if (GetCenter(D_RIGHT).x < rectangle.left)
		{
			need_erase_ = TRUE;
			return;
		}
	}
}

void Ball::Move()
{
	position_ += velocity_;
}

void Ball::Draw(HDC hdc) const
{
	int x = position_.x;
	int y = position_.y;
	Ellipse(hdc, x, y, x + 2 * radius_, y + 2 * radius_);
}

Ball::~Ball()
{

}
