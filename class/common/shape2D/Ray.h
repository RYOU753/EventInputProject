#pragma once
#include "Shape.h"
class Ray :
    public Shape
{
public:
	Ray(Position2F p, Vector2F d) :pos(p), vec(d) {};
	~Ray() {};
	ShapeType GetShapeType(void)const override { return ShapeType::Ray; };
	void dbgDraw(int color)const override{_dbgDrawLine(static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(end().x),static_cast<int>(end().y), color);};
	void Draw(int color)const override{DrawLine(static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(end().x), static_cast<int>(end().y), color);};
	Position2F end(void) const{ return { pos.x + vec.x, pos.y + vec.y }; };//終点
	Position2F pos;//始点
	Vector2F vec;//方向ベクトル	
};

