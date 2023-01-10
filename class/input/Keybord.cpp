#include <DxLib.h>
#include <magic_enum.hpp>
#include "Keybord.h"
#include "KeybordID.h"
#include "../_debug/_DebugConOut.h"
#include "../_debug/_DebugDispOut.h"

Keybord::Keybord()
{
	InInit();
}

Keybord::~Keybord()
{
}

void Keybord::Update(void)
{
	UpdateKeybord();
	UpdateMouse();
}

void Keybord::InInit(void)
{
	//�L�[���͂�ێ�����256�̔z���Now��Old�ŗp��
	keybordData_.try_emplace(Trg::Now);
	keybordData_.try_emplace(Trg::Old);
	//MouseInputID�̕ۑ��ꏊ���쐬
	for (auto id : MouseInputID())
	{
		mouseData_.try_emplace(id);
		mouseData_[id].try_emplace(Trg::Now, false);
		mouseData_[id].try_emplace(Trg::Old, false);
	}
	//MouseInputID��DXLib�̃}�E�X���͂̒l���e�[�u���ɂ���
	clickTbl_ = {
		{MouseInputID::Click_L,MOUSE_INPUT_LEFT},
		{MouseInputID::Click_R,MOUSE_INPUT_RIGHT},
		{MouseInputID::Click_M,MOUSE_INPUT_MIDDLE},
		{MouseInputID::Click_1,MOUSE_INPUT_4},
		{MouseInputID::Click_2,MOUSE_INPUT_5},
		{MouseInputID::Click_3,MOUSE_INPUT_6},
		{MouseInputID::Click_4,MOUSE_INPUT_7},
	};
	DoCenterCursor();
}

InputState Keybord::GetInputState(std::string keyid)
{
	auto enum_key = magic_enum::enum_cast<KeybordID>(keyid);
	if (enum_key.has_value())
	{
		auto key = static_cast<size_t>(enum_key.value());
		if (keybordData_[Trg::Now][key] == 1 && keybordData_[Trg::Old][key] != 1)
		{
			return InputState::Push;
		}
		if (keybordData_[Trg::Now][key] != 1 && keybordData_[Trg::Old][key] == 1)
		{
			return InputState::Relese;
		}
		if (keybordData_[Trg::Now][key] == 1 && keybordData_[Trg::Old][key] == 1)
		{
			return InputState::Hold;
		}
	}
	auto mouse_key = magic_enum::enum_cast<MouseInputID>(keyid);
	if (mouse_key)
	{
		auto key = mouse_key.value();
		if (mouseData_[key][Trg::Now] && !mouseData_[key][Trg::Old])
		{
			return InputState::Push;
		}
		if (!mouseData_[key][Trg::Now] && mouseData_[key][Trg::Old])
		{
			return InputState::Relese;
		}
		if (mouseData_[key][Trg::Now] && mouseData_[key][Trg::Old])
		{
			return InputState::Hold;
		}
	}

	return InputState::None;
}

float Keybord::GetAnalogData(std::string keyid)
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

bool Keybord::IsActive(void)
{
	//�L�[���͂���������
	for (const auto& key : keybordData_[Trg::Now])
	{
		if (key != 0)
		{
			return true;
		}
	}
	//�}�E�X�̃X�C�b�`���͂���������
	for (auto id : MouseInputID())
	{
		if (mouseData_[id][Trg::Now])
		{
			return true;
		}
	}
	//�}�E�X����������
	if (analogData_[AnalogInputID::CURSOR_MOVED_X] > 0.f && analogData_[AnalogInputID::CURSOR_MOVED_X] < 0.f)
	{
		return true;
	}
	if (analogData_[AnalogInputID::CURSOR_MOVED_Y] > 0.f && analogData_[AnalogInputID::CURSOR_MOVED_Y] < 0.f)
	{
		return true;
	}

	return false;
}

void Keybord::UpdateKeybord(void)
{
	keybordData_[Trg::Old].swap(keybordData_[Trg::Now]);
	GetHitKeyStateAll(keybordData_[Trg::Now].data());
}

void Keybord::UpdateMouse(void)
{
	for (auto& data : mouseData_)
	{
		data.second[Trg::Old] = data.second[Trg::Now];//1�t���[���O�̃}�E�X���͂�ۑ�
	}
	//�}�E�X�̃X�C�b�`���͂̍X�V����
	int click = GetMouseInput();
	for (auto id = MouseInputID(); id <= MouseInputID::Click_4; id = static_cast<MouseInputID>(static_cast<int>(id) + 1))
	{
		mouseData_[id][Trg::Now] = click & clickTbl_[id];
	}
	//�}�E�X�̃z�C�[�����͂̍X�V����
	int vol = GetMouseWheelRotVol();
	mouseData_[MouseInputID::WheelUp][Trg::Now] = vol > 0;
	mouseData_[MouseInputID::WheelDown][Trg::Now] = vol < 0;
	//�}�E�X�̃J�[�\���ʒu�̍X�V����	
	Vector2 nowPos;
	GetMousePoint(&nowPos.x,&nowPos.y);
	oldCursorPos_.x = analogData_.at(AnalogInputID::CURSOR_X);
	oldCursorPos_.y = analogData_.at(AnalogInputID::CURSOR_Y);
	analogData_.at(AnalogInputID::CURSOR_X) = static_cast<float>(nowPos.x);
	analogData_.at(AnalogInputID::CURSOR_Y) = static_cast<float>(nowPos.y);	
	//�}�E�X�̃J�[�\���ړ��ʂ̍X�V����
	analogData_.at(AnalogInputID::CURSOR_MOVED_X) = analogData_.at(AnalogInputID::CURSOR_X) - oldCursorPos_.x;
	analogData_.at(AnalogInputID::CURSOR_MOVED_Y) = analogData_.at(AnalogInputID::CURSOR_Y) - oldCursorPos_.y;
	//�J�[�\���̒����Œ莞�̏���
	if(isFixCenterCursor_)//��ʒ����Œ�̎��C�����ɖ߂�(��ʒ����t���O�𗧂Ă鎞�ɁC�ꏏ��CursorPos����ʒ����̒l�ɂȂ��Ă���̂őO�t���[����CursorPos������)
	{
		SetMousePoint(static_cast<int>(oldCursorPos_.x), static_cast<int>(oldCursorPos_.y));
		analogData_.at(AnalogInputID::CURSOR_X) = oldCursorPos_.x;
		analogData_.at(AnalogInputID::CURSOR_Y) = oldCursorPos_.y;
	}
}
