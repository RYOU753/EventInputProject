#pragma once
#include <DxLib.h>

enum class KeybordID
{
 KEY_BACK =	(0x0E),				// BackSpaceキー	D_DIK_BACK
 KEY_TAB = (0x0F),				// Tabキー			D_DIK_TAB
 KEY_RETURN = (0x1C),			// Enterキー		D_DIK_RETURN

 KEY_LSHIFT = (0x2A),			// 左Shiftキー		D_DIK_LSHIFT
 KEY_RSHIFT = (0x36),			// 右Shiftキー		D_DIK_RSHIFT
 KEY_LCONTROL = (0x1D),			// 左Ctrlキー		D_DIK_LCONTROL
 KEY_RCONTROL = (0x9D),			// 右Ctrlキー		D_DIK_RCONTROL
 KEY_ESCAPE = (0x01),			// Escキー			D_DIK_ESCAPE
 KEY_SPACE = (0x39),			// スペースキー		D_DIK_SPACE
 KEY_PGUP = (0xC9),				// PageUpキー		D_DIK_PGUP
 KEY_PGDN = (0xD1),				// PageDownキー		D_DIK_PGDN
 KEY_END = (0xCF),				// Endキー			D_DIK_END
 KEY_HOME = (0xC7),				// Homeキー			D_DIK_HOME
 KEY_LEFT = (0xCB),				// 左キー			D_DIK_LEFT
KEY_UP = (0xC8),				// 上キー			D_DIK_UP
KEY_RIGHT = (0xCD),			// 右キー			D_DIK_RIGHT
KEY_DOWN = (0xD0),				// 下キー			D_DIK_DOWN
KEY_INSERT = (0xD2),			// Insertキー		D_DIK_INSERT
KEY_DELETE = (0xD3),			// Deleteキー		D_DIK_DELETE

KEY_MINUS = (0x0C),			// −キー			D_DIK_MINUS
KEY_YEN = (0x7D),				// ￥キー			D_DIK_YEN
KEY_PREVTRACK = (0x90),		// ＾キー			D_DIK_PREVTRACK
KEY_PERIOD = (0x34),			// ．キー			D_DIK_PERIOD
KEY_SLASH = (0x35),			// ／キー			D_DIK_SLASH
KEY_LALT = (0x38),				// 左Altキー		D_DIK_LALT
KEY_RALT = (0xB8),				// 右Altキー		D_DIK_RALT
KEY_SCROLL = (0x46),			// ScrollLockキー	D_DIK_SCROLL
KEY_SEMICOLON = (0x27),		// ；キー			D_DIK_SEMICOLON
KEY_COLON = (0x92),			// ：キー			D_DIK_COLON
KEY_LBRACKET = (0x1A),			// ［キー			D_DIK_LBRACKET
KEY_RBRACKET = (0x1B),			// ］キー			D_DIK_RBRACKET
KEY_AT = (0x91),				// ＠キー			D_DIK_AT
KEY_BACKSLASH = (0x2B),		// ＼キー			D_DIK_BACKSLASH
KEY_COMMA = (0x33),			// ，キー			D_DIK_COMMA
KEY_KANJI = (0x94),			// 漢字キー			D_DIK_KANJI
KEY_CONVERT = (0x79),			// 変換キー			D_DIK_CONVERT
KEY_NOCONVERT = (0x7B),		// 無変換キー		D_DIK_NOCONVERT
KEY_KANA = (0x70),				// カナキー			D_DIK_KANA
KEY_APPS = (0xDD),				// アプリケーションメニューキー		D_DIK_APPS
KEY_CAPSLOCK = (0x3A),			// CaspLockキー		D_DIK_CAPSLOCK
KEY_SYSRQ = (0xB7),			// PrintScreenキー	D_DIK_SYSRQ
KEY_PAUSE = (0xC5),			// PauseBreakキー	D_DIK_PAUSE
KEY_LWIN = (0xDB),				// 左Winキー		D_DIK_LWIN
KEY_RWIN = (0xDC),				// 右Winキー		D_DIK_RWIN

KEY_NUMLOCK = (0x45),			// テンキーNumLockキー		D_DIK_NUMLOCK
KEY_NUMPAD0 = (0x52),			// テンキー０				D_DIK_NUMPAD0
KEY_NUMPAD1 = (0x4F),			// テンキー１				D_DIK_NUMPAD1
KEY_NUMPAD2 = (0x50),			// テンキー２				D_DIK_NUMPAD2
KEY_NUMPAD3 = (0x51),			// テンキー３				D_DIK_NUMPAD3
KEY_NUMPAD4 = (0x4B),			// テンキー４				D_DIK_NUMPAD4
KEY_NUMPAD5 = (0x4C),			// テンキー５				D_DIK_NUMPAD5
KEY_NUMPAD6 = (0x4D),			// テンキー６				D_DIK_NUMPAD6
KEY_NUMPAD7 = (0x47),			// テンキー７				D_DIK_NUMPAD7
KEY_NUMPAD8 = (0x48),			// テンキー８				D_DIK_NUMPAD8
KEY_NUMPAD9 = (0x49),			// テンキー９				D_DIK_NUMPAD9
KEY_MULTIPLY = (0x37),			// テンキー＊キー			D_DIK_MULTIPLY
KEY_ADD = (0x4E),				// テンキー＋キー			D_DIK_ADD
KEY_SUBTRACT = (0x4A),			// テンキー−キー			D_DIK_SUBTRACT
KEY_DECIMAL = (0x53),			// テンキー．キー			D_DIK_DECIMAL
KEY_DIVIDE = (0xB5),			// テンキー／キー			D_DIK_DIVIDE
KEY_NUMPADENTER = (0x9C),		// テンキーのエンターキー	D_DIK_NUMPADENTER

KEY_F1 = (0x3B),			// Ｆ１キー			D_DIK_F1
KEY_F2 = (0x3C),			// Ｆ２キー			D_DIK_F2
KEY_F3 = (0x3D),			// Ｆ３キー			D_DIK_F3
KEY_F4 = (0x3E),			// Ｆ４キー			D_DIK_F4
KEY_F5 = (0x3F),			// Ｆ５キー			D_DIK_F5
KEY_F6 = (0x40),			// Ｆ６キー			D_DIK_F6
KEY_F7 = (0x41),			// Ｆ７キー			D_DIK_F7
KEY_F8 = (0x42),			// Ｆ８キー			D_DIK_F8
KEY_F9 = (0x43),			// Ｆ９キー			D_DIK_F9
KEY_F10 = (0x44),			// Ｆ１０キー		D_DIK_F10
KEY_F11 = (0x57),			// Ｆ１１キー		D_DIK_F11
KEY_F12 = (0x58),			// Ｆ１２キー		D_DIK_F12

KEY_A = (0x1E),			// Ａキー			D_DIK_A
KEY_B = (0x30),			// Ｂキー			D_DIK_B
KEY_C = (0x2E),			// Ｃキー			D_DIK_C
KEY_D = (0x20),			// Ｄキー			D_DIK_D
KEY_E = (0x12),			// Ｅキー			D_DIK_E
KEY_F = (0x21),			// Ｆキー			D_DIK_F
KEY_G = (0x22),			// Ｇキー			D_DIK_G
KEY_H = (0x23),			// Ｈキー			D_DIK_H
KEY_I = (0x17),			// Ｉキー			D_DIK_I
KEY_J = (0x24),			// Ｊキー			D_DIK_J
KEY_K = (0x25),			// Ｋキー			D_DIK_K
KEY_L = (0x26),			// Ｌキー			D_DIK_L
KEY_M = (0x32),			// Ｍキー			D_DIK_M
KEY_N = (0x31),			// Ｎキー			D_DIK_N
KEY_O = (0x18),			// Ｏキー			D_DIK_O
KEY_P = (0x19),			// Ｐキー			D_DIK_P
KEY_Q = (0x10),			// Ｑキー			D_DIK_Q
KEY_R = (0x13),			// Ｒキー			D_DIK_R
KEY_S = (0x1F),			// Ｓキー			D_DIK_S
KEY_T = (0x14),			// Ｔキー			D_DIK_T
KEY_U = (0x16),			// Ｕキー			D_DIK_U
KEY_V = (0x2F),			// Ｖキー			D_DIK_V
KEY_W = (0x11),			// Ｗキー			D_DIK_W
KEY_X = (0x2D),			// Ｘキー			D_DIK_X
KEY_Y = (0x15),			// Ｙキー			D_DIK_Y
KEY_Z = (0x2C),			// Ｚキー			D_DIK_Z

KEY_0 = (0x0B),			// ０キー			D_DIK_0
KEY_1 = (0x02),			// １キー			D_DIK_1
KEY_2 = (0x03),			// ２キー			D_DIK_2
KEY_3 = (0x04),			// ３キー			D_DIK_3
KEY_4 = (0x05),			// ４キー			D_DIK_4
KEY_5 = (0x06),			// ５キー			D_DIK_5
KEY_6 = (0x07),			// ６キー			D_DIK_6
KEY_7 = (0x08),			// ７キー			D_DIK_7
KEY_8 = (0x09),			// ８キー			D_DIK_8
KEY_9 = (0x0A),			// ９キー			D_DIK_9
};