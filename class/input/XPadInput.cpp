#include <Windows.h>
#include <Xinput.h>
#include <iostream>
#include <magic_enum.hpp>
#include "XPadInput.h"

//#include"../_debug/_DebugDispOut.h"

constexpr float PI_F = 3.1415926535897932384626433832795f;
constexpr float PI2_F = PI_F*2.0f;

XPadInput::XPadInput(int no)
{
	ZeroMemory(&xInput_, sizeof(_XINPUT_STATE));
	InInit();
}

XPadInput::~XPadInput()
{
}

void XPadInput::Update(void)
{
	
	if (XInputGetState(isConnectXPad_, &xInput_) != ERROR_DEVICE_NOT_CONNECTED)
	{
		for (auto& data : padData_)
		{
			data.second[Trg::OLD] = data.second[Trg::NOW];
		}

		for (auto& tblData : btnTbl_)
		{
			padData_[tblData.first][Trg::NOW] = xInput_.Gamepad.wButtons & tblData.second;
		}

		UpdateStickDigitalButton();

		padData_[PadInputID::LT][Trg::NOW] = xInput_.Gamepad.bLeftTrigger > 0;
		padData_[PadInputID::RT][Trg::NOW] = xInput_.Gamepad.bRightTrigger > 0;
		UpdateAnalog();
		DoCenterCursor();
	}
	else
	{
		std::cout << "失敗" << std::endl;
		ConectXPad();
	}
	DebugDraw();
}

void XPadInput::InInit(void)
{
	analogData_.try_emplace(AnalogInputID::PAD_STICK_LX, 0.0f);
	analogData_.try_emplace(AnalogInputID::PAD_STICK_LY, 0.0f);
	analogData_.try_emplace(AnalogInputID::PAD_STICK_RX, 0.0f);
	analogData_.try_emplace(AnalogInputID::PAD_STICK_RY, 0.0f);
	analogData_.try_emplace(AnalogInputID::PAD_TRIGGER_L, 0.0f);
	analogData_.try_emplace(AnalogInputID::PAD_TRIGGER_R, 0.0f);

	btnTbl_ = {
		{PadInputID::UP,XINPUT_GAMEPAD_DPAD_UP},
		{PadInputID::DOWN,XINPUT_GAMEPAD_DPAD_DOWN},
		{PadInputID::LEFT,XINPUT_GAMEPAD_DPAD_LEFT},
		{PadInputID::RIGHT,XINPUT_GAMEPAD_DPAD_RIGHT},

		{PadInputID::START,XINPUT_GAMEPAD_START},
		{PadInputID::PAUSE,XINPUT_GAMEPAD_BACK},

		{PadInputID::LB,XINPUT_GAMEPAD_LEFT_SHOULDER},
		{PadInputID::RB,XINPUT_GAMEPAD_RIGHT_SHOULDER},

		{PadInputID::STICK_PUSH_L,XINPUT_GAMEPAD_LEFT_THUMB},
		{PadInputID::STICK_PUSH_R,XINPUT_GAMEPAD_RIGHT_THUMB},

		{PadInputID::BTN_A,XINPUT_GAMEPAD_A},
		{PadInputID::BTN_B,XINPUT_GAMEPAD_B},
		{PadInputID::BTN_X,XINPUT_GAMEPAD_X},
		{PadInputID::BTN_Y,XINPUT_GAMEPAD_Y}
	};

	for (auto id : PadInputID())
	{
		padData_.try_emplace(id);
		padData_.at(id).try_emplace(Trg::NOW);
		padData_.at(id).try_emplace(Trg::OLD);
	}

	deadzone_ = 0.2f;
	ConectXPad();
}

InputState XPadInput::GetInputState(std::string_view keyid)
{
	auto id = magic_enum::enum_cast<PadInputID>(keyid);
	if (id.has_value())
	{
		if (padData_[id.value()][Trg::NOW] && !padData_[id.value()][Trg::OLD])
		{
			return InputState::PUSH;
		}
		if (!padData_[id.value()][Trg::NOW] && padData_[id.value()][Trg::OLD])
		{
			return InputState::RELEASE;
		}
		if (padData_[id.value()][Trg::NOW] && padData_[id.value()][Trg::OLD])
		{
			return InputState::HOLD;
		}
	}

	return InputState::NONE;
}

float XPadInput::GetAnalogData(std::string_view keyid)
{
	auto id = magic_enum::enum_cast<AnalogInputID>(keyid);
	if (id.has_value())
	{
		if (analogData_.count(id.value()))
		{
			return analogData_.at(id.value());
		}
	}

	return 0.0f;
}

float XPadInput::GetDirRot(StickLR dir)
{
	if (dir == StickLR::L)
	{
		return GetMoveDirRot(xInput_.Gamepad.sThumbLX, xInput_.Gamepad.sThumbLY);
	}

	return GetMoveDirRot(xInput_.Gamepad.sThumbRX, xInput_.Gamepad.sThumbRY);
}

