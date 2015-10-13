#ifndef __ANIMA_GRAPHICS_INDEX_BUFFER_DX9__
#define __ANIMA_GRAPHICS_INDEX_BUFFER_DX9__

#include "AnimaGraphicsIndexBuffer.h"

#include <vector>
#include <d3d9.h>

namespace AE
{
	namespace Graphics
	{
		class IndexBufferDX9 : public IndexBuffer
		{
		public:
			IndexBufferDX9(std::vector<AE::ushort> &indices, BufferUsage bufferUsage, BufferChangeFrequency bufferChangeFrequency, IDirect3DDevice9 *d3dDevice);
			~IndexBufferDX9() { mIndexBuffer->Release(); }

			size_t getSize() { return mIndexBufferDesc.Size; }

			IDirect3DIndexBuffer9* _getIndexBuffer() { return mIndexBuffer; }

		private:
			IDirect3DIndexBuffer9 *mIndexBuffer;
			D3DINDEXBUFFER_DESC mIndexBufferDesc;
		};
	}
}


#endif