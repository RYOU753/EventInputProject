#include <magic_enum.hpp>
#include "PadInput.h"
#include "../_debug/_DebugDispOut.h"
#include "../_debug/_DebugConOut.h"

PadInput::PadInput(int padNo):padNo_(padNo)
{
	InInit();
}

PadInput::~PadInput()
{
}

void PadInput::Update(void)
{
	//�p�b�h�̐ڑ����̍X�V����
	ConnectNum_.second = ConnectNum_.first;
	ConnectNum_.first = GetJoypadNum();

	if (isConnectXPad_ == 0)//�ڑ��ł��Ă��鎞
	{
		UpdateDigital();
		UpdateAnalog();
		DoCenterCursor();
	}
	else if (ConnectNum_.first > ConnectNum_.second)
	{
		ReSetupJoypad();
		isConnectXPad_ = GetJoypadXInputState(padNo_, &xInput_);
	}
	DebugDraw();
}

void PadInput::InInit(void)
{
	//�A�i���O�f�[�^�̏�����
	analogData_.try_emplace(AnalogInputID::PAD_STICK_LX, 0.0f);
	analogData_.try_emplace(AnalogInputID::PAD_STICK_LY, 0.0f);
	analogData_.try_emplace(AnalogInputID::PAD_STICK_RX, 0.0f);
	analogData_.try_emplace(AnalogInputID::PAD_STICK_RY, 0.0f);
	analogData_.try_emplace(AnalogInputID::PAD_TRIGGER_L, 0.0f);
	analogData_.try_emplace(AnalogInputID::PAD_TRIGGER_R, 0.0f);
	//�e�[�u���̏�����
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
	//�p�b�h�̓��͕ۊǏꏊ�̏�����
	for (auto id : PadInputID())
	{
		padData_.try_emplace(id);
		padData_.at(id).try_emplace(Trg::Now);
		padData_.at(id).try_emplace(Trg::Old);
	}
	SetDeadZone(0.3f);
	//���݁CXPAD���Ȃ����Ă��邩���m�F
	isConnectXPad_ = GetJoypadXInputState(padNo_, &xInput_);
	//���炩��Pad���Ȃ����Ă��邩���m�F
	ConnectNum_.first = GetJoypadNum();
	ConnectNum_.second = ConnectNum_.first;
}

