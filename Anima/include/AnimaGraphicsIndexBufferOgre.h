#ifndef __ANIMA_GRAPHICS_INDEX_BUFFER_OGRE__
#define __ANIMA_GRAPHICS_INDEX_BUFFER_OGRE__

#include "AnimaGraphicsIndexBuffer.h"

#include "Ogre.h"
#include "OgreHardwareIndexBuffer.h"

namespace AE
{
	namespace Graphics
	{
		class IndexBufferOgre : public IndexBuffer
		{
		public:
			IndexBufferOgre(std::vector<AE::ushort> &indices, BufferUsage bufferUsage, bool useShadowBuffer);
			~IndexBufferOgre() { mIndexBuffer.setNull(); }

			size_t getSize() { return mIndexBuffer->getNumIndexes(); }

			Ogre::HardwareIndexBufferSharedPtr _getOgreIndexBuffer() { return mIndexBuffer; }

		private:
			Ogre::HardwareIndexBufferSharedPtr mIndexBuffer;
		};
	}
}


#endif