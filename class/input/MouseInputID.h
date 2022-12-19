#pragma once
#include <type_traits>
enum class MouseInputID
{
	Click_L,
	Click_R,
	Click_M,
	Click_1,
	Click_2,
	Click_3,
	Click_4,
	WheelUp,
	WheelDown,
	Max
};

static MouseInputID begin(MouseInputID)
{
	return MouseInputID::Click_L;
};

static MouseInputID end(MouseInputID)
{
	return MouseInputID::Max;
};

static MouseInputID operator++(MouseInputID& state)
{
	return state = static_cast<MouseInputID>(std::underlying_type<MouseInputID>::type(state) + 1);
}

static MouseInputID operator*(const MouseInputID& state) { return state; };
