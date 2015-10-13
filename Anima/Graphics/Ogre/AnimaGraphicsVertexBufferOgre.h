#ifndef __ANIMA_GRAPHICS_VERTEX_BUFFER_OGRE__
#define __ANIMA_GRAPHICS_VERTEX_BUFFER_OGRE__

#include "AnimaGraphicsVertexBuffer.h"

#include "Ogre.h"
#include "OgreHardwareVertexBuffer.h"

namespace AE
{
	namespace Graphics
	{
		class VertexBufferOgre : public VertexBuffer
		{
		public:
			VertexBufferOgre(VertexBufferDesc &vertexBufferDesc);
			virtual ~VertexBufferOgre() { mVertexBuffer.setNull(); }

			size_t getOffset() { return mOffset; }
			size_t getSize() { return mVertexBuffer->getNumVertices(); }
			AE::uchar* getVertexElement(VertexElement elementType);

			Ogre::AxisAlignedBox& _getOgreAABB() { return mAABB; }
			Ogre::Real _getOgreRadius() { return mRadius; }
			Ogre::HardwareVertexBufferSharedPtr _getOgreVertexBuffer() { return mVertexBuffer; }

		private:
			Ogre::AxisAlignedBox mAABB;
			Ogre::Real mRadius;
			size_t mOffset;
			size_t mOffsetBlendWeight1, mOffsetBlendWeight2, mOffsetBlendWeight3, mOffsetBlendWeight4,
				mOffsetNormal, mOffsetDiffuse, mOffsetSpecular, mOffsetTextureCoordinate1, mOffsetTextureCoordinate2,
				mOffsetTextureCoordinate3, mOffsetTextureCoordinate4;
			Ogre::HardwareVertexBufferSharedPtr mVertexBuffer;
		};
	}
}


#endif