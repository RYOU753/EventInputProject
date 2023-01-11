#pragma once
#include "Vector2.h"

class Transform2D
{
public:
	Transform2D(void);
	~Transform2D();
	//座標XYを設定
	void SetPos(Position2F pos);
	//座標Xを設定
	void SetPosX(float x);
	//座標Yを設定
	void SetPosY(float y);
	//座標を取得
	const Position2F& GetPos(void);
	/// <summary>
	/// 度数法の引数分回転する +方向右回転 -方向左回転
	/// </summary>
	///<param name="deg">追加する値(度数法)</param>
	void RotateDeg(float deg);
	/// <summary>
	/// 弧度法の引数分回転する +方向右回転 -方向左回転
	/// </summary>
	///<param name="rad">追加する値(弧度法)</param>
	void RotateRad(float rad);
	//度数法で指定した値を設定
	///<param name="rotationDeg">追加する値(度数法)</param>
	void SetRotationDeg(float rotationDeg);
	/// <summary>
	///弧度法で指定した値を設定
	/// </summary>
	///<param name="rotationRad">追加する値(弧度法)</param>
	void SetRotationRad(float rotationRad);
	/// <summary>
	/// 回転値を取得
	/// </summary>
	/// <returns>ラジアン値</returns>
	const float& GetRotation(void);
	//拡大値を設定
	void SetScale(float scale);
	//拡大値を取得
	const float& GetScale(void);
private:
	Position2F position_;
	float rotation_;//ラジアン値
	float scale_;
};
