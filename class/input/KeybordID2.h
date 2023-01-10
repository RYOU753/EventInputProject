#pragma once
#include <unordered_map>
enum class KeybordID
{
	KEY_BACK,				// BackSpace�L�[		D_DIK_BACK
	KEY_TAB,				// Tab�L�[			D_DIK_TAB
	KEY_RETURN,				// Enter�L�[			D_DIK_RETURN

	KEY_LSHIFT,				// ��Shift�L�[		D_DIK_LSHIFT
	KEY_RSHIFT ,			// �EShift�L�[		D_DIK_RSHIFT
	KEY_LCONTROL ,			// ��Ctrl�L�[		D_DIK_LCONTROL
	KEY_RCONTROL ,			// �ECtrl�L�[		D_DIK_RCONTROL
	KEY_ESCAPE ,			// Esc�L�[			D_DIK_ESCAPE
	KEY_SPACE ,				// �X�y�[�X�L�[		D_DIK_SPACE
	KEY_PGUP ,				// PageUp�L�[		D_DIK_PGUP
	KEY_PGDN ,				// PageDown�L�[		D_DIK_PGDN
	KEY_END ,				// End�L�[			D_DIK_END
	KEY_HOME ,				// Home�L�[			D_DIK_HOME
	KEY_LEFT,				// ���L�[			D_DIK_LEFT
	KEY_UP,					// ��L�[			D_DIK_UP
	KEY_RIGHT,				// �E�L�[			D_DIK_RIGHT
	KEY_DOWN,				// ���L�[			D_DIK_DOWN
	KEY_INSERT,				// Insert�L�[		D_DIK_INSERT
	KEY_DELETE,				// Delete�L�[		D_DIK_DELETE

	KEY_MINUS,				// �|�L�[							D_DIK_MINUS
	KEY_YEN,				// ���L�[							D_DIK_YEN
	KEY_PREVTRACK,			// �O�L�[							D_DIK_PREVTRACK
	KEY_PERIOD,				// �D�L�[							D_DIK_PERIOD
	KEY_SLASH,				// �^�L�[							D_DIK_SLASH
	KEY_LALT,				// ��Alt�L�[							D_DIK_LALT
	KEY_RALT,				// �EAlt�L�[							D_DIK_RALT
	KEY_SCROLL,				// ScrollLock�L�[					D_DIK_SCROLL
	KEY_SEMICOLON,			// �G�L�[							D_DIK_SEMICOLON
	KEY_COLON,				// �F�L�[							D_DIK_COLON
	KEY_LBRACKET,			// �m�L�[							D_DIK_LBRACKET
	KEY_RBRACKET,			// �n�L�[							D_DIK_RBRACKET
	KEY_AT,					// ���L�[							D_DIK_AT
	KEY_BACKSLASH,			// �_�L�[							D_DIK_BACKSLASH
	KEY_COMMA,				// �C�L�[							D_DIK_COMMA
	KEY_KANJI,				// �����L�[							D_DIK_KANJI
	KEY_CONVERT,			// �ϊ��L�[							D_DIK_CONVERT
	KEY_NOCONVERT,			// ���ϊ��L�[						D_DIK_NOCONVERT
	KEY_KANA,				// �J�i�L�[							D_DIK_KANA
	KEY_APPS,				// �A�v���P�[�V�������j���[�L�[		D_DIK_APPS
	KEY_CAPSLOCK,			// CaspLock�L�[						D_DIK_CAPSLOCK
	KEY_SYSRQ,				// PrintScreen�L�[					D_DIK_SYSRQ
	KEY_PAUSE,				// PauseBreak�L�[					D_DIK_PAUSE
	KEY_LWIN,				// ��Win�L�[							D_DIK_LWIN
	KEY_RWIN,				// �EWin�L�[							D_DIK_RWIN

