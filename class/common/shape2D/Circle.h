#pragma once
#include "Shape.h"
class Circle :
    public Shape
{
public:
	Circle(Position2F center,float radius):Shape(center), radius_(radius) {};
	void dbgDraw(int color = 0xffffff, bool isFill = true)const;
	void Draw(int color = 0xffffff, bool isFill = true)const;
	ShapeType GetShapeType(void)const;

	/// <summary>
	/// 円の半径を設定する(マイナスの場合はプラスになる);
	/// </summary>
	/// <param name="radius">半径</param>
	void SetRadius(float radius);
	/// <summary>
	/// 円の半径を返す
	/// </summary>
	/// <returns>円の半径</returns>
	const float& GetRadius(void)const;
private:
	float radius_;

};

