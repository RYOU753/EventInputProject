#pragma once
#include <type_traits>
//ƒ{ƒ^ƒ“‚ÌŽí—Þ
enum class PadInputID
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	BTN_A,
	BTN_X,
	BTN_Y,
	BTN_B,
	START,
	PAUSE,
	LB,
	RB,
	LT,
	RT,
	STICK_PUSH_L,
	STICK_PUSH_R,
	STICK_L_UP,
	STICK_L_DOWN,
	STICK_L_LEFT,
	STICK_L_RIGHT,
	STICK_R_UP,
	STICK_R_DOWN,
	STICK_R_LEFT,
	STICK_R_RIGHT,
	MAX
};
static PadInputID begin(PadInputID) {
	return PadInputID::UP;
};

static PadInputID end(PadInputID) {
	return PadInputID::MAX;
};

static PadInputID operator++(PadInputID& state) {
	return state = static_cast<PadInputID>(std::underlying_type<PadInputID>::type(state) + 1);
}

static PadInputID operator*(const PadInputID& state) { return state; };