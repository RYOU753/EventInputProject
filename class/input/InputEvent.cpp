#include <fstream>
#include <chrono>
#include <json.hpp>
#define MAGIC_ENUM_RANGE_MIN 0
#define MAGIC_ENUM_RANGE_MAX 256
#include <magic_enum.hpp>
#include "InputEvent.h"
#include "Keybord.h"
#include "PadInput.h"
#include "KeybordID.h"
#include "../_debug/_DebugConOut.h"
#include "../_debug/_DebugDispOut.h"

InputEvent::InputEvent(std::string filePath)
{
	filePath_ = filePath;
	InInit();
}

InputEvent::~InputEvent()
{
}

void InputEvent::Update(const double& delta)
{
	activeInput_->Update();
	SwitchInput();
}

float InputEvent::GetDigitalEvent(EventID id,InputState state)const
{
	if (eventTbl_.count(id)==0)
	{
		return false;
	}
	int type = static_cast<int>(activeInput_->GetInputType());
	for (const auto& keys_btns : eventTbl_.at(id).continer[type])//FlexibleInputは対応ボタンが複数ある時に入る
	{
		if(state == activeInput_->GetInputState(keys_btns))
		{
			return true;
		}
	}

	return false;
}

float InputEvent::GetAnalogEvent(AnalogInputID id)const
{
	return activeInput_->GetAnalogData(magic_enum::enum_name(id).data());
}

float InputEvent::GetAnalogEvent(EventID id1,EventID id2)const
{
	bool flag1 = GetDigitalEvent(id1, InputState::Push) || GetDigitalEvent(id1, InputState::Hold);
	bool flag2 = GetDigitalEvent(id2, InputState::Push) || GetDigitalEvent(id2, InputState::Hold);
	if (flag1 && !flag2)
	{
		return 1.0f;
	}
	if (!flag1 && flag2)
	{
		return -1.0f;
	}
	if (flag1 && flag2)
	{
		return 0.0f;
	}

	return 0.0f;
}

Vector2F InputEvent::GetAnalogVecEvent(AnalogInputID id1, AnalogInputID id2)const
{
	return Vector2F(GetAnalogEvent(id1), GetAnalogEvent(id2));
}

Vector2F InputEvent::GetAnalogVecEvent(Axis axis1, Axis axis2)const
{
	return Vector2F(GetAnalogEvent(axis1.first,axis1.second),GetAnalogEvent(axis2.first,axis2.second));
}

std::optional<float> InputEvent::GetDirAngle(AnalogInputID id, AnalogInputID id2, float offsetdeg)const
{
	auto dir = GetAnalogVecEvent(id, id2).normalized();
	auto r = atan2(dir.y, -dir.x);

	if (isnan(r))
	{
		return std::nullopt;
	}
	r += offsetdeg * DX_PI_F / 180.0f;
	if (r < 0)//ここで-を180度以上に拡張する
	{
		r = r + DX_TWO_PI_F;
	}

	return std::optional<float>(r * 360.0f / DX_TWO_PI_F);
}

std::optional<float> InputEvent::GetDirAngle(Axis axis1, Axis axis2, float offsetdeg)const
{
	auto dir = GetAnalogVecEvent(axis1, axis2).normalized();
	auto rad = atan2(dir.y, -dir.x);

	if (isnan(rad))
	{
		return std::nullopt;
	}
	rad += offsetdeg * DX_PI_F / 180.0f;
	if (rad < 0)//ここで-を180度以上に拡張する
	{
		rad = rad + DX_TWO_PI_F;
	}

	return std::optional<float>(rad * 360.0f / DX_TWO_PI_F);
}

void InputEvent::SetSensi(InputType type, float sensi)
{
	if (activeInput_->GetInputType() == type)
	{
		activeInput_->SetSensi(sensi);
	}
	else
	{
		noneActive_->SetSensi(sensi);
	}
}

float InputEvent::GetSensi(InputType type)
{
	if (activeInput_->GetInputType() == type)
	{
		return activeInput_->GetSensi();
	}
	return noneActive_->GetSensi();
}

