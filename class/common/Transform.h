#pragma once
#include <DxLib.h>
#include <optional>
#include "Quaternion.h"
//#if __has_include("../jsonConvert/TransPtr_JSON.h")
//	#include "../jsonConvert/TransPtr_JSON.h"
//#endif
//#if __has_include("../jsonConvert/TransUniPtr_JSON.h")
//	#include "../jsonConvert/TransUniPtr_JSON.h"
//#endif

/// <summary>
/// モデル制御の基本情報
/// 大きさ：VECTOR基準
/// 回転　：Quaternion基準
/// 位置　：VECTOR基準
/// </summary>
class Transform
{

public:
	Transform(void);
	Transform(VECTOR pos, Quaternion qRot, VECTOR scale, Quaternion qRotLocal = Quaternion{});
	~Transform();

	//大きさをセット
	void SetScale(VECTOR scl);
	//座標をセット
	void SetPosition(VECTOR pos);
	//回転をセット
	void SetQuaternionRot(Quaternion qua);
	//X軸だけ回転
	void SetRotX(float rotx);
	//Y軸だけ回転
	void SetRotY(float roty);
	//Z軸だけ回転
	void SetRotZ(float rotz);
	void SetQuaternionRotLocal(Quaternion quaLocal);

	//X軸だけ回転(ローカル)
	void SetRotLocalX(const float& rotx);
	//Y軸だけ回転(ローカル)
	void SetRotLocalY(const float& roty);
	//Z軸だけ回転(ローカル)
	void SetRotLocalZ(const float& rotz);
	//大きさを取得
	const VECTOR& GetScale(void) const{ return scl; };
	//座標を取得
	const VECTOR& GetPosition(void) const { return pos; };
	//回転を取得
	Quaternion GetQuaternionRot(void) { return quaRot; };
	const Quaternion& GetQuaternionLocalRot(void)const { return quaRotLocal; };

	// 前方方向を取得
	const VECTOR&& GetForward(void);

	// 後方方向を取得
	const VECTOR&& GetBack(void);

	// 右方向を取得
	const VECTOR&& GetRight(void);

	// 左方向を取得
	const VECTOR&& GetLeft(void);

	// 上方向を取得
	const VECTOR&& GetUp(void);

	// 下方向を取得
	const VECTOR&& GetDown(void);

	// 対象方向を取得
	const VECTOR&& GetDir(VECTOR vec);

public:
private:
	// 大きさ
	VECTOR scl;
	// 回転
	VECTOR rot;
	// 位置
	VECTOR pos;

	MATRIX matScl;
	MATRIX matRot;
	MATRIX matPos;
	MATRIX matAll;
	// 回転
	Quaternion quaRot;

	// ローカル回転
	Quaternion quaRotLocal;
};

