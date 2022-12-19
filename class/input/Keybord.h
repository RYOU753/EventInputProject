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
	/// @brief センター固定の時センターから動いた量
	/// @brief センター固定じゃないときはoldから現在の移動量
	/// @return カーソル移動量
	Vector2F GetMoveVec(void);
	void UpdateKeybord(void);
	void UpdateMouse(void);

	KeybordData keybordData_;
	MouseData mouseData_;
	std::unordered_map<MouseInputID, int> clickTbl_;
};
