#pragma once
#include <unordered_map>
#include <array>
#include <vector>
#include <string>
#include "PadInputID.h"
#include "AnalogInputID.h"
#include "MouseInputID.h"
#include "../common/Vector2.h"

enum class Trg {
	Now,	//���݂̃t���[��
	Old,	//1�t���[���O�̃t���[��
	Max
};
enum class InputType {
	Keybord,
	Pad,
	Max
};
enum class InputState
{
	None,	//�������ĂȂ�	now:false,old:false
	Push,	//�������u��	now:true,old:false
	Relese,	//�������u��	now:false,old:true
	Hold,	//�����Ă����	now:true,old:true
	Max
};
enum class Stick_LR
{
	L,
	R,
	Max
};
using TrgBool = std::unordered_map<Trg, bool>;//�ǂ̃^�C�~���O�̉�����Ă邩
using XPadData = std::unordered_map<PadInputID, TrgBool>;//������Ă�{�^���Ƃ������ꂽ��
using KeyState = std::array<char, 256U>;
using KeybordData = std::unordered_map<Trg,KeyState>;
using MouseData = std::unordered_map<MouseInputID, TrgBool>;
using AnalogData = std::unordered_map<AnalogInputID, float>;
using MousePointer = std::unordered_map<Trg, Vector2>;//now,old
class Input
{
public:
	Input();
	~Input();
	virtual void Update(void) = 0;

	/// @brief ���͋@��̃^�C�v���擾
	/// @return ���͋@��^�C�v
	virtual InputType GetInputType(void)const = 0;

	/// @brief �{�^���̏�Ԃ��擾����
	/// @param keyid enum����string�ɕϊ�����keyid
	/// @return �{�^�����
	virtual InputState GetInputState(std::string keyid)=0;

	/// @brief �A�i���O�l�̎擾����
	/// @param keyid enum����string�ɕϊ�����keyid
	/// @return �A�i���O�l
	virtual float GetAnalogData(std::string keyid) = 0;

	/// @brief ���͂����邩
	/// @return ���͂���:true ���͂Ȃ�:false
	virtual bool IsActive(void) = 0;

	/// @brief �w�肵�����͋@��̊��x���Z�b�g����
	/// @param sensi 0.01~20.0
	void SetSensi(float sensi);

	/// @brief �w�肵�����͋@��̊��x���擾����
	/// @return 0.01~20.0
	float GetSensi(void) { return sensitivity_; };

	/// @brief �w�肵�����͋@��̃f�b�h�]�[�����Z�b�g����
	/// @param zone 0.0~1.0
	virtual void SetDeadZone(float zone);

	/// @brief �w�肵�����͋@��̃f�b�h�]�[�����擾����
	/// @return 1.0~0.0�̊Ԃ̃f�b�h�]�[��
	float GetDeadZone(void) { return deadZone_; };

	/// @brief �}�E�X�|�C���^�[���Z���^�[�Œ肷��
	/// @param flag true:�Œ� false:���R
	void FixCenterCursor(bool flag);

	/// @brief �}�E�X�J�[�\�����Z���^�[�ɌŒ肵�Ă��邩
	/// @return true:�Œ� false:���R
	bool GetIsFixCenterCursor(void) { return isFixCenterCursor_; };
private:
	/// @brief �C���X�^���X���ł̏����� 
	virtual void InInit(void) = 0;
protected:
	/// @brief isFixCenterCursor��true�̎��C��ʒ����ɃZ�b�g���� 
	void DoCenterCursor(void);

	AnalogData analogData_;		//�A�i���O�l(�g���K�[��X�e�B�b�N�Ȃ�)
	float sensitivity_;			//�J�[�\���̊��x(�A�i���O�l�Ɋ|����l)
	float deadZone_;			//�X�e�B�b�N�̃f�b�h�]�[���͈�
	bool isFixCenterCursor_;	//��ʒ����ɌŒ肷�邩
};

