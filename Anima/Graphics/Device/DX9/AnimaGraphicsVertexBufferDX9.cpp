#include "../include/AnimaGraphicsVertexBufferDX9.h"
#include "../include/AnimaMathVector3.h"

namespace AE
{
	namespace Graphics
	{
		VertexBufferDX9::VertexBufferDX9(VertexBufferDesc &vertexBufferDesc, IDirect3DDevice9 *d3dDevice) 
			: mOffset(0), mVertexDeclarationD3d(0)
		{
			mOffsetBlendWeight0 = mOffsetBlendWeight1 = mOffsetBlendWeight2 = mOffsetBlendWeight3 =
				mOffsetNormal = mOffsetDiffuse = mOffsetSpecular = mOffsetTextureCoordinate0 = mOffsetTextureCoordinate1 = 
				mOffsetTextureCoordinate2 = mOffsetTextureCoordinate3 = 0;

			mNumberOfVertices = vertexBufferDesc.positions->size();

			D3DVERTEXELEMENT9 *elements = 0;
			D3DVERTEXELEMENT9 *elementPtr = 0;
			AE::uchar numberOfElements = 1;
			
			mOffset += (sizeof(float) * 3);
			mVertexDeclaration |= VE_POSITION;
			{
				D3DVERTEXELEMENT9 tempElement = { 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 };
				elements = (D3DVERTEXELEMENT9 *)malloc(sizeof(D3DVERTEXELEMENT9));
				memcpy(elements, &tempElement, sizeof(D3DVERTEXELEMENT9));
			}

			bool hasBlendWeight = false;
			D3DDECLTYPE declType;
			size_t offsetTemp = 0;
			
			if(vertexBufferDesc.vertexElements & VE_BLEND_WEIGHT0)
			{
				mOffsetBlendWeight0 = mOffset;
				offsetTemp = mOffsetBlendWeight0;
				mOffset += sizeof(float);
				mVertexDeclaration |= VE_BLEND_WEIGHT0;
				declType = D3DDECLTYPE_FLOAT1;
				hasBlendWeight = true;
				numberOfElements++;
			}

			if(vertexBufferDesc.vertexElements & VE_BLEND_WEIGHT1)
			{
				mOffsetBlendWeight1 = mOffset;
				offsetTemp = mOffsetBlendWeight1;
				mOffset += sizeof(float);
				mVertexDeclaration |= VE_BLEND_WEIGHT1;
				declType = D3DDECLTYPE_FLOAT2;
			}

			if(vertexBufferDesc.vertexElements & VE_BLEND_WEIGHT2)
			{
				mOffsetBlendWeight2 = mOffset;
				offsetTemp = mOffsetBlendWeight2;
				mOffset += sizeof(float);
				mVertexDeclaration |= VE_BLEND_WEIGHT2;
				declType = D3DDECLTYPE_FLOAT3;
			}

			if(vertexBufferDesc.vertexElements & VE_BLEND_WEIGHT3)
			{
				mOffsetBlendWeight3 = mOffset;
				offsetTemp = mOffsetBlendWeight3;
				mOffset += sizeof(float);
				mVertexDeclaration |= VE_BLEND_WEIGHT3;
				declType = D3DDECLTYPE_FLOAT4;
			}

			if(hasBlendWeight)
			{
				D3DVERTEXELEMENT9 tempElement = { 0, offsetTemp, declType, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT, 0 };
				elements = (D3DVERTEXELEMENT9 *)realloc((void *)elements, sizeof(D3DVERTEXELEMENT9) * numberOfElements);
				elementPtr = elements + (numberOfElements - 1);
				memcpy(elementPtr, &tempElement, sizeof(D3DVERTEXELEMENT9));
			}

			if(vertexBufferDesc.vertexElements & VE_NORMAL)
			{
				mOffsetNormal = mOffset;
				mOffset += (sizeof(float) * 3);
				mVertexDeclaration |= VE_NORMAL;
				numberOfElements++;

				D3DVERTEXELEMENT9 tempElement = { 0, mOffsetNormal, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 };
				elements = (D3DVERTEXELEMENT9 *)realloc((void *)elements, sizeof(D3DVERTEXELEMENT9) * numberOfElements);
				elementPtr = elements + (numberOfElements - 1);
				memcpy(elementPtr, &tempElement, sizeof(D3DVERTEXELEMENT9));
			}

			if(vertexBufferDesc.vertexElements & VE_DIFFUSE)
			{
				mOffsetDiffuse = mOffset;
				mOffset += (sizeof(DWORD));
				mVertexDeclaration |= VE_DIFFUSE;
				numberOfElements++;

				D3DVERTEXELEMENT9 tempElement = { 0, mOffsetDiffuse, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 };
				elements = (D3DVERTEXELEMENT9 *)realloc((void *)elements, sizeof(D3DVERTEXELEMENT9) * numberOfElements);
				elementPtr = elements + (numberOfElements - 1);
				memcpy(elementPtr, &tempElement, sizeof(D3DVERTEXELEMENT9));
			}

			if(vertexBufferDesc.vertexElements & VE_SPECULAR)
			{
				mOffsetSpecular = mOffset;
				mOffset += (sizeof(DWORD));
				mVertexDeclaration |= VE_SPECULAR;
				numberOfElements++;

				D3DVERTEXELEMENT9 tempElement = { 0, mOffsetSpecular, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 1 };
				elements = (D3DVERTEXELEMENT9 *)realloc((void *)elements, sizeof(D3DVERTEXELEMENT9) * numberOfElements);
				elementPtr = elements + (numberOfElements - 1);
				memcpy(elementPtr, &tempElement, sizeof(D3DVERTEXELEMENT9));
			}

			if(vertexBufferDesc.vertexElements & VE_TEX_COORD0)
			{
				mOffsetTextureCoordinate0 = mOffset;
				mOffset += (sizeof(float) * 2);
				mVertexDeclaration |= VE_TEX_COORD0;
				numberOfElements++;

				D3DVERTEXELEMENT9 tempElement = { 0, mOffsetTextureCoordinate0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 };
				elements = (D3DVERTEXELEMENT9 *)realloc((void *)elements, sizeof(D3DVERTEXELEMENT9) * numberOfElements);
				elementPtr = elements + (numberOfElements - 1);
				memcpy(elementPtr, &tempElement, sizeof(D3DVERTEXELEMENT9));
			}
			
			if(vertexBufferDesc.vertexElements & VE_TEX_COORD1)
			{
				mOffsetTextureCoordinate1 = mOffset;
				mOffset += (sizeof(float) * 2);
				mVertexDeclaration |= VE_TEX_COORD1;
				numberOfElements++;

				D3DVERTEXELEMENT9 tempElement = { 0, mOffsetTextureCoordinate1, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 };
				elements = (D3DVERTEXELEMENT9 *)realloc((void *)elements, sizeof(D3DVERTEXELEMENT9) * numberOfElements);
				elementPtr = elements + (numberOfElements - 1);
				memcpy(elementPtr, &tempElement, sizeof(D3DVERTEXELEMENT9));
			}
			
			if(vertexBufferDesc.vertexElements & VE_TEX_COORD2)
			{
				mOffsetTextureCoordinate2 = mOffset;
				mOffset += (sizeof(float) * 2);
				mVertexDeclaration |= VE_TEX_COORD2;
				numberOfElements++;

				D3DVERTEXELEMENT9 tempElement = { 0, mOffsetTextureCoordinate2, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2 };
				elements = (D3DVERTEXELEMENT9 *)realloc((void *)elements, sizeof(D3DVERTEXELEMENT9) * numberOfElements);
				elementPtr = elements + (numberOfElements - 1);
				memcpy(elementPtr, &tempElement, sizeof(D3DVERTEXELEMENT9));
			}
			
			if(vertexBufferDesc.vertexElements & VE_TEX_COORD3)
			{
				mOffsetTextureCoordinate3 = mOffset;
				mOffset += (sizeof(float) * 2);
				mVertexDeclaration |= VE_TEX_COORD3;
				numberOfElements++;

				D3DVERTEXELEMENT9 tempElement = { 0, mOffsetTextureCoordinate3, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 3 };
				elements = (D3DVERTEXELEMENT9 *)realloc((void *)elements, sizeof(D3DVERTEXELEMENT9) * numberOfElements);
				elementPtr = elements + (numberOfElements - 1);
				memcpy(elementPtr, &tempElement, sizeof(D3DVERTEXELEMENT9));
			}

			//Mark the end of declaration
			{
				D3DVERTEXELEMENT9 tempElement = D3DDECL_END();
				elements = (D3DVERTEXELEMENT9 *)realloc((void *)elements, sizeof(D3DVERTEXELEMENT9) * (numberOfElements + 1));
				elementPtr = elements + numberOfElements;
				memcpy(elementPtr, &tempElement, sizeof(D3DVERTEXELEMENT9));
			}

			// Create vertex declaration
			if(FAILED(d3dDevice->CreateVertexDeclaration(elements, &mVertexDeclarationD3d)))
				assert("error");

			DWORD bufferUsageDx9 = 0;
			D3DPOOL memoryPoolDx9 = D3DPOOL_DEFAULT;
			switch(vertexBufferDesc.bufferUsage)
			{
				case BU_USER_WRITE:
					if(vertexBufferDesc.bufferChangeFrequency == AE::Graphics::BCF_STATIC)
						bufferUsageDx9 = D3DUSAGE_WRITEONLY;
					else if(vertexBufferDesc.bufferChangeFrequency == AE::Graphics::BCF_DYNAMIC)
						bufferUsageDx9 = D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY;
					else if(vertexBufferDesc.bufferChangeFrequency == AE::Graphics::BCF_STREAM)
						bufferUsageDx9 = D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY;
					break;
				case BU_USER_READ: 
					if(vertexBufferDesc.bufferChangeFrequency == AE::Graphics::BCF_STATIC)
						break;
					else if(vertexBufferDesc.bufferChangeFrequency == AE::Graphics::BCF_DYNAMIC)
						bufferUsageDx9 = D3DUSAGE_DYNAMIC;
					else if(vertexBufferDesc.bufferChangeFrequency == AE::Graphics::BCF_STREAM)
						bufferUsageDx9 = D3DUSAGE_DYNAMIC;
					break;
				case BU_CPU_COPY:
					if(vertexBufferDesc.bufferChangeFrequency == AE::Graphics::BCF_STATIC)
						break;
					else if(vertexBufferDesc.bufferChangeFrequency == AE::Graphics::BCF_DYNAMIC)
						bufferUsageDx9 = D3DUSAGE_DYNAMIC;
					else if(vertexBufferDesc.bufferChangeFrequency == AE::Graphics::BCF_STREAM)
						bufferUsageDx9 = D3DUSAGE_DYNAMIC;
					break;
				default: 
					bufferUsageDx9 = D3DUSAGE_WRITEONLY;
					break;
			}

			// Allocate memory
			if(FAILED(d3dDevice->CreateVertexBuffer(vertexBufferDesc.positions->size() * mOffset,
						bufferUsageDx9, 0, memoryPoolDx9, &mVertexBuffer, NULL)))
				assert("DX9: unable to create vertex buffer");
			
			// Buffer filling process
			AE::uchar *pBytes;
			if(!FAILED(mVertexBuffer->Lock(0, vertexBufferDesc.positions->size() * mOffset, (void**)&pBytes, D3DLOCK_DISCARD)))
			{
				AE::uint sizeofFloat = sizeof(float);
				AE::uint sizeOfFloatTimesTwo = sizeofFloat * 2;
				AE::uint sizeOfFloatTimesThree = sizeofFloat * 3;
				AE::uint sizeofColor = sizeof(DWORD);

				for(AE::uint i = 0; i < vertexBufferDesc.positions->size(); i++)
				{
					// Position
					memcpy(pBytes, &(*vertexBufferDesc.positions)[i].x, sizeOfFloatTimesThree);
					pBytes += sizeOfFloatTimesThree;

					// Blend weights
					if(mOffsetBlendWeight0) 
					{
						memcpy(pBytes, &(*vertexBufferDesc.blendWeights0)[i], sizeofFloat);
						pBytes += sizeofFloat;

						if(mOffsetBlendWeight1)
						{
							memcpy(pBytes, &(*vertexBufferDesc.blendWeights1)[i], sizeofFloat);
							pBytes += sizeofFloat;

							if(mOffsetBlendWeight2) 
							{
								memcpy(pBytes, &(*vertexBufferDesc.blendWeights2)[i], sizeofFloat);
								pBytes += sizeofFloat;

								if(mOffsetBlendWeight3) 
								{
									memcpy(pBytes, &(*vertexBufferDesc.blendWeights3)[i], sizeofFloat);
									pBytes += sizeofFloat;
								}
							}
						}
					}

					// Normal
					if(mOffsetNormal)
					{
						memcpy(pBytes, &(*vertexBufferDesc.normals)[i].x, sizeOfFloatTimesThree);
						pBytes += sizeOfFloatTimesThree;
					}

					// Diffuse/specular colors
					if(mOffsetDiffuse)
					{
						memcpy(pBytes, &(*vertexBufferDesc.diffuseColors)[i], sizeofColor);
						pBytes += sizeofColor;
					}

					if(mOffsetSpecular)
					{
						memcpy(pBytes, &(*vertexBufferDesc.specularColors)[i], sizeofColor);
						pBytes += sizeofColor;
					}

					// Texture coordinates
					if(mOffsetTextureCoordinate0)
					{
						memcpy(pBytes, &(*vertexBufferDesc.textureCoordinates0)[i].x, sizeOfFloatTimesTwo);
						pBytes += sizeOfFloatTimesTwo;

						if(mOffsetTextureCoordinate1)
						{
							memcpy(pBytes, &(*vertexBufferDesc.textureCoordinates1)[i].x, sizeOfFloatTimesTwo);
							pBytes += sizeOfFloatTimesTwo;

							if(mOffsetTextureCoordinate2)
							{
								memcpy(pBytes, &(*vertexBufferDesc.textureCoordinates2)[i].x, sizeOfFloatTimesTwo);
								pBytes += sizeOfFloatTimesTwo;

								if(mOffsetTextureCoordinate3)
								{
									memcpy(pBytes, &(*vertexBufferDesc.textureCoordinates3)[i].x, sizeOfFloatTimesTwo);
									pBytes += sizeOfFloatTimesTwo;
								}
							}
						}
					}
				}
				mVertexBuffer->Unlock();
				mVertexBuffer->GetDesc(&mVertexBufferDesc);
			}
			else
				assert(1 && "DX9: unable to fill vertex buffer");
		}

