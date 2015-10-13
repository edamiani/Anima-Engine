#ifndef __AE_INPUT_KEY_VALUE_WIN32__
#define __AE_INPUT_KEY_VALUE_WIN32__

#include "allegro5/allegro.h"

namespace AE
{
	namespace Input
	{
		enum KeyValue
		{
			KV_ESC = ALLEGRO_KEY_ESCAPE,
			KV_ALT = ALLEGRO_KEY_ALT,
			KV_0 = ALLEGRO_KEY_0,
			KV_1 = ALLEGRO_KEY_1,
			KV_2 = ALLEGRO_KEY_2,
			KV_3 = ALLEGRO_KEY_3,
			KV_4 = ALLEGRO_KEY_4,
			KV_5 = ALLEGRO_KEY_5,
			KV_6 = ALLEGRO_KEY_6,
			KV_7 = ALLEGRO_KEY_7,
			KV_8 = ALLEGRO_KEY_8,
			KV_9 = ALLEGRO_KEY_9,
			KV_A = ALLEGRO_KEY_A,
			KV_B = ALLEGRO_KEY_B,
			KV_C = ALLEGRO_KEY_C,
			KV_D = ALLEGRO_KEY_D,
			KV_E = ALLEGRO_KEY_E,
			KV_F = ALLEGRO_KEY_F,
			KV_G = ALLEGRO_KEY_G,
			KV_H = ALLEGRO_KEY_H,
			KV_I = ALLEGRO_KEY_I,
			KV_J = ALLEGRO_KEY_J,
			KV_K = ALLEGRO_KEY_K,
			KV_L = ALLEGRO_KEY_L,
			KV_M = ALLEGRO_KEY_M,
			KV_N = ALLEGRO_KEY_N,
			KV_O = ALLEGRO_KEY_O,
			KV_P = ALLEGRO_KEY_P,
			KV_Q = ALLEGRO_KEY_Q,
			KV_R = ALLEGRO_KEY_R,
			KV_S = ALLEGRO_KEY_S,
			KV_T = ALLEGRO_KEY_T,
			KV_U = ALLEGRO_KEY_U,
			KV_V = ALLEGRO_KEY_V,
			KV_W = ALLEGRO_KEY_W,
			KV_X = ALLEGRO_KEY_X,
			KV_Y = ALLEGRO_KEY_Y,
			KV_Z = ALLEGRO_KEY_Z,
			KV_LSHIFT = ALLEGRO_KEY_LSHIFT, //VK_LSHIFT
			KV_RSHIFT = ALLEGRO_KEY_RSHIFT, //VK_RSHIFT
			KV_LCONTROL = ALLEGRO_KEY_LCTRL, //VK_LCONTROL
			KV_RCONTROL = ALLEGRO_KEY_RCTRL //VK_RCONTROL
		};
	}
}

#endif