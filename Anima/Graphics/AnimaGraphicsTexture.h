#ifndef __AE_GRAPHICS_TEXTURE__
#define __AE_GRAPHICS_TEXTURE__

#include "../AnimaPrerequisites.h"

namespace AE
{
	namespace Graphics
	{
		class Texture
		{
		public:
			Texture() { }
			virtual ~Texture() { }

			virtual void* lock() = 0;
			virtual void unlock() = 0;
		};
	}
}

#endif