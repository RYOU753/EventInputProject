#pragma once
#include <memory>
#include <vector>
#include <list>
#include <optional>
#include "EventID.h"
#include "Input.h"
#include "../common/Vector2.h"
#include "AnalogInputID.h"

using Axis = std::pair<EventID, EventID>;
using FlexibleInput = std::vector<std::string>;
using InputTypeContena = std::array<FlexibleInput, 2U>;

struct EventData
{
	EventData() :isCanConfig(false){}
	InputTypeContena container;
	bool isCanConfig;
};

class InputEvent
{
public:
	explicit InputEvent(std::string filePath);
	~InputEvent();
	/// @brief 入力機器の情報更新とPadと切り替えがあるかまた接続検知をする
	/// @param delta デルタカウンタ
	void Update(const double& delta);

	/// @brief EventIDと紐づいてるボタンの状態がみたい状態かを調べる
	/// @param id 登録したイベント
	/// @param state 見たいボタンの状態
	/// @return 見たいボタンの状態だったら:true|そうじゃない:false
	[[nodiscard]] float GetDigitalEvent(EventID id,InputState state = InputState::NONE)const;

	/// @brief 紐づいてるAnalogInputIDのアナログ値を取得
	/// @return 指定のアナログ値
	[[nodiscard]] float GetAnalogEvent(AnalogInputID id)const;
	
	/// @brief EventIDからボタン情報を取得し，id1が押されてら1.0f,id2がおされてたら-1.0fで
	/// AnalogInputIDが入ってたら1.0f~-1.0fを取得する
	/// @param id1 +方向の入力
	/// @param id2 -方向の入力
	/// @return 1.0f~-1.0fを取得する
	[[nodiscard]] float GetAnalogEvent(EventID id1, EventID id2)const;

	/// @brief アナログ値を二つ取得してvecやposのように扱う
	/// @param id1 横方向の値
	/// @param id2 縦方向の値
	/// @return 方向ベクトルや座標
	[[nodiscard]] Vector2F GetAnalogVecEvent(AnalogInputID id1, AnalogInputID id2)const;

	/// @brief 二つの軸からvecやposを作成する
	/// @param axis1 x軸(+方向の入力,-方向の入力)
	/// @param axis2 y軸(+方向の入力,-方向の入力)
	/// @return 方向ベクトルや座標
	[[nodiscard]] Vector2F GetAnalogVecEvent(Axis axis1, Axis axis2)const;
	
	/// @brief コントローラスティックのたおした方向の角度やマウスを動かした方向の角度を求める
	/// @param id x値
	/// @param id2 y値
	/// @param offsetDeg 0度の基準位置をずらす
	/// @returns 度数法(たおしてない時は中身がない)右が0度上が90度
	[[nodiscard]] std::optional<float> GetDirAngle(AnalogInputID id, AnalogInputID id2,float offsetDeg= 0.0f)const;

	/// @brief digitalのスティックとanalogのスティックが同じORVectorの中にいると正確な値が取れない場合があります．
	/// @param axis1 x軸(+方向の入力,-方向の入力)
	/// @param axis2 y軸(+方向の入力,-方向の入力)
	/// @param offsetDeg 0度の基準位置をずらす
	/// @return 度数法(たおしてない時は中身がない)右が0度上が90度
	[[nodiscard]] std::optional<float> GetDirAngle(const Axis& axis1,const Axis& axis2,const float& offsetDeg = 0.0f)const;
	
	/// @brief 指定した入力機器の感度をセットする \n
	/// 0.01~20.0の範囲でセットするようになっている
	/// @param type 入力機器種
	/// @param sensitivity 0.01~20.0の範囲でセットする
	void SetSensitivity(InputType type, float sensitivity) const;

	/// @brief 指定した入力機器の感度を取得する
	/// @return 0.01~20.0の間の感度
	[[nodiscard]] float GetSensitivity(InputType type) const;

	/// @brief 指定した入力機器のデッドゾーンをセットする
	/// @param type 入力機器種
	/// @param zone 0.0~1.0
	void SetDeadZone(InputType type,float zone) const;

	/// @brief 指定した入力機器のデッドゾーンを取得する
	/// @return 1.0~0.0の間のデッドゾーン
	float GetDeadZone(InputType type);
	
	/// @brief マウスポインターをセンター固定する
	/// @param flag true:固定 false:自由
	void FixCenterCursor(bool flag) const;

	/// @brief マウスカーソルをセンターに固定しているか
	/// @return true:固定 false:自由
	[[nodiscard]] bool GetIsFixCenterCursor(void) const;

	/// @brief 現在使っている入力機器の種類を返す
	/// @returns 入力機器の種類
	[[nodiscard]] InputType GetInputType(void) const;

	/// @brief 登録されているイベントを入力されているかデバッグ表示する 
	void DebugDraw(void) const;

	/// @brief コンフィグをjson形式で保存する
	void SaveConfig() const;
private:
	/// @brief インスタンス時の初期化処理
	void InInit(void);

	/// @brief jsonファイルにEventTblの中身を書いて記録する
	void Write();
	bool ChangeEventKeyInput(EventID eventID,InputType type);
	/// @brief jsonファイルの読み込みをしEventTblをロードする
	/// @return jsonファイルがある:true | ない:false
	bool Read(void);

	/// @brief jsonに書き込まれた情報とenum classにあるkeyidが一致しているかを調べる
	/// 一致してなかったらログファイルを残して強制終了する
	void InputIDCheck(void) const;

	/// @brief 入力機器が使われてるかを調べ，使われてなかったらnoneActiveを調べ使われていたら切り替える
	void SwitchInput();

	std::unique_ptr<Input> activeInput_;	//現在使っている入力
	std::unique_ptr<Input> noneActive_;		//現在使われてない入力
	std::unique_ptr<class Keyboard> keyboard_;
	std::list<std::unique_ptr<class PadInput>> padList_;

	std::pair<int, int> connectNum_;		//padの接続数(Now,Old)

	std::unordered_map<EventID, EventData> eventTbl_;

	std::string filePath_;
};
