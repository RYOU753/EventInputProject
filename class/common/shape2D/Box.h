#pragma once
#include "Shape.h"

enum class BOX_PLACE_TYPE
{
	LT,//左上
	LB,//左下
	RT,//右上
	RB,//右下
	CT,//上辺の中央
	CB,//下辺の中央
	CL,//左辺の中央
	CR,//右辺の中央
	CC,//四角の中心
	MAX
};

class Box :
    public Shape
{
public:
	Box(BOX_PLACE_TYPE placeType, Position2F pos, Vector2F size);
	~Box();
	//自身の形のタイプを取得する
	ShapeType GetShapeType(void)const override;
	//DEBUG時にBoxを描画する
	void dbgDraw(int color, bool isFill = true)const override;
	//Boxを描画する
	void Draw(int color, bool isFill = true)const override;
	/// <summary>
	/// 指定した座標を取得する
	/// </summary>
	/// <param name="placeType">Boxの取得したい場所</param>
	/// <returns>指定した座標</returns>
	Position2F GetSelectPos(BOX_PLACE_TYPE placeType)const;
	/// <summary>
	/// Boxの大きさを設定する
	/// </summary>
	/// <param name="size">(幅，高さ)</param>
	void SetSize(Vector2F size);
	/// <summary>
	/// Boxの大きさを取得する
	/// </summary>
	/// <returns>Boxの大きさ</returns>
	const Vector2F& GetSize(void)const;
	/// <summary>
	/// Boxの起点となる場所を変更する
	/// </summary>
	/// <param name="placeType">起点となる場所名</param>
	void ChangeBasePosType(BOX_PLACE_TYPE placeType);
	const BOX_PLACE_TYPE& GetBasePosType(){
		return type_;
	};
	bool IsHit(Position2 pos,bool inLine)override;
private:
	Vector2F size_;
	BOX_PLACE_TYPE type_;
};

