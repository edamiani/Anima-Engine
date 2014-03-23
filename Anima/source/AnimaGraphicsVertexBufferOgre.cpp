#include "../include/AnimaGraphicsVertexBufferOgre.h"

namespace AE
{
	namespace Graphics
	{
		VertexBufferOgre::VertexBufferOgre(VertexBufferDesc &vertexBufferDesc) : mRadius(0), mOffset(0)
		{
			mOffsetBlendWeight1 = mOffsetBlendWeight2 = mOffsetBlendWeight3 = mOffsetBlendWeight4 =
				mOffsetNormal = mOffsetDiffuse = mOffsetSpecular = mOffsetTextureCoordinate1 = mOffsetTextureCoordinate2 = 
				mOffsetTextureCoordinate3 =  mOffsetTextureCoordinate4 = 0;

			mOffset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);
			mVertexDeclaration |= VE_POSITION;
			
			if(vertexBufferDesc.vertexElements & VE_BLEND_WEIGHT1)
			{
				mOffsetBlendWeight1 = mOffset;
				mOffset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT1);
				mVertexDeclaration |= VE_BLEND_WEIGHT1;
			}

			if(vertexBufferDesc.vertexElements & VE_BLEND_WEIGHT2)
			{
				mOffsetBlendWeight2 = mOffset;
				mOffset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT1);
				mVertexDeclaration |= VE_BLEND_WEIGHT2;
			}

			if(vertexBufferDesc.vertexElements & VE_BLEND_WEIGHT3)
			{
				mOffsetBlendWeight3 = mOffset;
				mOffset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT1);
				mVertexDeclaration |= VE_BLEND_WEIGHT3;
			}

			if(vertexBufferDesc.vertexElements & VE_BLEND_WEIGHT4)
			{
				mOffsetBlendWeight4 = mOffset;
				mOffset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT1);
				mVertexDeclaration |= VE_BLEND_WEIGHT4;
			}

			if(vertexBufferDesc.vertexElements & VE_NORMAL)
			{
				mOffsetNormal = mOffset;
				mOffset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);
				mVertexDeclaration |= VE_NORMAL;
			}

			if(vertexBufferDesc.vertexElements & VE_DIFFUSE)
			{
				mOffsetDiffuse = mOffset;
				mOffset += Ogre::VertexElement::getTypeSize(Ogre::VET_COLOUR);
				mVertexDeclaration |= VE_DIFFUSE;
			}

			if(vertexBufferDesc.vertexElements & VE_SPECULAR)
			{
				mOffsetSpecular = mOffset;
				mOffset += Ogre::VertexElement::getTypeSize(Ogre::VET_COLOUR);
				mVertexDeclaration |= VE_SPECULAR;
			}

			if(vertexBufferDesc.vertexElements & VE_TEX_COORD1)
			{
				mOffsetTextureCoordinate1 = mOffset;
				mOffset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT2);
				mVertexDeclaration |= VE_TEX_COORD1;
			}
			
			if(vertexBufferDesc.vertexElements & VE_TEX_COORD2)
			{
				mOffsetTextureCoordinate2 = mOffset;
				mOffset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT2);
				mVertexDeclaration |= VE_TEX_COORD2;
			}
			
			if(vertexBufferDesc.vertexElements & VE_TEX_COORD3)
			{
				mOffsetTextureCoordinate3 = mOffset;
				mOffset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT2);
				mVertexDeclaration |= VE_TEX_COORD3;
			}
			
			if(vertexBufferDesc.vertexElements & VE_TEX_COORD4)
			{
				mOffsetTextureCoordinate4 = mOffset;
				mOffset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT2);
				mVertexDeclaration |= VE_TEX_COORD4;
			}

			Ogre::HardwareBuffer::Usage ogreBufferUsage;
			switch(vertexBufferDesc.bufferUsage)
			{
				case BU_DYNAMIC: ogreBufferUsage = Ogre::HardwareBuffer::HBU_DYNAMIC; break;
				case BU_DYNAMIC_WRITE_ONLY: ogreBufferUsage = Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY; break;
				case BU_DYNAMIC_WRITE_ONLY_DISCARDABLE: ogreBufferUsage = Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE; break;
				case BU_STATIC: ogreBufferUsage = Ogre::HardwareBuffer::HBU_STATIC; break;
				case BU_STATIC_WRITE_ONLY: ogreBufferUsage = Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY; break;
				case BU_WRITE_ONLY: ogreBufferUsage = Ogre::HardwareBuffer::HBU_WRITE_ONLY; break;
				default: ogreBufferUsage = Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY; break;
			}

			// Allocate memory
			mVertexBuffer = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
								mOffset, 
								vertexBufferDesc.positions->size(), 
								ogreBufferUsage, 
								vertexBufferDesc.useShadowBuffer);

			
			// Buffer filling process
			Ogre::Vector3 tempVertexPosition;
			Ogre::uchar *pBytes = static_cast<Ogre::uchar *>(mVertexBuffer->lock(Ogre::HardwareBuffer::HBL_DISCARD));
			{
				AE::uint sizeofFloat = Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT1);
				AE::uint sizeOfFloatTimesTwo = sizeofFloat * 2;
				AE::uint sizeOfFloatTimesThree = sizeofFloat * 3;
				AE::uint sizeofColor = Ogre::VertexElement::getTypeSize(Ogre::VET_COLOUR);

				for(AE::uint i = 0; i < vertexBufferDesc.positions->size(); i++)
				{
					// Position
					memcpy(pBytes, &(*vertexBufferDesc.positions)[i].x, sizeOfFloatTimesThree);
					pBytes += sizeOfFloatTimesThree;

					tempVertexPosition.x = (*vertexBufferDesc.positions)[i].x;
					tempVertexPosition.y = (*vertexBufferDesc.positions)[i].y;
					tempVertexPosition.z = (*vertexBufferDesc.positions)[i].z;
					mAABB.merge(tempVertexPosition);
					mRadius = std::max(mRadius, tempVertexPosition.length());

					// Blend weights
					if(mOffsetBlendWeight1) 
					{
						memcpy(pBytes, &(*vertexBufferDesc.blendWeights1)[i], sizeofFloat);
						pBytes += sizeofFloat;
					}

					if(mOffsetBlendWeight2)
					{
						memcpy(pBytes, &(*vertexBufferDesc.blendWeights2)[i], sizeofFloat);
						pBytes += sizeofFloat;
					}

					if(mOffsetBlendWeight3) 
					{
						memcpy(pBytes, &(*vertexBufferDesc.blendWeights3)[i], sizeofFloat);
						pBytes += sizeofFloat;
					}

					if(mOffsetBlendWeight4) 
					{
						memcpy(pBytes, &(*vertexBufferDesc.blendWeights4)[i], sizeofFloat);
						pBytes += sizeofFloat;
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
					if(mOffsetTextureCoordinate1)
					{
						memcpy(pBytes, &(*vertexBufferDesc.textureCoordinates1)[i].x, sizeOfFloatTimesTwo);
						pBytes += sizeOfFloatTimesTwo;
					}

					if(mOffsetTextureCoordinate2)
					{
						memcpy(pBytes, &(*vertexBufferDesc.textureCoordinates2)[i].x, sizeOfFloatTimesTwo);
						pBytes += sizeOfFloatTimesTwo;
					}

					if(mOffsetTextureCoordinate3)
					{
						memcpy(pBytes, &(*vertexBufferDesc.textureCoordinates3)[i].x, sizeOfFloatTimesTwo);
						pBytes += sizeOfFloatTimesTwo;
					}

					if(mOffsetTextureCoordinate4)
					{
						memcpy(pBytes, &(*vertexBufferDesc.textureCoordinates4)[i].x, sizeOfFloatTimesTwo);
						pBytes += sizeOfFloatTimesTwo;
					}
				}
			}
			mVertexBuffer->unlock();
		}

		AE::uchar* VertexBufferOgre::getVertexElement(VertexElement elementType)
		{
			size_t offset = 0;
			size_t sizeOfElement = sizeof(AE::Real);
			switch(elementType)
			{
			case VE_POSITION : 
				sizeOfElement *= 3;
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
			case VE_BLEND_WEIGHT4: 
				mOffsetBlendWeight4 ? offset = mOffsetBlendWeight4 : -1; 
				break;
			case VE_NORMAL: 
				mOffsetNormal ? offset = mOffsetNormal : -1; 
				sizeOfElement *= 3;
				break;
			case VE_DIFFUSE: 
				mOffsetDiffuse ? offset = mOffsetDiffuse : -1; 
				sizeOfElement = sizeof(AE::Graphics::RGBA);
				break;
			case VE_SPECULAR: 
				mOffsetSpecular ? offset = mOffsetSpecular : -1; 
				sizeOfElement = sizeof(AE::Graphics::RGBA);
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
			case VE_TEX_COORD4: 
				mOffsetTextureCoordinate4 ? offset = mOffsetTextureCoordinate4 : -1;
				sizeOfElement *= 3;
				break;
			default: 
				offset = -1; 
				break;
			}

			if(offset == -1)
				return 0;

			AE::uchar *buffer = new AE::uchar[mVertexBuffer->getNumVertices() * sizeOfElement];
			AE::uchar *pBytes = static_cast<AE::uchar*>(mVertexBuffer->lock(Ogre::HardwareBuffer::HBL_DISCARD));
			{
				pBytes += offset;
				for(AE::uint i = 0; i < mVertexBuffer->getNumVertices(); i++)
				{
					memcpy(buffer, pBytes, sizeOfElement);
					pBytes += mOffset;
					buffer += mOffset;
				}
			}
			mVertexBuffer->unlock();

			return buffer;
		}
	}
}