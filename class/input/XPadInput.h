#pragma once
#include <Xinput.h>
#pragma comment (lib,"xinput.lib")
#include "Input.h"
class XPadInput :
	public Input
{
public:
	XPadInput(int no = 0);
	~XPadInput();

	void Update(void)override;
	void InInit(void)override;
	InputType GetInputType(void)const override { return InputType::PAD; };

	InputState GetInputState(std::string_view keyid)override;
	float GetAnalogData(std::string_view keyid)override;

	float GetDirRot(StickLR dir);
	Vector2F GetMoveVec(StickLR dir);
	bool IsActive(void)override;
private:
	void UpdateStickDigitalButton(void);
	void UpdateAnalog(void);
	//指定した方
	float GetMoveDirRot(short x, short y);
	//指定した方
	Vector2F GetMoveVec(short x, short y);
	//デッドゾーン内ならゼロにする
	Vector2F CorrectDeadZone(Vector2F in);
	void ConectXPad();
	void DebugDraw(void);

	XPadData padData_;
	_XINPUT_STATE xInput_;
	std::unordered_map<PadInputID, unsigned int> btnTbl_;
	float deadzone_;
	int isConnectXPad_;
};

