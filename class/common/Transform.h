#pragma once
#include <DxLib.h>
#include <optional>
#include "Quaternion.h"
//#if __has_include("../jsonConvert/TransPtr_JSON.h")
//	#include "../jsonConvert/TransPtr_JSON.h"
//#endif
//#if __has_include("../jsonConvert/TransUniPtr_JSON.h")
//	#include "../jsonConvert/TransUniPtr_JSON.h"
//#endif

/// <summary>
/// ���f������̊�{���
/// �傫���FVECTOR�
/// ��]�@�FQuaternion�
/// �ʒu�@�FVECTOR�
/// </summary>
class Transform
{

public:
	Transform(void);
	Transform(VECTOR pos, Quaternion qRot, VECTOR scale, Quaternion qRotLocal = Quaternion{});
	~Transform();

	//�傫�����Z�b�g
	void SetScale(VECTOR scl);
	//���W���Z�b�g
	void SetPosition(VECTOR pos);
	//��]���Z�b�g
	void SetQuaternionRot(Quaternion qua);
	//X��������]
	void SetRotX(float rotx);
	//Y��������]
	void SetRotY(float roty);
	//Z��������]
	void SetRotZ(float rotz);
	void SetQuaternionRotLocal(Quaternion quaLocal);

	//X��������](���[�J��)
	void SetRotLocalX(const float& rotx);
	//Y��������](���[�J��)
	void SetRotLocalY(const float& roty);
	//Z��������](���[�J��)
	void SetRotLocalZ(const float& rotz);
	//�傫�����擾
	const VECTOR& GetScale(void) const{ return scl; };
	//���W���擾
	const VECTOR& GetPosition(void) const { return pos; };
	//��]���擾
	Quaternion GetQuaternionRot(void) { return quaRot; };
	const Quaternion& GetQuaternionLocalRot(void)const { return quaRotLocal; };

	// �O���������擾
	const VECTOR&& GetForward(void);

	// ����������擾
	const VECTOR&& GetBack(void);

	// �E�������擾
	const VECTOR&& GetRight(void);

	// ���������擾
	const VECTOR&& GetLeft(void);

	// ��������擾
	const VECTOR&& GetUp(void);

	// ���������擾
	const VECTOR&& GetDown(void);

	// �Ώە������擾
	const VECTOR&& GetDir(VECTOR vec);

public:
private:
	// �傫��
	VECTOR scl;
	// ��]
	VECTOR rot;
	// �ʒu
	VECTOR pos;

	MATRIX matScl;
	MATRIX matRot;
	MATRIX matPos;
	MATRIX matAll;
	// ��]
	Quaternion quaRot;

	// ���[�J����]
	Quaternion quaRotLocal;
};

