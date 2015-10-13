#ifndef __ANIMA_GRAPHICS_VERTEX_BUFFER_DX9__
#define __ANIMA_GRAPHICS_VERTEX_BUFFER_DX9__

#include "AnimaGraphicsVertexBuffer.h"

#include <d3d9.h>
#include <d3dx9.h>

namespace AE
{
	namespace Graphics
	{
		class VertexBufferDX9 : public VertexBuffer
		{
		public:
			VertexBufferDX9(VertexBufferDesc &vertexBufferDesc, IDirect3DDevice9 *d3dDevice);
			virtual ~VertexBufferDX9() { mVertexBuffer->Release(); }

			size_t getOffset() { return mOffset; }
			size_t getSize() { return mNumberOfVertices; }
			size_t getStrideInBytes() { return mOffset; }
			AE::uchar* getVertexElement(VertexElement elementType);

			//Ogre::AxisAlignedBox& _getOgreAABB() { return mAABB; }
			//Ogre::Real _getOgreRadius() { return mRadius; }
			IDirect3DVertexBuffer9* _getVertexBuffer() { return mVertexBuffer; }
			IDirect3DVertexDeclaration9* _getVertexDeclaration() { return mVertexDeclarationD3d; }

		private:
			//Ogre::AxisAlignedBox mAABB;
			//Ogre::Real mRadius;
			size_t mNumberOfVertices;
			size_t mOffset;
			size_t mOffsetBlendWeight0, mOffsetBlendWeight1, mOffsetBlendWeight2, mOffsetBlendWeight3,
				mOffsetNormal, mOffsetDiffuse, mOffsetSpecular, mOffsetTextureCoordinate0, mOffsetTextureCoordinate1,
				mOffsetTextureCoordinate2, mOffsetTextureCoordinate3;

			IDirect3DVertexBuffer9			*mVertexBuffer;
			IDirect3DVertexDeclaration9		*mVertexDeclarationD3d;
			D3DVERTEXBUFFER_DESC			mVertexBufferDesc;
		};
	}
}


#endif