#include <DxLib.h>
#include <iostream>
#include "class/_debug/_DebugConOut.h"
#include "class/_debug/_DebugDispOut.h"
#include "class/input/InputEvent.h"

using namespace std;

int WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	ChangeWindowMode(true);
	SetGraphMode(640, 480, 32);
	DxLib_Init();
	_dbgSetup(640, 480, 255);
	auto input = InputEvent("resource/data/json/KeyConfig.json");
	while (ProcessMessage() != -1 && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		_dbgStartDraw();
		//Update
		input.Update(0.5);
		input.DebugDraw();
		if(input.GetDigitalEvent(EventID::ShotBall, InputState::Relese))
		{
			//input.FixCenterCursor(!input.GetIsFixCenterCursor());
			input.SaveConfig();
		}
		//Draw
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		DrawCircle(input.GetAnalogEvent(AnalogInputID::CURSOR_X), input.GetAnalogEvent(AnalogInputID::CURSOR_Y), 3, 0xff0000, true);
		_dbgDraw();
		ScreenFlip();
	}


	DxLib_End();
	return 0;
}
