#ifndef __ANIMA_GRAPHICS_DEVICE_INDEX_BUFFER__
#define __ANIMA_GRAPHICS_DEVICE_INDEX_BUFFER__

#include "Anima/AnimaTypes.h"
#include "Anima/Graphics/AnimaGraphicsEnums.h"

#include <cassert>

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class IndexBuffer
			{
			public:
				IndexBuffer() { }
				virtual ~IndexBuffer() { }

				virtual size_t getSize() = 0;
			};
		}
	}
}


#endif