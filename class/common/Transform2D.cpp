#include <DxLib.h>
#include "Transform2D.h"
#include "Utility.h"

Transform2D::Transform2D(void) :position_(0.0f, 0.0f), rotation_(0.0f), scale_(1.0f)
{
}

Transform2D::~Transform2D()
{
}

void Transform2D::SetPos(Position2F pos)
{
	position_ = pos;
}

void Transform2D::SetPosX(float x)
{
	position_.x = x;
}

void Transform2D::SetPosY(float y)
{
	position_.y = y;
}

const Position2F& Transform2D::GetPos(void)
{
	return position_;
}

void Transform2D::RotateDeg(float deg)
{
	RotateRad((deg / 360.0f) * DX_TWO_PI_F);
}

void Transform2D::RotateRad(float rad)
{
	rotation_ = utility::RadIn2PI()(rotation_ + rad);
}

void Transform2D::SetRotationDeg(float rotationDeg)
{
	SetRotationRad((rotationDeg / 360.0f) * DX_TWO_PI_F);
}

void Transform2D::SetRotationRad(float rotationRad)
{
	rotation_ = utility::RadIn2PI()(rotationRad);
}

const float& Transform2D::GetRotation(void)
{
	return rotation_;
}

void Transform2D::SetScale(float scale)
{
	scale_ = scale;
}

const float& Transform2D::GetScale(void)
{
	return scale_;
}
