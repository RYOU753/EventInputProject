#pragma once
#include <unordered_map>
enum class KeybordID
{
	KEY_BACK,				// BackSpaceキー		D_DIK_BACK
	KEY_TAB,				// Tabキー			D_DIK_TAB
	KEY_RETURN,				// Enterキー			D_DIK_RETURN

	KEY_LSHIFT,				// 左Shiftキー		D_DIK_LSHIFT
	KEY_RSHIFT ,			// 右Shiftキー		D_DIK_RSHIFT
	KEY_LCONTROL ,			// 左Ctrlキー		D_DIK_LCONTROL
	KEY_RCONTROL ,			// 右Ctrlキー		D_DIK_RCONTROL
	KEY_ESCAPE ,			// Escキー			D_DIK_ESCAPE
	KEY_SPACE ,				// スペースキー		D_DIK_SPACE
	KEY_PGUP ,				// PageUpキー		D_DIK_PGUP
	KEY_PGDN ,				// PageDownキー		D_DIK_PGDN
	KEY_END ,				// Endキー			D_DIK_END
	KEY_HOME ,				// Homeキー			D_DIK_HOME
	KEY_LEFT,				// 左キー			D_DIK_LEFT
	KEY_UP,					// 上キー			D_DIK_UP
	KEY_RIGHT,				// 右キー			D_DIK_RIGHT
	KEY_DOWN,				// 下キー			D_DIK_DOWN
	KEY_INSERT,				// Insertキー		D_DIK_INSERT
	KEY_DELETE,				// Deleteキー		D_DIK_DELETE

	KEY_MINUS,				// －キー							D_DIK_MINUS
	KEY_YEN,				// ￥キー							D_DIK_YEN
	KEY_PREVTRACK,			// ＾キー							D_DIK_PREVTRACK
	KEY_PERIOD,				// ．キー							D_DIK_PERIOD
	KEY_SLASH,				// ／キー							D_DIK_SLASH
	KEY_LALT,				// 左Altキー							D_DIK_LALT
	KEY_RALT,				// 右Altキー							D_DIK_RALT
	KEY_SCROLL,				// ScrollLockキー					D_DIK_SCROLL
	KEY_SEMICOLON,			// ；キー							D_DIK_SEMICOLON
	KEY_COLON,				// ：キー							D_DIK_COLON
	KEY_LBRACKET,			// ［キー							D_DIK_LBRACKET
	KEY_RBRACKET,			// ］キー							D_DIK_RBRACKET
	KEY_AT,					// ＠キー							D_DIK_AT
	KEY_BACKSLASH,			// ＼キー							D_DIK_BACKSLASH
	KEY_COMMA,				// ，キー							D_DIK_COMMA
	KEY_KANJI,				// 漢字キー							D_DIK_KANJI
	KEY_CONVERT,			// 変換キー							D_DIK_CONVERT
	KEY_NOCONVERT,			// 無変換キー						D_DIK_NOCONVERT
	KEY_KANA,				// カナキー							D_DIK_KANA
	KEY_APPS,				// アプリケーションメニューキー		D_DIK_APPS
	KEY_CAPSLOCK,			// CaspLockキー						D_DIK_CAPSLOCK
	KEY_SYSRQ,				// PrintScreenキー					D_DIK_SYSRQ
	KEY_PAUSE,				// PauseBreakキー					D_DIK_PAUSE
	KEY_LWIN,				// 左Winキー							D_DIK_LWIN
	KEY_RWIN,				// 右Winキー							D_DIK_RWIN

