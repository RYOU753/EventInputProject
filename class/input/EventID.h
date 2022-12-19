#pragma once
#include <type_traits>

enum class EventID
{
	None,
	Left,
	Right,
	Up,
	Down,
	MoveLeft,
	MoveRight,
	MoveForward,
	MoveBack,
	PauseKey,
	SelectField,
	ClubSelectL,
	ClubSelectR,
	CheckScoreBord,
	TestClick1,
	TestClick2,
	ChangeScene,
	ShotBall,
	Max
};
static EventID begin(EventID)
{
	return EventID::None;
};

static EventID end(EventID)
{
	return EventID::Max;
};

static EventID operator++(EventID& state)
{
	return state = static_cast<EventID>(std::underlying_type<EventID>::type(state) + 1);
}

static EventID operator*(const EventID& state) { return state; };
