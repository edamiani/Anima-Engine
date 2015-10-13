#include "../include/AnimaGraphicsIndexBufferOgre.h"

namespace AE
{
	namespace Graphics
	{
		IndexBufferOgre::IndexBufferOgre(std::vector<AE::ushort> &indices, BufferUsage bufferUsage, bool useShadowBuffer)
		{
			Ogre::HardwareBuffer::Usage ogreBufferUsage;
			switch(bufferUsage)
			{
				case BU_DYNAMIC: ogreBufferUsage = Ogre::HardwareBuffer::HBU_DYNAMIC; break;
				case BU_DYNAMIC_WRITE_ONLY: ogreBufferUsage = Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY; break;
				case BU_DYNAMIC_WRITE_ONLY_DISCARDABLE: ogreBufferUsage = Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE; break;
				case BU_STATIC: ogreBufferUsage = Ogre::HardwareBuffer::HBU_STATIC; break;
				case BU_STATIC_WRITE_ONLY: ogreBufferUsage = Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY; break;
				case BU_WRITE_ONLY: ogreBufferUsage = Ogre::HardwareBuffer::HBU_WRITE_ONLY; break;
				default: ogreBufferUsage = Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY; break;
			}

			mIndexBuffer = Ogre::HardwareBufferManager::getSingleton().
				createIndexBuffer(Ogre::HardwareIndexBuffer::IT_16BIT, 
								  indices.size(), 
								  ogreBufferUsage, 
								  useShadowBuffer);

			AE::ushort* pIndices = static_cast<unsigned short*>(mIndexBuffer->lock(Ogre::HardwareBuffer::HBL_DISCARD));
			{
				for(AE::uint i = 0; i < indices.size(); i++)
					*pIndices++ = indices[i];
			}
			mIndexBuffer->unlock();
		}
	}
}