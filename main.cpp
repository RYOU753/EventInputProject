#include <DxLib.h>
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
		//Draw
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		_dbgDraw();
		ScreenFlip();
	}


	DxLib_End();
	return 0;
}
