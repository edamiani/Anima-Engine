#ifndef __AE_GRAPHICS_COLOR_STRUCTURE__
#define __AE_GRAPHICS_COLOR_STRUCTURE__

#include "../AnimaTypes.h"

namespace AE
{
	namespace Graphics
	{
		struct ColorStructure
		{
			AE::int8	alphaShift;
			AE::uint8	bitDepth;
			AE::int8	blueShift;
			AE::int8	greenShift;
			AE::int8	redShift;
		};
	}
}

#endif