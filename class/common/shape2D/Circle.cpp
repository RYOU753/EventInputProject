#include <DxLib.h>
#include "Circle.h"
#include "../../_debug/_DebugDispOut.h"

void Circle::dbgDraw(int color, bool isFill) const
{
	_dbgDrawCircle(static_cast<int>(basePos_.x), static_cast<int>(basePos_.y), static_cast<int>(radius_), color, isFill);
}

void Circle::Draw(int color, bool isFill) const
{
	DrawCircle(static_cast<int>(basePos_.x), static_cast<int>(basePos_.y), static_cast<int>(radius_), color, isFill);
}

ShapeType Circle::GetShapeType(void) const
{
	return ShapeType::Circle; 
}

void Circle::SetRadius(float radius)
{
	radius_ = radius;
}

const float& Circle::GetRadius(void) const
{
	return radius_;
}
