#pragma once
#include "Input.h"
#include "../common/Vector2.h"

class Keybord :
	public Input
{
public:
	Keybord();
	~Keybord();
	void Update(void)override;

	/// @brief ���͋@��̃^�C�v���擾
	/// @return ���͋@��^�C�v
	InputType GetInputType(void)const override { return InputType::Keybord; };

	/// @brief �w�肵������ID�̏�Ԃ��擾����
	/// @param keyid �L�[�{�[�h���}�E�X�̓���ID�̕�����
	/// @return �w�肳�ꂽ����ID�̏��
	InputState GetInputState(std::string keyid)override;

	/// @brief �L�[�{�[�h�ƃ}�E�X�̃A�i���O���͒l���擾����
	/// @param keyid �L�[�{�[�h���}�E�X�̓���ID�̕�����
	/// @return �w�肳�ꂽ����ID�̃A�i���O���͒l
	float GetAnalogData(std::string keyid)override;

	/// @brief �L�[�{�[�h�����ݎg���Ă��邩�𔻒肷�� 
	/// @return true:�g���Ă��� false:�g���Ă��Ȃ�
	bool IsActive(void)override;
private:
	/// @brief �C���X�^���X���ł̏����� 
	void InInit(void)override;

	/// @brief �L�[�{�[�h���͂̍X�V 
	void UpdateKeybord(void);

	/// @brief �}�E�X���͂̍X�V
	void UpdateMouse(void);

	KeybordData keybordData_;							//�L�[�{�[�h�̓��̓f�[�^
	MouseData mouseData_;								//�}�E�X�̃X�C�b�`���̓f�[�^
	std::unordered_map<MouseInputID, int> clickTbl_;	//MouseInputID��DxLib�̃r�b�g���e�[�u���ɂ��Ă���
	Vector2F oldCursorPos_;								//�J�[�\���ʒu�̑O�t���[���̍��W
};
