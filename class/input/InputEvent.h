#pragma once
#include <memory>
#include <vector>
#include <list>
#include <optional>
#include "EventID.h"
#include "Input.h"
#include "../common/Vector2.h"
#include "AnalogInputID.h"

using Axis = std::pair<EventID, EventID>;
using FlexibleInput = std::vector<std::string>;
using InputTypeContena = std::array<FlexibleInput, 2U>;

struct EventData
{
	EventData() :isCanConfig(false){};
	InputTypeContena continer;
	bool isCanConfig;
};

class InputEvent
{
public:
	InputEvent(std::string filePath);
	~InputEvent();
	/// @brief ���͋@��̏��X�V��Pad�Ɛ؂�ւ������邩�܂��ڑ����m������
	/// @param delta �f���^�J�E���^
	void Update(const double& delta);

	/// @brief EventID�ƕR�Â��Ă�{�^���̏�Ԃ��݂�����Ԃ��𒲂ׂ�
	/// @param id �o�^�����C�x���g
	/// @param state �������{�^���̏��
	/// @return �������{�^���̏�Ԃ�������:true|��������Ȃ�:false
	float GetDigitalEvent(EventID id,InputState state = InputState::None)const;

	/// @brief �R�Â��Ă�AnalogInputID�̃A�i���O�l���擾
	/// @return �w��̃A�i���O�l
	float GetAnalogEvent(AnalogInputID id)const;
	
	/// @brief EventID����{�^�������擾���Cid1��������Ă�1.0f,id2��������Ă���-1.0f��
	/// @brief AnalogInputID�������Ă���1.0f~-1.0f���擾����
	/// @param id1 +�����̓���
	/// @param id2 -�����̓���
	/// @return 1.0f~-1.0f���擾����
	float GetAnalogEvent(EventID id1, EventID id2)const;

	/// @brief �A�i���O�l���擾����vec��pos�̂悤�Ɉ���
	/// @param id1 �������̒l
	/// @param id2 �c�����̒l
	/// @return �����x�N�g������W
	Vector2F GetAnalogVecEvent(AnalogInputID id1, AnalogInputID id2)const;

	/// @brief ��̎�����vec��pos���쐬����
	/// @param x��(+�����̓���,-�����̓���)
	/// @param y��(+�����̓���,-�����̓���)
	/// @return �����x�N�g������W
	Vector2F GetAnalogVecEvent(Axis axis1, Axis axis2)const;
	
	/// @brief �R���g���[���X�e�B�b�N�̂������������̊p�x��}�E�X�𓮂����������̊p�x�����߂�
	/// @param id x�l
	/// @param id2 y�l
	/// @returns �x���@(�������ĂȂ����͒��g���Ȃ�)�E��0�x�オ90�x
	std::optional<float> GetDirAngle(AnalogInputID id, AnalogInputID id2,float offset = 0.0f)const;

	/// @brief digital�̃X�e�B�b�N��analog�̃X�e�B�b�N������ORVector�̒��ɂ���Ɛ��m�Ȓl�����Ȃ��ꍇ������܂��D
	/// @param axis1 x��(+�����̓���,-�����̓���)
	/// @param axis2 y��(+�����̓���,-�����̓���)
	/// @return �x���@(�������ĂȂ����͒��g���Ȃ�)�E��0�x�オ90�x
	std::optional<float> GetDirAngle(Axis axis1, Axis axis2, float offset = 0.0f)const;

	/// @brief �w�肵�����͋@��̊��x���Z�b�g����
	/// @brief 0.01~20.0�͈̔͂ŃZ�b�g����悤�ɂȂ��Ă���
	/// @param sensi 0.01~20.0�͈̔͂ŃZ�b�g����
	void SetSensi(InputType type, float sensi);

	/// @brief �w�肵�����͋@��̊��x���擾����
	/// @return 0.01~20.0�̊Ԃ̊��x
	float GetSensi(InputType type);

	/// @brief �w�肵�����͋@��̃f�b�h�]�[�����Z�b�g����
	/// @param zone 0.0~1.0
	void SetDeadZone(InputType type,float zone);

	/// @brief �w�肵�����͋@��̃f�b�h�]�[�����擾����
	/// @return 1.0~0.0�̊Ԃ̃f�b�h�]�[��
	float GetDeadZone(InputType type);
	
	/// @brief �}�E�X�|�C���^�[���Z���^�[�Œ肷��
	/// @param flag true:�Œ� false:���R
	void FixCenterCursor(bool flag);

	/// @brief �}�E�X�J�[�\�����Z���^�[�ɌŒ肵�Ă��邩
	/// @return true:�Œ� false:���R
	bool GetIsFixCenterCursor(void);

	/// @brief ���ݎg���Ă�����͋@��̎�ނ�Ԃ�
	/// @returns ���͋@��̎��
	InputType GetInputType(void);

	/// @brief �o�^����Ă���C�x���g����͂���Ă��邩�f�o�b�O�\������ 
	void DebugDraw(void);
	void SaveConfig();
private:
	/// @brief �C���X�^���X���̏���������
	void InInit(void);

	/// @brief json�t�@�C����EventTbl�̒��g�������ċL�^����
	void Write();
	bool ChangeEventKeyInput(EventID eventID,InputType type);
	/// @brief json�t�@�C���̓ǂݍ��݂���EventTbl�����[�h����
	/// @return json�t�@�C��������:true | �Ȃ�:false
	bool Read(void);

	/// @brief json�ɏ������܂ꂽ����enum class�ɂ���keyid����v���Ă��邩�𒲂ׂ�
	/// @brief ��v���ĂȂ������烍�O�t�@�C�����c���ċ����I������
	void InputIDCheck(void);

	/// @brief ���͋@�킪�g���Ă邩�𒲂ׁC�g���ĂȂ�������noneActive�𒲂׎g���Ă�����؂�ւ���
	void SwitchInput();

	std::unique_ptr<Input> activeInput_;	//���ݎg���Ă������
	std::unique_ptr<Input> noneActive_;		//���ݎg���ĂȂ�����
	std::unique_ptr<class Keybord> keybord_;
	std::list<std::unique_ptr<class PadInput>> padList_;

	std::pair<int, int> ConnectNum_;		//pad�̐ڑ���(Now,Old)

	std::unordered_map<EventID, EventData> eventTbl_;

	std::string filePath_;
};
