#pragma once
#include <unordered_map>
#include <array>
#include <vector>
#include <string>
#include "PadInputID.h"
#include "AnalogInputID.h"
#include "MouseInputID.h"
#include "../common/Vector2.h"

enum class Trg {
	NOW,	//現在のフレーム
	OLD,	//1フレーム前のフレーム
	MAX
};
enum class InputType {
	KEYBOARD,
	PAD,
	MAX
};
enum class InputState
{
	NONE,		//何もしてない	now:false,old:false
	PUSH,		//押した瞬間	now:true,old:false
	RELEASE,	//離した瞬間	now:false,old:true
	HOLD,		//押している間	now:true,old:true
	MAX
};
enum class StickLR
{
	L,
	R,
	MAX
};
using TrgBool = std::unordered_map<Trg, bool>;//どのタイミングの押されてるか
using XPadData = std::unordered_map<PadInputID, TrgBool>;//押されてるボタンといつ押されたか
using KeyState = std::array<char, 256U>;
using KeyboardData = std::unordered_map<Trg,KeyState>;
using MouseData = std::unordered_map<MouseInputID, TrgBool>;
using AnalogData = std::unordered_map<AnalogInputID, float>;
using MousePointer = std::unordered_map<Trg, Vector2>;//now,old
class Input
{
public:
	Input();
	virtual ~Input();
	virtual void Update(void) = 0;

	/// @brief 入力機器のタイプを取得
	/// @return 入力機器タイプ
	[[nodiscard]] virtual InputType GetInputType(void)const = 0;

	/// @brief ボタンの状態を取得する
	/// @param keyid enumからstringに変換したkeyid
	/// @return ボタン状態
	virtual InputState GetInputState(std::string_view keyid)=0;

	/// @brief アナログ値の取得する
	/// @param keyid enumからstringに変換したkeyid
	/// @return アナログ値
	virtual float GetAnalogData(std::string_view keyid) = 0;

	/// @brief 入力があるか
	/// @return 入力あり:true 入力なし:false
	virtual bool IsActive(void) = 0;

	/// @brief 指定した入力機器の感度をセットする
	/// @param sensitivity 0.01~20.0
	void SetSensitivity(float sensitivity);

	/// @brief 指定した入力機器の感度を取得する
	/// @return 0.01~20.0
	[[nodiscard]] float GetSensitivity(void) const { return sensitivity_; }

	/// @brief 指定した入力機器のデッドゾーンをセットする
	/// @param zone 0.0~1.0
	virtual void SetDeadZone(float zone);

	/// @brief 指定した入力機器のデッドゾーンを取得する
	/// @return 1.0~0.0の間のデッドゾーン
	[[nodiscard]] float GetDeadZone(void) const { return deadZone_; }

	/// @brief マウスポインターをセンター固定する
	/// @param flag true:固定 false:自由
	void FixCenterCursor(bool flag);

	/// @brief マウスカーソルをセンターに固定しているか
	/// @return true:固定 false:自由
	[[nodiscard]] bool GetIsFixCenterCursor(void) const { return isFixCenterCursor_; }
private:
	/// @brief インスタンス内での初期化 
	virtual void InInit(void) = 0;
protected:
	/// @brief isFixCenterCursorがtrueの時，画面中央にセットする 
	void DoCenterCursor(void);

	AnalogData analogData_;		//アナログ値(トリガーやスティックなど)
	float sensitivity_;			//カーソルの感度(アナログ値に掛ける値)
	float deadZone_;			//スティックのデッドゾーン範囲
	bool isFixCenterCursor_;	//画面中央に固定するか
};

