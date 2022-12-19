#include <magic_enum.hpp>
#include "PadInput.h"
#include "../_debug/_DebugDispOut.h"
#include "../_debug/_DebugConOut.h"

PadInput::PadInput()
{
	InInit();
}

PadInput::~PadInput()
{
}

void PadInput::Update(void)
{
	auto a = GetJoypadDeadZone(DX_INPUT_PAD1);
	ConnectNum_.second = ConnectNum_.first;
	ConnectNum_.first = GetJoypadNum();
	_TRACE_S(0xffffff, "Num:", ConnectNum_.first);

	if (ConnectPadNum_ != -1)
	{
		for (auto& data : padData_)
		{
			data.second[Trg::Old] = data.second[Trg::Now];
		}

		ConnectPadNum_ = GetJoypadXInputState(DX_INPUT_PAD1, &xInput_);
		for (auto& tblData : btnTbl_)
		{
			padData_[tblData.first][Trg::Now] = xInput_.Buttons[tblData.second];
		}

		StickDigitalButtonUpdate();

		padData_[PadInputID::LT][Trg::Now] = xInput_.LeftTrigger > 0;
		padData_[PadInputID::RT][Trg::Now] = xInput_.RightTrigger > 0;
		AnalogUpdate();
		MouseCenterSet();
	}
	else if (ConnectNum_.first > ConnectNum_.second)
	{
		ReSetupJoypad();
		ConnectPadNum_ = GetJoypadXInputState(DX_INPUT_PAD1, &xInput_);
	}
	DebugDraw();
}

void PadInput::InInit(void)
{
	analogData_.try_emplace(AnalogInputID::PAD_STICK_LX, 0.0f);
	analogData_.try_emplace(AnalogInputID::PAD_STICK_LY, 0.0f);
	analogData_.try_emplace(AnalogInputID::PAD_STICK_RX, 0.0f);
	analogData_.try_emplace(AnalogInputID::PAD_STICK_RY, 0.0f);
	analogData_.try_emplace(AnalogInputID::PAD_TRIGGER_L, 0.0f);
	analogData_.try_emplace(AnalogInputID::PAD_TRIGGER_R, 0.0f);

	btnTbl_ = {
		{PadInputID::UP,XINPUT_BUTTON_DPAD_UP},
		{PadInputID::DOWN,XINPUT_BUTTON_DPAD_DOWN},
		{PadInputID::LEFT,XINPUT_BUTTON_DPAD_LEFT},
		{PadInputID::RIGHT,XINPUT_BUTTON_DPAD_RIGHT},

		{PadInputID::START,XINPUT_BUTTON_START},
		{PadInputID::PAUSE,XINPUT_BUTTON_BACK},

		{PadInputID::LB,XINPUT_BUTTON_LEFT_SHOULDER},
		{PadInputID::RB,XINPUT_BUTTON_RIGHT_SHOULDER},

		{PadInputID::STICK_PUSH_L,XINPUT_BUTTON_LEFT_THUMB},
		{PadInputID::STICK_PUSH_R,XINPUT_BUTTON_RIGHT_THUMB},

		{PadInputID::BTN_A,XINPUT_BUTTON_A},
		{PadInputID::BTN_B,XINPUT_BUTTON_B},
		{PadInputID::BTN_X,XINPUT_BUTTON_X},
		{PadInputID::BTN_Y,XINPUT_BUTTON_Y}
	};

	for (auto id : PadInputID())
	{
		padData_.try_emplace(id);
		padData_.at(id).try_emplace(Trg::Now);
		padData_.at(id).try_emplace(Trg::Old);
	}

	deadzone_ = 0.2f;
	ConnectPadNum_ = GetJoypadXInputState(DX_INPUT_PAD1, &xInput_);
	ConnectNum_.first = GetJoypadNum();
	ConnectNum_.second = ConnectNum_.first;
}

InputState PadInput::GetInputState(std::string keyid)
{
	auto id = magic_enum::enum_cast<PadInputID>(keyid);
	if (id.has_value())
	{
		if (padData_[id.value()][Trg::Now] && !padData_[id.value()][Trg::Old])
		{
			return InputState::Push;
		}
		if (!padData_[id.value()][Trg::Now] && padData_[id.value()][Trg::Old])
		{
			return InputState::Relese;
		}
		if (padData_[id.value()][Trg::Now] && padData_[id.value()][Trg::Old])
		{
			return InputState::Hold;
		}
	}

	return InputState::None;
}

