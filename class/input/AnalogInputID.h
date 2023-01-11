#pragma once
enum class AnalogInputID
{
	PAD_STICK_LX,		//左スティックの横の値
	PAD_STICK_LY,		//左スティックの縦の値
	PAD_STICK_RX,		//右スティックの横の値
	PAD_STICK_RY,		//右スティックの縦の値
	PAD_TRIGGER_L,		//左トリガーの押し込み値
	PAD_TRIGGER_R,		//右トリガーの押し込み値
	CURSOR_MOVED_X,		//カーソルの移動量X
	CURSOR_MOVED_Y,		//カーソルの移動量Y
	CURSOR_X,			//カーソル位置X
	CURSOR_Y,			//カーソル位置Y
	Max
};