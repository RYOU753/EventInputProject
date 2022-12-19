#include "Shape.h"
#include "Box.h"
#include "Collision.h"

Shape::Shape(Position2F basePos)
	:basePos_(basePos) 
{
	col_ = new FlexibleCollision();
}

const Position2F& Shape::GetBasePos(void)const
{
	return basePos_;
}

void Shape::SetBasePos(Position2F pos)
{
	basePos_ = pos;
}

bool Shape::IsHit(Shape* shape)
{
	return col_->IsHitObject(*this,*shape);
}

bool Shape::IsHit(Position2 pos, bool inLine)
{
	return false;
}