float PadInput::GetAnalogData(std::string keyid)
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

float PadInput::GetDirRot(Stick_LR dir)
{
	if (dir == Stick_LR::L)
	{
		return GetMoveDirRot(xInput_.ThumbLX, xInput_.ThumbLY);
	}

	return GetMoveDirRot(xInput_.ThumbRX, xInput_.ThumbRY);
}

Vector2F PadInput::GetMoveDir(Stick_LR dir)
{
	if (dir == Stick_LR::L)
	{
		return GetMoveDir(xInput_.ThumbLX, xInput_.ThumbLY);
	}

	return GetMoveDir(xInput_.ThumbRX, xInput_.ThumbRY);
}

bool PadInput::IsActive(void)
{
	for (auto id : PadInputID())
	{
		if (padData_[id][Trg::Now])
		{
			return true;
		}
	}
	return false;
}

void PadInput::StickDigitalButtonUpdate(void)
{
	auto StickL = GetMoveDir(Stick_LR::L);
	auto StickR = GetMoveDir(Stick_LR::R);

	padData_[PadInputID::STICK_L_DOWN][Trg::Now] = StickL.y < 0;
	padData_[PadInputID::STICK_L_UP][Trg::Now] = StickL.y > 0;
	padData_[PadInputID::STICK_L_RIGHT][Trg::Now] = StickL.x > 0;
	padData_[PadInputID::STICK_L_LEFT][Trg::Now] = StickL.x < 0;

	padData_[PadInputID::STICK_R_DOWN][Trg::Now] = StickR.y < 0;
	padData_[PadInputID::STICK_R_UP][Trg::Now] = StickR.y > 0;
	padData_[PadInputID::STICK_R_RIGHT][Trg::Now] = StickR.x > 0;
	padData_[PadInputID::STICK_R_LEFT][Trg::Now] = StickR.x < 0;
}

void PadInput::AnalogUpdate(void)
{
	auto StickL = GetMoveDir(Stick_LR::L);
	auto StickR = GetMoveDir(Stick_LR::R);
	analogData_.at(AnalogInputID::PAD_STICK_LX) = StickL.x;
	analogData_.at(AnalogInputID::PAD_STICK_LY) = StickL.y;
	analogData_.at(AnalogInputID::PAD_STICK_RX) = StickR.x;
	analogData_.at(AnalogInputID::PAD_STICK_RY) = StickR.y;
	analogData_.at(AnalogInputID::PAD_TRIGGER_L) = xInput_.LeftTrigger / 255.0f;
	analogData_.at(AnalogInputID::PAD_TRIGGER_R) = xInput_.RightTrigger / 255.0f;
	//マウスポインター更新
	float oldPx, oldPy;
	oldPx = analogData_.at(AnalogInputID::CURSOR_X);
	oldPy = analogData_.at(AnalogInputID::CURSOR_Y);
	analogData_.at(AnalogInputID::CURSOR_X) += StickL.x * sensitivity_;
	analogData_.at(AnalogInputID::CURSOR_Y) -= StickL.y * sensitivity_;
	analogData_.at(AnalogInputID::CURSOR_MOVED_X) = analogData_.at(AnalogInputID::CURSOR_X) - oldPx;
	analogData_.at(AnalogInputID::CURSOR_MOVED_Y) = analogData_.at(AnalogInputID::CURSOR_Y) - oldPy;
}

float PadInput::GetMoveDirRot(short x, short y)
{
	auto dir = Vector2F(x, y);
	auto kijun = Vector2F();

	auto r = atan2(-(kijun.x - dir.x), -(kijun.y - dir.y));
	if (r < 0)
	{
		r = r + 2 * DX_PI_F;
	};

	return floorf(r * 360 / (2 * DX_PI_F));
}

Vector2F PadInput::GetMoveDir(short x, short y)
{
	const float Max = 32767.0f;
	const float Min = 32768.0f;
	auto xdir = x > 0 ? x / Max : x / Min;
	auto ydir = y > 0 ? y / Max : y / Min;
	auto Dir = Vector2F(xdir, ydir);

	return CorrectDeadZone(Dir);
}

Vector2F PadInput::CorrectDeadZone(Vector2F in)
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

void PadInput::DebugDraw()
{
	for (auto& data : padData_)
	{
		if (data.second[Trg::Now])
		{
			auto str = magic_enum::enum_name(data.first).data();
			_TRACE_M(0xffffff, str);
		}
	}
}