Vector2F XPadInput::GetMoveVec(StickLR dir)
{
	if (dir == StickLR::L)
	{
		return GetMoveVec(xInput_.Gamepad.sThumbLX, xInput_.Gamepad.sThumbLY);
	}

	return GetMoveVec(xInput_.Gamepad.sThumbRX, xInput_.Gamepad.sThumbRY);
}

bool XPadInput::IsActive(void)
{
	for (auto id : PadInputID())
	{
		if (padData_[id][Trg::NOW])
		{
			return true;
		}
	}
	return false;
}

void XPadInput::UpdateStickDigitalButton(void)
{
	auto StickL = GetMoveVec(StickLR::L);
	auto StickR = GetMoveVec(StickLR::R);

	padData_[PadInputID::STICK_L_DOWN][Trg::NOW] = StickL.y < 0;
	padData_[PadInputID::STICK_L_UP][Trg::NOW] = StickL.y > 0;
	padData_[PadInputID::STICK_L_RIGHT][Trg::NOW] = StickL.x > 0;
	padData_[PadInputID::STICK_L_LEFT][Trg::NOW] = StickL.x < 0;

	padData_[PadInputID::STICK_R_DOWN][Trg::NOW] = StickR.y < 0;
	padData_[PadInputID::STICK_R_UP][Trg::NOW] = StickR.y > 0;
	padData_[PadInputID::STICK_R_RIGHT][Trg::NOW] = StickR.x > 0;
	padData_[PadInputID::STICK_R_LEFT][Trg::NOW] = StickR.x < 0;
}

void XPadInput::UpdateAnalog(void)
{
	auto StickL = GetMoveVec(StickLR::L);
	auto StickR = GetMoveVec(StickLR::R);
	analogData_.at(AnalogInputID::PAD_STICK_LX) = StickL.x;
	analogData_.at(AnalogInputID::PAD_STICK_LY) = StickL.y;
	analogData_.at(AnalogInputID::PAD_STICK_RX) = StickR.x;
	analogData_.at(AnalogInputID::PAD_STICK_RY) = StickR.y;
	analogData_.at(AnalogInputID::PAD_TRIGGER_L) = xInput_.Gamepad.bLeftTrigger / 255.0f;
	analogData_.at(AnalogInputID::PAD_TRIGGER_R) = xInput_.Gamepad.bRightTrigger / 255.0f;
	//マウスポインター更新
	analogData_.at(AnalogInputID::CURSOR_X) += StickL.x * sensitivity_;
	analogData_.at(AnalogInputID::CURSOR_Y) -= StickL.y * sensitivity_;
}

float XPadInput::GetMoveDirRot(short x, short y)
{
	auto dir = Vector2F(x, y);
	auto kijun = Vector2F();

	auto r = atan2(-(kijun.x - dir.x), -(kijun.y - dir.y));
	if (r < 0)
	{
		r = r + PI2_F;
	};

	return floorf(r * 360 / PI2_F);
}

Vector2F XPadInput::GetMoveVec(short x, short y)
{
	const float Max = 32767.0f;
	const float Min = 32768.0f;
	auto xdir = x > 0 ? x / Max : x / Min;
	auto ydir = y > 0 ? y / Max : y / Min;
	auto Dir = Vector2F(xdir, ydir);

	return CorrectDeadZone(Dir);
}

Vector2F XPadInput::CorrectDeadZone(Vector2F in)
{
	if (in.x > 0)
	{
		if (in.x > deadzone_)
		{
			auto f = (1.0f - in.x) / (1.0f - deadzone_);
			in.x = -(f - 1.0f);
		}
		else
		{
			in.x = 0.0f;
		}
	}
	else
	{
		if (-in.x > deadzone_)
		{
			auto f = (1.0f + in.x) / (1.0f - deadzone_);
			in.x = -(1.0f - f);
		}
		else
		{
			in.x = 0.0f;
		}
	}
	if (in.y > 0)
	{
		if (in.y > deadzone_)
		{
			auto f = (1.0f - in.y) / (1.0f - deadzone_);
			in.y = -(f - 1.0f);
		}
		else
		{
			in.y = 0.0f;
		}
	}
	else
	{
		if (-in.y > deadzone_)
		{
			auto f = (1.0f + in.y) / (1.0f - deadzone_);
			in.y = -(1.0f - f);
		}
		else
		{
			in.y = 0.0f;
		}
	}



	return in;
}

void XPadInput::ConectXPad()
{
	DWORD dwResult;
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		dwResult = XInputGetState(i, &xInput_);
		if (dwResult == ERROR_SUCCESS)
		{
			// Controller is connected
			std::cout << i << ":成功" << std::endl;
			isConnectXPad_ = i;
		}
		else
		{
			// Controller is not connected
			std::cout << i << ":失敗" << std::endl;
		}
	}
}

void XPadInput::DebugDraw(void)
{
	for (auto& data : padData_)
	{
		if (data.second[Trg::NOW])
		{
			auto str = magic_enum::enum_name(data.first).data();
			std::cout << str << std::endl;
		}
	}
}