void InputEvent::SetDeadZone(InputType type,float zone)
{
	if (activeInput_->GetInputType() == type)
	{
		activeInput_->SetDeadZone(zone);
	}
	else
	{
		noneActive_->SetDeadZone(zone);
	}
}

float InputEvent::GetDeadZone(InputType type)
{
	return 0.0f;
}

void InputEvent::FixCenterCursor(bool flag)
{
	activeInput_->FixCenterCursor(flag);
	noneActive_->FixCenterCursor(flag);
}

bool InputEvent::GetIsFixCenterCursor(void)
{
	return activeInput_->GetIsFixCenterCursor();
}

InputType InputEvent::GetInputType(void)
{
	return activeInput_->GetInputType();
}

void InputEvent::InInit()
{
	activeInput_ = std::make_unique<Keybord>();
	noneActive_ = std::make_unique<PadInput>(DX_INPUT_PAD1);

	Read();
	InputIDCheck();
}

void InputEvent::Write()
{
	nlohmann::json jsonfile;
	std::string eventName;
	std::string typeName;
	for (auto& eventID : eventTbl_)//defaultの書き込み
	{
		int type = 0;
		for (auto& typecontena : eventID.second.continer)
		{
			eventName = magic_enum::enum_name(eventID.first).data();
			if (magic_enum::enum_cast<InputType>(type).has_value())
			{
				typeName = magic_enum::enum_name(magic_enum::enum_cast<InputType>(type).value()).data();
				if (!typecontena.empty())
				{
					for (auto& key : typecontena)
					{
						jsonfile["default"][eventName][typeName].push_back(key);
					}
				}
				else
				{
					jsonfile["default"][eventName][typeName] = nullptr;
				}
			}
			type++;
		}
		jsonfile["default"][eventName]["isCanConfig"] = eventID.second.isCanConfig;
	}
	for (auto& eventID : eventTbl_)//configの書き込み
	{
		eventName = magic_enum::enum_name(eventID.first).data();
		auto b = jsonfile["default"][eventName]["isCanConfig"].get<bool>();
		if (b)
		{
			jsonfile["config"][eventName]["Keybord"] = jsonfile["default"][eventName]["Keybord"];
			jsonfile["config"][eventName]["Pad"] = jsonfile["default"][eventName]["Pad"];
		}
	}

	std::ofstream file(filePath_);
	file << jsonfile.dump(2) << std::endl;
}

void InputEvent::SaveConfig()
{
	std::ifstream file(filePath_);
	if(file.good())
	{
		nlohmann::json json;
		file >> json;
		for(const auto& eventSet : eventTbl_)
		{
			if(!eventSet.second.isCanConfig)//configとして書き換えが有効か？
			{
				continue;
			}
			const auto& keybord_KeyIDs = eventSet.second.continer[static_cast<int>(InputType::Keybord)];
			const auto& pad_KeyIDs = eventSet.second.continer[static_cast<int>(InputType::Pad)];
			
			if(!keybord_KeyIDs.empty())//空じゃない時
			{
				auto eventName = magic_enum::enum_name<EventID>(eventSet.first);
				auto& jdata = json["config"][eventName.data()];
				if(!jdata["Keybord"].is_null())
				{
					jdata["Keybord"].array() = keybord_KeyIDs;
				}
			}

		}

		std::ofstream f("test.txt");
		f << json.dump(2) << std::endl;
	}
}

bool InputEvent::ChangeEventKeyInput(EventID eventID,InputType type)
{
	if(eventTbl_[eventID].isCanConfig)
	{
		if(type == InputType::Keybord)
		{
			char keys[256];
			GetHitKeyStateAll(keys);
			for(int i = 0; i < 256; i++)//押されたキーを登録(同時押しが来たときは配列に入っている情報が早いのが登録される)
			{
				if(keys[i])
				{
					eventTbl_[eventID].continer[static_cast<int>(type)].clear();
					eventTbl_[eventID].continer[static_cast<int>(type)].push_back(magic_enum::enum_name(magic_enum::enum_cast<KeybordID>(i).value()).data());
					break;
				}
			}
		}
		else if(type == InputType::Pad)
		{

		}
	}
	return false;
}

