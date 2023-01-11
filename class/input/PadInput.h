#pragma once
#include <DxLib.h>
#include <memory>
#include <optional>
#include "Input.h"
#include "../common/Vector2.h"

class PadInput:public Input
{
public:
	PadInput(int padNo);
	~PadInput();

	void Update(void)override;

	/// @brief 入力機器のタイプを取得
	/// @return 入力機器タイプ
	InputType GetInputType(void)const override { return InputType::PAD; };

	/// @brief ボタンの状態を取得する
	/// @param keyid enumからstringに変換したkeyid
	/// @return ボタン状態
	InputState GetInputState(std::string_view keyid)override;

	/// @brief アナログ値の取得する
	/// @param keyid enumからstringに変換したkeyid
	/// @return アナログ値
	float GetAnalogData(std::string_view keyid)override;

	/// @brief スティックの倒した方向の角度を取得する
	/// @param dir 指定するスティック
	/// @return 上方向を0度として時計回りに360度までの間を返す(度数法)(倒れてない時，無効値を返す)
	std::optional<float> GetDirRot(StickLR dir);

	/// @brief スティックの倒したベクトルを返す
	/// @param dir 指定するスティック
	/// @return 0~1の倒した値(DeadZoneの中だったら(0,0)で返す)
	Vector2F GetMoveVec(StickLR dir);

	/// @brief 0~0.999の間でデッドゾーンを設定する
	/// @param zone 0~1の値(範囲外の値はclampされる)
	void SetDeadZone(float zone)override;

	/// @brief 入力があるか
	/// @return 入力あり:true 入力なし:false
	bool IsActive(void)override;
private:
	/// @brief インスタンス内での初期化 
	void InInit(void)override;

	/// @brief ボタンなどのboolで決まる入力を更新する
	void UpdateDigital(void);

	/// @brief スティックを倒しているかを更新する
	void UpdateStickDigitalButton(void);

	/// @brief スティック入力やトリガーの深度などのアナログ入力を更新する
	void UpdateAnalog(void);

	/// @brief スティックの倒した方向の角度を返す
	/// @param x スティックの横軸
	/// @param y スティックの縦軸
	/// @return 上方向を0度として時計回りに360度までの間を返す(倒れてない時，無効値を返す)
	std::optional<float> GetMoveDirRot(short x, short y);
	
	/// @brief スティックの縦横の倒した時の値を0~1の間に正規化した値を返す
	/// @param x スティックの横軸
	/// @param y スティックの縦軸
	/// @return 0~1の倒した値(DeadZoneの中だったら(0,0)で返す)
	Vector2F GetMoveVec(short x, short y);

	/// @brief デッドゾーン内ならゼロにする
	/// @param in 補正するスティックの倒したベクトル
	/// @return 補正後のスティックの倒したベクトル
	Vector2F CorrectDeadZone(Vector2F in);

	/// @brief デバッグ表示
	void DebugDraw(void);

	const int padNo_;										//パッドの個体番号
	XINPUT_STATE xInput_;									//XInputのデータを受け取る変数
	XPadData padData_;										//Padの入力保管場所
	std::unordered_map<PadInputID, unsigned int> btnTbl_;	//PadInputIDとDxlibのパッドのビットをテーブル化
	Vector2F oldCursorPos_;									//カーソル位置の前フレームの座標
	std::pair<int, int> connectNum_;						//パッドの接続状態 first:Now,second:Old
	int isConnectXPad_;										//パッドがいくつつながっているか
};

