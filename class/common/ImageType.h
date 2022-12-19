#pragma once
#include <json.hpp>

enum class IMAGE_TYPE
{
	Single,
	Chips,
	Atlas,
	Max
};

NLOHMANN_JSON_SERIALIZE_ENUM(IMAGE_TYPE,
	{
		{IMAGE_TYPE::Single,"Single"},
		{IMAGE_TYPE::Chips,"Chips"},
		{IMAGE_TYPE::Atlas,"Atlas"},
	})
