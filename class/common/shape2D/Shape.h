#pragma once
#include "../Vector2.h"

enum class ShapeType
{
	Ray,
	Box,
	Circle,
	Max
};
class Shape
{
public:
	Shape(Position2F basePos);

	virtual ~Shape() {};
	virtual void dbgDraw(int color = 0xffffff,bool isFill = true)const = 0;
	virtual void Draw(int color = 0xffffff, bool isFill = true)const = 0;
	virtual ShapeType GetShapeType(void)const = 0;
	const Position2F& GetBasePos(void)const;
	void SetBasePos(Position2F pos);
	bool IsHit(Shape* shape);
	virtual bool IsHit(Position2 pos, bool inLine);
	bool isHit_ = false;
	class FlexibleCollision* col_;
protected:
	Position2F basePos_;
};
