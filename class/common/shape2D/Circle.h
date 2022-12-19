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
	/// �~�̔��a��ݒ肷��(�}�C�i�X�̏ꍇ�̓v���X�ɂȂ�);
	/// </summary>
	/// <param name="radius">���a</param>
	void SetRadius(float radius);
	/// <summary>
	/// �~�̔��a��Ԃ�
	/// </summary>
	/// <returns>�~�̔��a</returns>
	const float& GetRadius(void)const;
private:
	float radius_;

};

