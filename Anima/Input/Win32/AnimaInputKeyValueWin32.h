#ifndef __AE_INPUT_KEY_VALUE_WIN32__
#define __AE_INPUT_KEY_VALUE_WIN32__

namespace AE
{
	namespace Input
	{
		enum KeyValue
		{
			KV_ESC = 0x1B, //VK_ESCAPE
			KV_ALT = 0x12, //VK_MENU
			KV_0 = 0x30,
			KV_1 = 0x31,
			KV_2 = 0x32,
			KV_3 = 0x33,
			KV_4 = 0x34,
			KV_5 = 0x35,
			KV_6 = 0x36,
			KV_7 = 0x37,
			KV_8 = 0x38,
			KV_9 = 0x39,
			KV_A = 0x41,
			KV_B = 0x42,
			KV_C = 0x43,
			KV_D = 0x44,
			KV_E = 0x45,
			KV_F = 0x46,
			KV_G = 0x47,
			KV_H = 0x48,
			KV_I = 0x49,
			KV_J = 0x4A,
			KV_K = 0x4B,
			KV_L = 0x4C,
			KV_M = 0x4D,
			KV_N = 0x4E,
			KV_O = 0x4F,
			KV_P = 0x50,
			KV_Q = 0x51,
			KV_R = 0x52,
			KV_S = 0x53,
			KV_T = 0x54,
			KV_U = 0x55,
			KV_V = 0x56,
			KV_W = 0x57,
			KV_X = 0x58,
			KV_Y = 0x59,
			KV_Z = 0x5A,
			KV_FILL = 0x07, // Arbitrary value; chosen because it's not a valid character
			KV_BACKSPACE = 0x08, //VK_BACK
			KV_TAB = 0x09, //VK_TAB
			KV_ENTER = 0x0D, //VK_RETURN
			KV_SHIFT = 0x10, //VK_SHIFT
			KV_CONTROL = 0x11, //VK_CONTROL
			KV_CAPS_LOCK = 0x14, //VK_CAPS
			KV_ESCAPE = 0x1B, //VK_ESCAPE
			KV_SPACE = 0x20, //VK_SPACE
			KV_LSHIFT = 0xA0, //VK_LSHIFT
			KV_RSHIFT = 0xA1, //VK_RSHIFT
			KV_LCONTROL = 0xA2, //VK_LCONTROL
			KV_RCONTROL = 0xA3, //VK_RCONTROL
			KV_EQUAL = 0xBB, //VK_OEM_PLUS
			KV_COMMA = 0xBC, //VK_OEM_COMMA
			KV_MINUS = 0xBD, //VK_OEM_MINUS
			KV_DOT = 0xBE //VK_OEM_PERIOD
		};
	}
}

#endif