	KEY_NUMLOCK,			// テンキーNumLockキー		D_DIK_NUMLOCK
	KEY_NUMPAD0,			// テンキー０				D_DIK_NUMPAD0
	KEY_NUMPAD1,			// テンキー１				D_DIK_NUMPAD1
	KEY_NUMPAD2,			// テンキー２				D_DIK_NUMPAD2
	KEY_NUMPAD3,			// テンキー３				D_DIK_NUMPAD3
	KEY_NUMPAD4,			// テンキー４				D_DIK_NUMPAD4
	KEY_NUMPAD5,			// テンキー５				D_DIK_NUMPAD5
	KEY_NUMPAD6,			// テンキー６				D_DIK_NUMPAD6
	KEY_NUMPAD7,			// テンキー７				D_DIK_NUMPAD7
	KEY_NUMPAD8,			// テンキー８				D_DIK_NUMPAD8
	KEY_NUMPAD9,			// テンキー９				D_DIK_NUMPAD9
	KEY_MULTIPLY,			// テンキー＊キー			D_DIK_MULTIPLY
	KEY_ADD,				// テンキー＋キー			D_DIK_ADD
	KEY_SUBTRACT,			// テンキー－キー			D_DIK_SUBTRACT
	KEY_DECIMAL,			// テンキー．キー			D_DIK_DECIMAL
	KEY_DIVIDE,				// テンキー／キー			D_DIK_DIVIDE
	KEY_NUMPADENTER,		// テンキーのエンターキー	D_DIK_NUMPADENTER

	KEY_F1,			// Ｆ１キー			D_DIK_F1
	KEY_F2,			// Ｆ２キー			D_DIK_F2
	KEY_F3,			// Ｆ３キー			D_DIK_F3
	KEY_F4,			// Ｆ４キー			D_DIK_F4
	KEY_F5,			// Ｆ５キー			D_DIK_F5
	KEY_F6,			// Ｆ６キー			D_DIK_F6
	KEY_F7,			// Ｆ７キー			D_DIK_F7
	KEY_F8,			// Ｆ８キー			D_DIK_F8
	KEY_F9,			// Ｆ９キー			D_DIK_F9
	KEY_F10,		// Ｆ１０キー		D_DIK_F10
	KEY_F11,		// Ｆ１１キー		D_DIK_F11
	KEY_F12,		// Ｆ１２キー		D_DIK_F12

	KEY_A,			// Ａキー			D_DIK_A
	KEY_B,			// Ｂキー			D_DIK_B
	KEY_C,			// Ｃキー			D_DIK_C
	KEY_D,			// Ｄキー			D_DIK_D
	KEY_E,			// Ｅキー			D_DIK_E
	KEY_F,			// Ｆキー			D_DIK_F
	KEY_G,			// Ｇキー			D_DIK_G
	KEY_H,			// Ｈキー			D_DIK_H
	KEY_I,			// Ｉキー			D_DIK_I
	KEY_J,			// Ｊキー			D_DIK_J
	KEY_K,			// Ｋキー			D_DIK_K
	KEY_L,			// Ｌキー			D_DIK_L
	KEY_M,			// Ｍキー			D_DIK_M
	KEY_N,			// Ｎキー			D_DIK_N
	KEY_O,			// Ｏキー			D_DIK_O
	KEY_P,			// Ｐキー			D_DIK_P
	KEY_Q,			// Ｑキー			D_DIK_Q
	KEY_R,			// Ｒキー			D_DIK_R
	KEY_S,			// Ｓキー			D_DIK_S
	KEY_T,			// Ｔキー			D_DIK_T
	KEY_U,			// Ｕキー			D_DIK_U
	KEY_V,			// Ｖキー			D_DIK_V
	KEY_W,			// Ｗキー			D_DIK_W
	KEY_X,			// Ｘキー			D_DIK_X
	KEY_Y,			// Ｙキー			D_DIK_Y
	KEY_Z,			// Ｚキー			D_DIK_Z

	KEY_0,			// ０キー			D_DIK_0
	KEY_1,			// １キー			D_DIK_1
	KEY_2,			// ２キー			D_DIK_2
	KEY_3,			// ３キー			D_DIK_3
	KEY_4,			// ４キー			D_DIK_4
	KEY_5,			// ５キー			D_DIK_5
	KEY_6,			// ６キー			D_DIK_6
	KEY_7,			// ７キー			D_DIK_7
	KEY_8,			// ８キー			D_DIK_8
	KEY_9			// ９キー			D_DIK_9
};