	KEY_NUMLOCK,			// �e���L�[NumLock�L�[		D_DIK_NUMLOCK
	KEY_NUMPAD0,			// �e���L�[�O				D_DIK_NUMPAD0
	KEY_NUMPAD1,			// �e���L�[�P				D_DIK_NUMPAD1
	KEY_NUMPAD2,			// �e���L�[�Q				D_DIK_NUMPAD2
	KEY_NUMPAD3,			// �e���L�[�R				D_DIK_NUMPAD3
	KEY_NUMPAD4,			// �e���L�[�S				D_DIK_NUMPAD4
	KEY_NUMPAD5,			// �e���L�[�T				D_DIK_NUMPAD5
	KEY_NUMPAD6,			// �e���L�[�U				D_DIK_NUMPAD6
	KEY_NUMPAD7,			// �e���L�[�V				D_DIK_NUMPAD7
	KEY_NUMPAD8,			// �e���L�[�W				D_DIK_NUMPAD8
	KEY_NUMPAD9,			// �e���L�[�X				D_DIK_NUMPAD9
	KEY_MULTIPLY,			// �e���L�[���L�[			D_DIK_MULTIPLY
	KEY_ADD,				// �e���L�[�{�L�[			D_DIK_ADD
	KEY_SUBTRACT,			// �e���L�[�|�L�[			D_DIK_SUBTRACT
	KEY_DECIMAL,			// �e���L�[�D�L�[			D_DIK_DECIMAL
	KEY_DIVIDE,				// �e���L�[�^�L�[			D_DIK_DIVIDE
	KEY_NUMPADENTER,		// �e���L�[�̃G���^�[�L�[	D_DIK_NUMPADENTER

	KEY_F1,			// �e�P�L�[			D_DIK_F1
	KEY_F2,			// �e�Q�L�[			D_DIK_F2
	KEY_F3,			// �e�R�L�[			D_DIK_F3
	KEY_F4,			// �e�S�L�[			D_DIK_F4
	KEY_F5,			// �e�T�L�[			D_DIK_F5
	KEY_F6,			// �e�U�L�[			D_DIK_F6
	KEY_F7,			// �e�V�L�[			D_DIK_F7
	KEY_F8,			// �e�W�L�[			D_DIK_F8
	KEY_F9,			// �e�X�L�[			D_DIK_F9
	KEY_F10,		// �e�P�O�L�[		D_DIK_F10
	KEY_F11,		// �e�P�P�L�[		D_DIK_F11
	KEY_F12,		// �e�P�Q�L�[		D_DIK_F12

	KEY_A,			// �`�L�[			D_DIK_A
	KEY_B,			// �a�L�[			D_DIK_B
	KEY_C,			// �b�L�[			D_DIK_C
	KEY_D,			// �c�L�[			D_DIK_D
	KEY_E,			// �d�L�[			D_DIK_E
	KEY_F,			// �e�L�[			D_DIK_F
	KEY_G,			// �f�L�[			D_DIK_G
	KEY_H,			// �g�L�[			D_DIK_H
	KEY_I,			// �h�L�[			D_DIK_I
	KEY_J,			// �i�L�[			D_DIK_J
	KEY_K,			// �j�L�[			D_DIK_K
	KEY_L,			// �k�L�[			D_DIK_L
	KEY_M,			// �l�L�[			D_DIK_M
	KEY_N,			// �m�L�[			D_DIK_N
	KEY_O,			// �n�L�[			D_DIK_O
	KEY_P,			// �o�L�[			D_DIK_P
	KEY_Q,			// �p�L�[			D_DIK_Q
	KEY_R,			// �q�L�[			D_DIK_R
	KEY_S,			// �r�L�[			D_DIK_S
	KEY_T,			// �s�L�[			D_DIK_T
	KEY_U,			// �t�L�[			D_DIK_U
	KEY_V,			// �u�L�[			D_DIK_V
	KEY_W,			// �v�L�[			D_DIK_W
	KEY_X,			// �w�L�[			D_DIK_X
	KEY_Y,			// �x�L�[			D_DIK_Y
	KEY_Z,			// �y�L�[			D_DIK_Z

	KEY_0,			// �O�L�[			D_DIK_0
	KEY_1,			// �P�L�[			D_DIK_1
	KEY_2,			// �Q�L�[			D_DIK_2
	KEY_3,			// �R�L�[			D_DIK_3
	KEY_4,			// �S�L�[			D_DIK_4
	KEY_5,			// �T�L�[			D_DIK_5
	KEY_6,			// �U�L�[			D_DIK_6
	KEY_7,			// �V�L�[			D_DIK_7
	KEY_8,			// �W�L�[			D_DIK_8
	KEY_9			// �X�L�[			D_DIK_9
};
