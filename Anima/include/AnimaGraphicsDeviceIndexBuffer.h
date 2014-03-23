#ifndef __ANIMA_GRAPHICS_DEVICE_INDEX_BUFFER__
#define __ANIMA_GRAPHICS_DEVICE_INDEX_BUFFER__

#include "AnimaTypes.h"
#include "AnimaGraphicsEnums.h"

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