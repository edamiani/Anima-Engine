#ifndef __AE_OS_ENUMS__
#define __AE_OS_ENUMS__

namespace AE
{
	namespace OS
	{
		enum ConfigOptions
		{
			CO_NO_OPTIONS	= 0,
			CO_FONT			= 1,
			CO_GEOMETRY		= 2,
			CO_IMAGE		= 4,
			CO_PRIMITIVES	= 8,
			CO_GUI			= 16,
			CO_XML			= 32
		};

		enum DeviceType
		{
			DT_GRAPHICS_PRIMARY,
			DT_GRAPHICS_SECONDARY,
			DT_INPUT_KEYBOARD,
			DT_INPUT_MOUSE
		};
	}
}

#endif
