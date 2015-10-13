#include "../include/AnimaGraphicsIndexBufferDX9.h"

namespace AE
{
	namespace Graphics
	{
		IndexBufferDX9::IndexBufferDX9(std::vector<AE::ushort> &indices, BufferUsage bufferUsage, BufferChangeFrequency bufferChangeFrequency, IDirect3DDevice9 *d3dDevice)
		{
			DWORD bufferUsageDx9 = 0;
			D3DPOOL memoryPoolDx9 = D3DPOOL_DEFAULT;
			switch(bufferUsage)
			{
				case BU_USER_WRITE:
					if(bufferChangeFrequency == AE::Graphics::BCF_STATIC)
						bufferUsageDx9 = D3DUSAGE_WRITEONLY;
					else if(bufferChangeFrequency == AE::Graphics::BCF_DYNAMIC)
						bufferUsageDx9 = D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY;
					else if(bufferChangeFrequency == AE::Graphics::BCF_STREAM)
						bufferUsageDx9 = D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY;
					break;
				case BU_USER_READ: 
					if(bufferChangeFrequency == AE::Graphics::BCF_STATIC)
						break;
					else if(bufferChangeFrequency == AE::Graphics::BCF_DYNAMIC)
						bufferUsageDx9 = D3DUSAGE_DYNAMIC;
					else if(bufferChangeFrequency == AE::Graphics::BCF_STREAM)
						bufferUsageDx9 = D3DUSAGE_DYNAMIC;
					break;
				case BU_CPU_COPY:
					if(bufferChangeFrequency == AE::Graphics::BCF_STATIC)
						break;
					else if(bufferChangeFrequency == AE::Graphics::BCF_DYNAMIC)
						bufferUsageDx9 = D3DUSAGE_DYNAMIC;
					else if(bufferChangeFrequency == AE::Graphics::BCF_STREAM)
						bufferUsageDx9 = D3DUSAGE_DYNAMIC;
					break;
				default: 
					bufferUsageDx9 = D3DUSAGE_WRITEONLY;
					break;
			}

			// Allocate memory
			HRESULT result = d3dDevice->CreateIndexBuffer(indices.size(),
						bufferUsageDx9, D3DFMT_INDEX16, memoryPoolDx9, &mIndexBuffer, NULL);
			/*HRESULT result = d3dDevice->CreateIndexBuffer(indices.size(),
						0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &mIndexBuffer, NULL);*/
			if(result < 0)
				assert(0 && "DX9: unable to create index buffer");

			AE::ushort *pIndices;
			if(!FAILED(mIndexBuffer->Lock(0, indices.size(), (void**)&pIndices, D3DLOCK_DISCARD)))
			{
				for(AE::uint i = 0; i < indices.size(); i++)
					*pIndices++ = indices[i];

				mIndexBuffer->Unlock();
				mIndexBuffer->GetDesc(&mIndexBufferDesc);
			}
			else
				assert(0 && "DX9: unable to fill index buffer");
		}
	}
}