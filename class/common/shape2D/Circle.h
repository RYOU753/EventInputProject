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
	/// ‰~‚Ì”¼Œa‚ğİ’è‚·‚é(ƒ}ƒCƒiƒX‚Ìê‡‚Íƒvƒ‰ƒX‚É‚È‚é);
	/// </summary>
	/// <param name="radius">”¼Œa</param>
	void SetRadius(float radius);
	/// <summary>
	/// ‰~‚Ì”¼Œa‚ğ•Ô‚·
	/// </summary>
	/// <returns>‰~‚Ì”¼Œa</returns>
	const float& GetRadius(void)const;
private:
	float radius_;

};

