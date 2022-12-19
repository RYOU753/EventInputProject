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
	void InInit(void)override;
	InputType GetInputType(void)const override { return InputType::Keybord; };
	InputState GetInputState(std::string keyid)override;
	float GetAnalogData(std::string keyid)override;
	bool IsActive(void)override;
private:
	/// @brief �Z���^�[�Œ�̎��Z���^�[���瓮������
	/// @brief �Z���^�[�Œ肶��Ȃ��Ƃ���old���猻�݂̈ړ���
	/// @return �J�[�\���ړ���
	Vector2F GetMoveVec(void);
	void UpdateKeybord(void);
	void UpdateMouse(void);

	KeybordData keybordData_;
	MouseData mouseData_;
	std::unordered_map<MouseInputID, int> clickTbl_;
};
