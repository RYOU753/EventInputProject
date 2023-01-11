#pragma once
#include <json.hpp>

enum class SOUND_TYPE {
	BGM,
	SE,
	MAX
};
static SOUND_TYPE begin(SOUND_TYPE) {
	return SOUND_TYPE::BGM;
};

static SOUND_TYPE end(SOUND_TYPE) {
	return SOUND_TYPE::MAX;
};

static SOUND_TYPE operator++(SOUND_TYPE& state) {
	return state = static_cast<SOUND_TYPE>(std::underlying_type<SOUND_TYPE>::type(state) + 1);
};

static SOUND_TYPE operator*(const SOUND_TYPE& state) { return state; };

NLOHMANN_JSON_SERIALIZE_ENUM(SOUND_TYPE,
	{
		{SOUND_TYPE::BGM,"BGM"},
		{SOUND_TYPE::SE,"SE"},
	})
