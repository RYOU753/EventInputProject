#pragma once
#include "Input.h"
#include "../common/Vector2.h"

class Keyboard :
	public Input
{
public:
	Keyboard();
	~Keyboard();
	void Update(void)override;

	/// @brief 入力機器のタイプを取得
	/// @return 入力機器タイプ
	InputType GetInputType(void)const override;

	/// @brief 指定した入力IDの状態を取得する
	/// @param keyid キーボードかマウスの入力IDの文字列
	/// @return 指定された入力IDの状態
	InputState GetInputState(std::string_view keyid)override;

	/// @brief キーボードとマウスのアナログ入力値を取得する
	/// @param keyid キーボードかマウスの入力IDの文字列
	/// @return 指定された入力IDのアナログ入力値
	float GetAnalogData(std::string_view keyid)override;

	/// @brief キーボードを現在使っているかを判定する 
	/// @return true:使っている false:使っていない
	bool IsActive(void)override;
private:
	/// @brief インスタンス内での初期化 
	void InInit(void)override;

	/// @brief キーボード入力の更新 
	void UpdateKeyboard(void);

	/// @brief マウス入力の更新
	void UpdateMouse(void);

	KeyboardData keybordData_;							//キーボードの入力データ
	MouseData mouseData_;								//マウスのスイッチ入力データ
	std::unordered_map<MouseInputID, int> clickTbl_;	//MouseInputIDとDxLibのビットをテーブルにしている
	Vector2F oldCursorPos_;								//カーソル位置の前フレームの座標
};