		AE::uchar* VertexBufferDX9::getVertexElement(VertexElement elementType)
		{
			size_t offset = 0;
			size_t sizeOfElement = sizeof(float);
			switch(elementType)
			{
			case VE_POSITION : 
				sizeOfElement *= 3;
				break;
			case VE_BLEND_WEIGHT0: 
				mOffsetBlendWeight0 ? offset = mOffsetBlendWeight0 : -1; 
				break;
			case VE_BLEND_WEIGHT1: 
				mOffsetBlendWeight1 ? offset = mOffsetBlendWeight1 : -1; 
				break;
			case VE_BLEND_WEIGHT2: 
				mOffsetBlendWeight2 ? offset = mOffsetBlendWeight2 : -1; 
				break;
			case VE_BLEND_WEIGHT3: 
				mOffsetBlendWeight3 ? offset = mOffsetBlendWeight3 : -1; 
				break;
			case VE_NORMAL: 
				mOffsetNormal ? offset = mOffsetNormal : -1; 
				sizeOfElement *= 3;
				break;
			case VE_DIFFUSE: 
				mOffsetDiffuse ? offset = mOffsetDiffuse : -1; 
				sizeOfElement = sizeof(DWORD);
				break;
			case VE_SPECULAR: 
				mOffsetSpecular ? offset = mOffsetSpecular : -1; 
				sizeOfElement = sizeof(DWORD);
				break;
			case VE_TEX_COORD0: 
				mOffsetTextureCoordinate0 ? offset = mOffsetTextureCoordinate0 : -1;
				sizeOfElement *= 3;
				break;
			case VE_TEX_COORD1: 
				mOffsetTextureCoordinate1 ? offset = mOffsetTextureCoordinate1 : -1;
				sizeOfElement *= 3;
				break;
			case VE_TEX_COORD2: 
				mOffsetTextureCoordinate2 ? offset = mOffsetTextureCoordinate2 : -1;
				sizeOfElement *= 3;
				break;
			case VE_TEX_COORD3: 
				mOffsetTextureCoordinate3 ? offset = mOffsetTextureCoordinate3 : -1;
				sizeOfElement *= 3;
				break;
			default: 
				offset = -1; 
				break;
			}

			if(offset == -1)
				return 0;

			AE::uchar *buffer = new AE::uchar[mVertexBufferDesc.Size * sizeOfElement];
			AE::uchar *pBytes;
			if(!FAILED(mVertexBuffer->Lock(0, mVertexBufferDesc.Size * mOffset, (void**)&pBytes, D3DLOCK_DISCARD | D3DLOCK_READONLY)))
			{
				pBytes += offset;
				for(AE::uint i = 0; i < mVertexBufferDesc.Size; i++)
				{
					memcpy(buffer, pBytes, sizeOfElement);
					pBytes += mOffset;
					buffer += mOffset;
				}
			}
			mVertexBuffer->Unlock();

			return buffer;
		}
	}
}