void PadInput::UpdateDigital(void)
{
	//�O�t���[����pad�̃{�^�����͂̍X�V����
	for(auto& data : padData_)
	{
		data.second[Trg::Old] = data.second[Trg::Now];
	}

	//���t���[���̃p�b�h�̃{�^�����͂̍X�V����
	isConnectXPad_ = GetJoypadXInputState(padNo_, &xInput_);
	for(auto& tblData : btnTbl_)
	{
		padData_[tblData.first][Trg::Now] = xInput_.Buttons[tblData.second];
	}

	//�g���K�[���͂̍X�V����
	padData_[PadInputID::LT][Trg::Now] = xInput_.LeftTrigger > 0;
	padData_[PadInputID::RT][Trg::Now] = xInput_.RightTrigger > 0;

	//�A�i���O�X�e�B�b�N���͂̍X�V����
	UpdateStickDigitalButton();
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

std::optional<float> PadInput::GetDirRot(Stick_LR dir)
{
	if (dir == Stick_LR::L)
	{
		return GetMoveDirRot(xInput_.ThumbLX, xInput_.ThumbLY);
	}

	return GetMoveDirRot(xInput_.ThumbRX, xInput_.ThumbRY);
}

Vector2F PadInput::GetMoveVec(Stick_LR dir)
{
	if (dir == Stick_LR::L)
	{
		return GetMoveVec(xInput_.ThumbLX, xInput_.ThumbLY);
	}

	return GetMoveVec(xInput_.ThumbRX, xInput_.ThumbRY);
}

void PadInput::SetDeadZone(float zone)
{
	deadZone_ = std::clamp(zone, 0.f, 0.999f);
	SetJoypadDeadZone(padNo_, static_cast<double>(deadZone_));
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

void PadInput::UpdateStickDigitalButton(void)
{
	//���X�e�B�b�N���͂̍X�V����
	auto StickL = GetMoveVec(Stick_LR::L);
	padData_[PadInputID::STICK_L_DOWN][Trg::Now] = StickL.y < 0;
	padData_[PadInputID::STICK_L_UP][Trg::Now] = StickL.y > 0;
	padData_[PadInputID::STICK_L_RIGHT][Trg::Now] = StickL.x > 0;
	padData_[PadInputID::STICK_L_LEFT][Trg::Now] = StickL.x < 0;
	//�E�X�e�B�b�N���͂̍X�V����
	auto StickR = GetMoveVec(Stick_LR::R);
	padData_[PadInputID::STICK_R_DOWN][Trg::Now] = StickR.y < 0;
	padData_[PadInputID::STICK_R_UP][Trg::Now] = StickR.y > 0;
	padData_[PadInputID::STICK_R_RIGHT][Trg::Now] = StickR.x > 0;
	padData_[PadInputID::STICK_R_LEFT][Trg::Now] = StickR.x < 0;
}

void PadInput::UpdateAnalog(void)
{
	//�A�i���O�X�e�B�b�N���͂̍X�V����
	auto StickL = GetMoveVec(Stick_LR::L);
	auto StickR = GetMoveVec(Stick_LR::R);
	analogData_.at(AnalogInputID::PAD_STICK_LX) = StickL.x;
	analogData_.at(AnalogInputID::PAD_STICK_LY) = StickL.y;
	analogData_.at(AnalogInputID::PAD_STICK_RX) = StickR.x;
	analogData_.at(AnalogInputID::PAD_STICK_RY) = StickR.y;
	analogData_.at(AnalogInputID::PAD_TRIGGER_L) = xInput_.LeftTrigger / 255.0f;
	analogData_.at(AnalogInputID::PAD_TRIGGER_R) = xInput_.RightTrigger / 255.0f;
	//�}�E�X�J�[�\���̍X�V����
	oldCursorPos_.x = analogData_.at(AnalogInputID::CURSOR_X);
	oldCursorPos_.y = analogData_.at(AnalogInputID::CURSOR_Y);
	analogData_.at(AnalogInputID::CURSOR_X) += StickL.x * sensitivity_;
	analogData_.at(AnalogInputID::CURSOR_Y) -= StickL.y * sensitivity_;
	analogData_.at(AnalogInputID::CURSOR_MOVED_X) = analogData_.at(AnalogInputID::CURSOR_X) - oldCursorPos_.x;
	analogData_.at(AnalogInputID::CURSOR_MOVED_Y) = analogData_.at(AnalogInputID::CURSOR_Y) - oldCursorPos_.y;

	if(isFixCenterCursor_)//��ʒ����Œ�̎��C�����ɖ߂�(��ʒ����t���O�𗧂Ă鎞�ɁC�ꏏ��CursorPos����ʒ����̒l�ɂȂ��Ă���̂őO�t���[����CursorPos������)
	{
		SetMousePoint(static_cast<int>(oldCursorPos_.x), static_cast<int>(oldCursorPos_.y));
		analogData_.at(AnalogInputID::CURSOR_X) = oldCursorPos_.x;
		analogData_.at(AnalogInputID::CURSOR_Y) = oldCursorPos_.y;
	}
	/*else//analogData_��CURSOR�ƃ}�E�X�J�[�\���𓯊�����
	{
		SetMousePoint(static_cast<int>(analogData_.at(AnalogInputID::CURSOR_X)), static_cast<int>(analogData_.at(AnalogInputID::CURSOR_Y)));
	}*/
}

std::optional<float> PadInput::GetMoveDirRot(short x, short y)
{
	auto dir = GetMoveVec(x,y);
	if(dir.isZero())//�ǂ��ɂ��X���ĂȂ���
	{
		return std::nullopt;
	}
	auto kijun = Vector2F();

	//auto rad = atan2(-(kijun.x - dir.x), -(kijun.y - dir.y));
	auto rad = atan2(dir.x, dir.y);
	if (rad < 0)
	{
		rad = rad + 2 * DX_PI_F;
	};

	return floorf(rad * 360 / (2 * DX_PI_F));//�x���@�ŕԂ�
}

Vector2F PadInput::GetMoveVec(short x, short y)
{
	static const float Max = 32767.0f;
	static const float Min = 32768.0f;
	auto xdir = x > 0 ? static_cast<float>(x) / Max : static_cast<float>(x) / Min;
	auto ydir = y > 0 ? static_cast<float>(y) / Max : static_cast<float>(y) / Min;

	return CorrectDeadZone(Vector2F{ xdir, ydir });
}

Vector2F PadInput::CorrectDeadZone(Vector2F in)
{
	auto func = [this](float& val){
		if(val > 0.f)
		{
			if(val >= deadZone_)
			{
				auto f = (1.0f - val) / (1.0f - deadZone_);
				val = -(f - 1.0f);
			}
			else
			{
				val = 0.0f;
			}
		}
		else
		{
			if(-val >= deadZone_)
			{
				auto f = (1.0f + val) / (1.0f - deadZone_);
				val = -(1.0f - f);
			}
			else
			{
				val = 0.0f;
			}
		}
	};

	func(in.x);
	func(in.y);
	/*if(in.lengthSQ() < deadZone_ * deadZone_)
	{
		return Vector2F();
	}
	auto len = in.length();
	auto norm = in / len;
	auto A = 1.f - deadZone_;
	auto B = (A / (1.f - deadZone_));
	return norm * B;

	auto func = [this,&len,&norm](float& val){
		if(val > 0.f)
		{
			auto f = (1.0f - val) / (1.0f - deadZone_);
			val = -(f - 1.0f);
		}
		else
		{
			auto f = (1.0f + val) / (1.0f - deadZone_);
			val = -(1.0f - f);
		}
	};
	func(in.x);
	func(in.y);*/
	return in;
}

void PadInput::DebugDraw()
{
	_TRACE_S(0xffffff, "�ڑ���:", ConnectNum_.first);
	for (auto& data : padData_)
	{
		if (data.second[Trg::Now])
		{
			auto str = magic_enum::enum_name(data.first).data();
			_TRACE_M(0xffffff, str);
		}
	}
	_TRACE_M(0xffffff, "StickL x:%.2f,y:%.2f", analogData_[AnalogInputID::PAD_STICK_LX], analogData_[AnalogInputID::PAD_STICK_LY]);
	_TRACE_M(0xffffff, "StickR x:%.2f,y:%.2f", analogData_[AnalogInputID::PAD_STICK_RX], analogData_[AnalogInputID::PAD_STICK_RY]);
	Vector2 center(400,400);
	int range = 50;
	_dbgDrawLine(center.x - range, center.y, center.x + range, center.y, 0xffffff);
	_dbgDrawLine(center.x, center.y - range, center.x, center.y + range, 0xffffff);
	_dbgDrawCircle(center.x+(analogData_[AnalogInputID::PAD_STICK_LX]*range), center.y-(analogData_[AnalogInputID::PAD_STICK_LY]*range), 2, 0x00ff00,true);
	_dbgDrawCircle(center.x, center.y, range, 0xffffff, false);
}
