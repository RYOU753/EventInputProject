#include <DxLib.h>
#include <algorithm>
#include "Input.h"

Input::Input()
{
	analogData_.try_emplace(AnalogInputID::CURSOR_X, 0.0f);
	analogData_.try_emplace(AnalogInputID::CURSOR_Y, 0.0f);
	analogData_.try_emplace(AnalogInputID::CURSOR_MOVED_X, 0.0f);
	analogData_.try_emplace(AnalogInputID::CURSOR_MOVED_Y, 0.0f);
	isFixCenterCursor_ = true;
	MouseCenterSet();
	isFixCenterCursor_ = false;
	SetSensi(0.5f);
	SetDeadZone(0.3f);
}

Input::~Input()
{
}

void Input::SetSensi(float sensi) 
{
	sensitivity_ = std::clamp(sensi, 0.01f, 20.0f);;
}

void Input::SetDeadZone(float zone) 
{
	deadZone_ = std::clamp(zone, 0.0f, 1.0f);
}

void Input::MouseCenterSet(void)
{
	if (isFixCenterCursor_)
	{
		Vector2 size;
		GetDrawScreenSize(&size.x, &size.y);
		Vector2F center = static_cast<Vector2F>(size) / 2.0f;
		SetMousePoint(static_cast<int>(center.x), static_cast<int>(center.y));

		analogData_.at(AnalogInputID::CURSOR_X) = center.x;
		analogData_.at(AnalogInputID::CURSOR_Y) = center.y;
	}
}