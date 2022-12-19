#include <DxLib.h>
#include <magic_enum.hpp>
#include "Keybord.h"
#include "KeybordID.h"
#include "../_debug/_DebugConOut.h"

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
	drawPos_.try_emplace(Trg::Now);
	drawPos_.try_emplace(Trg::Old);
	MouseCenterSet();
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

Vector2F Keybord::GetMoveVec(void)
{
	if (isFixCenterCursor_)
	{
		Vector2 size;
		GetDrawScreenSize(&size.x, &size.y);
		Vector2F center = static_cast<Vector2F>(size) / 2.0f;
		return drawPos_[Trg::Now] - center;
	}
	return drawPos_[Trg::Now] - drawPos_[Trg::Old];
}

void Keybord::UpdateKeybord(void)
{
	keybordData_[Trg::Old] = keybordData_[Trg::Now];
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
	drawPos_[Trg::Old] = drawPos_[Trg::Now];
	GetMousePoint(&drawPos_[Trg::Now].x, &drawPos_[Trg::Now].y);
	analogData_.at(AnalogInputID::CURSOR_X) = static_cast<float>(drawPos_[Trg::Now].x);
	analogData_.at(AnalogInputID::CURSOR_Y) = static_cast<float>(drawPos_[Trg::Now].y);
	//TRACE("場所::%d,%d\n", drawPos_.x, drawPos_.y);

	//マウスのカーソル移動量の更新部分
	MouseCenterSet();//センターにするフラグが立っている場合は画面中央にマウスカーソルが移動する
	auto movevec = GetMoveVec();
	analogData_.at(AnalogInputID::CURSOR_MOVED_X) = movevec.x;
	analogData_.at(AnalogInputID::CURSOR_MOVED_Y) = movevec.y;
	//TRACE("動いた距離::%lf,%lf\n", analogData_.at(AnalogInputID::CURSOR_MOVED_X), analogData_.at(AnalogInputID::CURSOR_MOVED_Y));
}
