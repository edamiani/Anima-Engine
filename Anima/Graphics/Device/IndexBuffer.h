#ifndef __ANIMA_GRAPHICS_DEVICE_INDEX_BUFFER__
#define __ANIMA_GRAPHICS_DEVICE_INDEX_BUFFER__

#include "Anima/Types.h"
#include "Anima/Graphics/Enums.h"

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

				virtual void	addIndex() = 0;
				virtual size_t	getSize() = 0;
				virtual void	lock() = 0;
				virtual void	unlock() = 0;
			};
		}
	}
}


#endif