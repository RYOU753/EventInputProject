#pragma once
#include <DxLib.h>
#include <memory>
#include <optional>
#include "Input.h"
#include "../common/Vector2.h"

class PadInput:public Input
{
public:
	PadInput(int padNo);
	~PadInput();

	void Update(void)override;

	/// @brief ���͋@��̃^�C�v���擾
	/// @return ���͋@��^�C�v
	InputType GetInputType(void)const override { return InputType::Pad; };

	/// @brief �{�^���̏�Ԃ��擾����
	/// @param keyid enum����string�ɕϊ�����keyid
	/// @return �{�^�����
	InputState GetInputState(std::string keyid)override;

	/// @brief �A�i���O�l�̎擾����
	/// @param keyid enum����string�ɕϊ�����keyid
	/// @return �A�i���O�l
	float GetAnalogData(std::string keyid)override;

	/// @brief �X�e�B�b�N�̓|���������̊p�x���擾����
	/// @param dir �w�肷��X�e�B�b�N
	/// @return �������0�x�Ƃ��Ď��v����360�x�܂ł̊Ԃ�Ԃ�(�x���@)(�|��ĂȂ����C�����l��Ԃ�)
	std::optional<float> GetDirRot(Stick_LR dir);

	/// @brief �X�e�B�b�N�̓|�����x�N�g����Ԃ�
	/// @param dir �w�肷��X�e�B�b�N
	/// @return 0~1�̓|�����l(DeadZone�̒���������(0,0)�ŕԂ�)
	Vector2F GetMoveVec(Stick_LR dir);

	/// @brief 0~0.999�̊ԂŃf�b�h�]�[����ݒ肷��
	/// @param zone 0~1�̒l(�͈͊O�̒l��clamp�����)
	void SetDeadZone(float zone)override;

	/// @brief ���͂����邩
	/// @return ���͂���:true ���͂Ȃ�:false
	bool IsActive(void)override;
private:
	/// @brief �C���X�^���X���ł̏����� 
	void InInit(void)override;

	/// @brief �{�^���Ȃǂ�bool�Ō��܂���͂��X�V����
	void UpdateDigital(void);

	/// @brief �X�e�B�b�N��|���Ă��邩���X�V����
	void UpdateStickDigitalButton(void);

	/// @brief �X�e�B�b�N���͂�g���K�[�̐[�x�Ȃǂ̃A�i���O���͂��X�V����
	void UpdateAnalog(void);

	/// @brief �X�e�B�b�N�̓|���������̊p�x��Ԃ�
	/// @param x �X�e�B�b�N�̉���
	/// @param y �X�e�B�b�N�̏c��
	/// @return �������0�x�Ƃ��Ď��v����360�x�܂ł̊Ԃ�Ԃ�(�|��ĂȂ����C�����l��Ԃ�)
	std::optional<float> GetMoveDirRot(short x, short y);
	
	/// @brief �X�e�B�b�N�̏c���̓|�������̒l��0~1�̊Ԃɐ��K�������l��Ԃ�
	/// @param x �X�e�B�b�N�̉���
	/// @param y �X�e�B�b�N�̏c��
	/// @return 0~1�̓|�����l(DeadZone�̒���������(0,0)�ŕԂ�)
	Vector2F GetMoveVec(short x, short y);

	/// @brief �f�b�h�]�[�����Ȃ�[���ɂ���
	/// @param in �␳����X�e�B�b�N�̓|�����x�N�g��
	/// @return �␳��̃X�e�B�b�N�̓|�����x�N�g��
	Vector2F CorrectDeadZone(Vector2F in);

	/// @brief �f�o�b�O�\��
	void DebugDraw(void);

	const int padNo_;										//�p�b�h�̌̔ԍ�
	XINPUT_STATE xInput_;									//XInput�̃f�[�^���󂯎��ϐ�
	XPadData padData_;										//Pad�̓��͕ۊǏꏊ
	std::unordered_map<PadInputID, unsigned int> btnTbl_;	//PadInputID��Dxlib�̃p�b�h�̃r�b�g���e�[�u����
	Vector2F oldCursorPos_;									//�J�[�\���ʒu�̑O�t���[���̍��W
	std::pair<int, int> ConnectNum_;						//�p�b�h�̐ڑ���� fierst:Now,second:Old
	int isConnectXPad_;										//�p�b�h�������Ȃ����Ă��邩
};

