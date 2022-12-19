#pragma once
#include "Vector2.h"

class Transform2D
{
public:
	Transform2D(void);
	~Transform2D();
	//���WXY��ݒ�
	void SetPos(Position2F pos);
	//���WX��ݒ�
	void SetPosX(float x);
	//���WY��ݒ�
	void SetPosY(float y);
	//���W���擾
	const Position2F& GetPos(void);
	/// <summary>
	/// �x���@�̈�������]���� +�����E��] -��������]
	/// </summary>
	///<param name="deg">�ǉ�����l(�x���@)</param>
	void RotateDeg(float deg);
	/// <summary>
	/// �ʓx�@�̈�������]���� +�����E��] -��������]
	/// </summary>
	///<param name="rad">�ǉ�����l(�ʓx�@)</param>
	void RotateRad(float rad);
	//�x���@�Ŏw�肵���l��ݒ�
	///<param name="rotationDeg">�ǉ�����l(�x���@)</param>
	void SetRotationDeg(float rotationDeg);
	/// <summary>
	///�ʓx�@�Ŏw�肵���l��ݒ�
	/// </summary>
	///<param name="rotationRad">�ǉ�����l(�ʓx�@)</param>
	void SetRotationRad(float rotationRad);
	/// <summary>
	/// ��]�l���擾
	/// </summary>
	/// <returns>���W�A���l</returns>
	const float& GetRotation(void);
	//�g��l��ݒ�
	void SetScale(float scale);
	//�g��l���擾
	const float& GetScale(void);
private:
	Position2F position_;
	float rotation_;//���W�A���l
	float scale_;
};
