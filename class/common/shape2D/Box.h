#pragma once
#include "Shape.h"

enum class BOX_PLACE_TYPE
{
	LT,//����
	LB,//����
	RT,//�E��
	RB,//�E��
	CT,//��ӂ̒���
	CB,//���ӂ̒���
	CL,//���ӂ̒���
	CR,//�E�ӂ̒���
	CC,//�l�p�̒��S
	MAX
};

class Box :
    public Shape
{
public:
	Box(BOX_PLACE_TYPE placeType, Position2F pos, Vector2F size);
	~Box();
	//���g�̌`�̃^�C�v���擾����
	ShapeType GetShapeType(void)const override;
	//DEBUG����Box��`�悷��
	void dbgDraw(int color, bool isFill = true)const override;
	//Box��`�悷��
	void Draw(int color, bool isFill = true)const override;
	/// <summary>
	/// �w�肵�����W���擾����
	/// </summary>
	/// <param name="placeType">Box�̎擾�������ꏊ</param>
	/// <returns>�w�肵�����W</returns>
	Position2F GetSelectPos(BOX_PLACE_TYPE placeType)const;
	/// <summary>
	/// Box�̑傫����ݒ肷��
	/// </summary>
	/// <param name="size">(���C����)</param>
	void SetSize(Vector2F size);
	/// <summary>
	/// Box�̑傫�����擾����
	/// </summary>
	/// <returns>Box�̑傫��</returns>
	const Vector2F& GetSize(void)const;
	/// <summary>
	/// Box�̋N�_�ƂȂ�ꏊ��ύX����
	/// </summary>
	/// <param name="placeType">�N�_�ƂȂ�ꏊ��</param>
	void ChangeBasePosType(BOX_PLACE_TYPE placeType);
	const BOX_PLACE_TYPE& GetBasePosType(){
		return type_;
	};
	bool IsHit(Position2 pos,bool inLine)override;
private:
	Vector2F size_;
	BOX_PLACE_TYPE type_;
};

