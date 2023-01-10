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
	//キー入力を保持する256の配列をNowとOldで用意
	keybordData_.try_emplace(Trg::Now);
	keybordData_.try_emplace(Trg::Old);
	//MouseInputIDの保存場所を作成
	for (auto id : MouseInputID())
	{
		mouseData_.try_emplace(id);
		mouseData_[id].try_emplace(Trg::Now, false);
		mouseData_[id].try_emplace(Trg::Old, false);
	}
	//MouseInputIDとDXLibのマウス入力の値をテーブルにする
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
	//キー入力があったか
	for (const auto& key : keybordData_[Trg::Now])
	{
		if (key != 0)
		{
			return true;
		}
	}
	//マウスのスイッチ入力があったか
	for (auto id : MouseInputID())
	{
		if (mouseData_[id][Trg::Now])
		{
			return true;
		}
	}
	//マウスが動いたか
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
		data.second[Trg::Old] = data.second[Trg::Now];//1フレーム前のマウス入力を保存
	}
	//マウスのスイッチ入力の更新部分
	int click = GetMouseInput();
	for (auto id = MouseInputID(); id <= MouseInputID::Click_4; id = static_cast<MouseInputID>(static_cast<int>(id) + 1))
	{
		mouseData_[id][Trg::Now] = click & clickTbl_[id];
	}
	//マウスのホイール入力の更新部分
	int vol = GetMouseWheelRotVol();
	mouseData_[MouseInputID::WheelUp][Trg::Now] = vol > 0;
	mouseData_[MouseInputID::WheelDown][Trg::Now] = vol < 0;
	//マウスのカーソル位置の更新部分	
	Vector2 nowPos;
	GetMousePoint(&nowPos.x,&nowPos.y);
	oldCursorPos_.x = analogData_.at(AnalogInputID::CURSOR_X);
	oldCursorPos_.y = analogData_.at(AnalogInputID::CURSOR_Y);
	analogData_.at(AnalogInputID::CURSOR_X) = static_cast<float>(nowPos.x);
	analogData_.at(AnalogInputID::CURSOR_Y) = static_cast<float>(nowPos.y);	
	//マウスのカーソル移動量の更新部分
	analogData_.at(AnalogInputID::CURSOR_MOVED_X) = analogData_.at(AnalogInputID::CURSOR_X) - oldCursorPos_.x;
	analogData_.at(AnalogInputID::CURSOR_MOVED_Y) = analogData_.at(AnalogInputID::CURSOR_Y) - oldCursorPos_.y;
	//カーソルの中央固定時の処理
	if(isFixCenterCursor_)//画面中央固定の時，中央に戻す(画面中央フラグを立てる時に，一緒にCursorPosが画面中央の値になっているので前フレームのCursorPosを入れる)
	{
		SetMousePoint(static_cast<int>(oldCursorPos_.x), static_cast<int>(oldCursorPos_.y));
		analogData_.at(AnalogInputID::CURSOR_X) = oldCursorPos_.x;
		analogData_.at(AnalogInputID::CURSOR_Y) = oldCursorPos_.y;
	}
}