bool InputEvent::Read(void)
{
	std::ifstream file(filePath_);
	if (file.good())
	{
		nlohmann::json json;
		file >> json;
		for (auto& it : json["default"].items())
		{
			auto eventId = magic_enum::enum_cast<EventID>(it.key()).value();
			auto& keybord = it.value()["Keybord"];
			auto& pad = it.value()["Pad"];
			FlexibleInput keys;
			FlexibleInput btns;
			if (!keybord.is_null())
			{
				keys = keybord;
			}
			if (!pad.is_null())
			{
				btns = pad;
			}
			if (!it.value()["isCanConfig"].get<bool>())
			{
				eventTbl_[eventId].continer[0] = keys;
				eventTbl_[eventId].continer[1] = btns;
			}
			else
			{
				if (!json["config"].find(it.key()).value()["Keybord"].is_null())
				{
					eventTbl_[eventId].continer[0] = json["config"].find(it.key()).value()["Keybord"];
				}
				if (!json["config"].find(it.key()).value()["Pad"].is_null())
				{
					eventTbl_[eventId].continer[1] = json["config"].find(it.key()).value()["Pad"];
				}
				eventTbl_[eventId].isCanConfig = true;
			}
		}
	}
	else
	{
		return false;
	}
	return true;
}

void InputEvent::InputIDCheck(void)
{
	int errorCnt = 0;
	std::string errorMes;
	for (const auto& Event : eventTbl_)//ORVectorは対応ボタンが複数ある時に入る
	{
		for (const auto& Container : Event.second.continer)
		{
			for (const auto& id : Container)
			{
				if (magic_enum::enum_cast<KeybordID>(id) ||	magic_enum::enum_cast<PadInputID>(id) || 
					magic_enum::enum_cast<AnalogInputID>(id) ||	magic_enum::enum_cast<MouseInputID>(id)
					)
				{
					continue;
				}
				errorCnt++;
				errorMes.append("DifferenceList\neventID:");
				errorMes.append(magic_enum::enum_name(Event.first).data());
				errorMes.append("\n");
				TRACE("%s\n", magic_enum::enum_name(Event.first).data());
			}
		}
	}
	if (errorCnt > 0)
	{
		std::ofstream writing_file;

		auto tz = std::chrono::locate_zone("Asia/Tokyo");
		auto now = std::chrono::system_clock::now();
		auto now_sec = std::chrono::floor<std::chrono::seconds>(tz->to_local(now));
		auto time = std::format("{:%Y%m%d_%H%M%S}", now_sec);
		writing_file.open("InputID_DifferenceReport_"+time+".txt", std::ios::out);
		writing_file << errorMes << std::endl;
		writing_file.close();
	}
	assert(!(errorCnt > 0));
}

void InputEvent::SwitchInput()
{
	if (activeInput_->IsActive())
	{
		return;
	}
	noneActive_->Update();
	if(noneActive_->IsActive())
	{
		activeInput_.swap(noneActive_);
	}
}

void InputEvent::DebugDraw(void)
{
#if _DEBUG
	_TRACE_M(0xffffff, "現在の入力機器:%s", magic_enum::enum_name(activeInput_->GetInputType()).data());
	for (auto event : EventID())
	{
		_TRACE_M(0xffffff, "%s::(None:%s Push:%s Hold:%s Relese:%s)", magic_enum::enum_name(event).data(),
			GetDigitalEvent(event, InputState::None) ? "True" : "False",
			GetDigitalEvent(event, InputState::Push) ? "True" : "False",
			GetDigitalEvent(event, InputState::Hold) ? "True" : "False",
			GetDigitalEvent(event, InputState::Relese) ? "True" : "False"
		);
	}
	_TRACE_M(0xffffff, "ポインター位置:%s", GetAnalogVecEvent(AnalogInputID::CURSOR_X, AnalogInputID::CURSOR_Y).toStr().c_str());
	_TRACE_M(0xffffff, "ポインター移動量:%s", GetAnalogVecEvent(AnalogInputID::CURSOR_MOVED_X, AnalogInputID::CURSOR_MOVED_Y).toStr().c_str());
	TRACE("ポインター移動量:%s\n", GetAnalogVecEvent(AnalogInputID::CURSOR_MOVED_X, AnalogInputID::CURSOR_MOVED_Y).toStr().c_str());
#endif
}
