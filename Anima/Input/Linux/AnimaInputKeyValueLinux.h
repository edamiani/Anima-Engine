#ifndef __AE_INPUT_KEY_VALUE_LINUX__
#define __AE_INPUT_KEY_VALUE_LINUX__

#include <X11/keysym.h>

namespace AE
{
	namespace Input
	{
		enum KeyValue
		{
			KV_ESC			= XK_Escape,
			KV_ALT			= XK_Alt_L,
			KV_0			= XK_0,
			KV_1			= XK_1,
			KV_2			= XK_2,
			KV_3			= XK_3,
			KV_4			= XK_4,
			KV_5			= XK_5,
			KV_6			= XK_6,
			KV_7			= XK_7,
			KV_8			= XK_8,
			KV_9			= XK_9,
			KV_A			= XK_a,
			KV_B			= XK_b,
			KV_C			= XK_c,
			KV_D			= XK_d,
			KV_E			= XK_e,
			KV_F			= XK_f,
			KV_G			= XK_g,
			KV_H			= XK_h,
			KV_I			= XK_i,
			KV_J			= XK_j,
			KV_K			= XK_k,
			KV_L			= XK_l,
			KV_M			= XK_m,
			KV_N			= XK_n,
			KV_O			= XK_o,
			KV_P			= XK_p,
			KV_Q			= XK_q,
			KV_R			= XK_r,
			KV_S			= XK_s,
			KV_T			= XK_t,
			KV_U			= XK_u,
			KV_V			= XK_v,
			KV_W			= XK_w,
			KV_X			= XK_x,
			KV_Y			= XK_y,
			KV_Z			= XK_z,
			KV_LSHIFT		= XK_Shift_L,
			KV_RSHIFT		= XK_Shift_R,
			KV_LCONTROL		= XK_Control_L,
			KV_RCONTROL		= XK_Control_R,
			KV_SPACE		= XK_space,
			KV_BACKSPACE	= XK_BackSpace,
			KV_ENTER		= XK_Return,
			KV_FILL			= 0x07 // Arbitrary value; chosen because it's not a valid character
		};
	}
}

#endif
