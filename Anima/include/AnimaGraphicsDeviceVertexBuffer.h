#ifndef __AE_GRAPHICS_DEVICE_VERTEX_BUFFER__
#define __AE_GRAPHICS_DEVICE_VERTEX_BUFFER__

#include "AnimaTypes.h"
#include "AnimaGraphicsColor.h"
#include "AnimaGraphicsEnums.h"
#include "AnimaMathVector2.h"
#include "AnimaMathVector3.h"

#include <vector>

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			struct VertexBufferDesc
			{
				VertexBufferDesc() :
					blendWeights0(0), blendWeights1(0), blendWeights2(0), blendWeights3(0),
					bufferChangeFrequency(AE::Graphics::BCF_STATIC), bufferUsage(AE::Graphics::BU_USER_WRITE), 
					diffuseColors(0), normals(0), positions(0), specularColors(0),
					textureCoordinates0(0), textureCoordinates1(0), textureCoordinates2(0), textureCoordinates3(0),
					useShadowBuffer(false), vertexElements(VE_POSITION) { }

				~VertexBufferDesc() { }

				std::vector<AE::Real>				*blendWeights0;
				std::vector<AE::Real>				*blendWeights1;
				std::vector<AE::Real>				*blendWeights2;
				std::vector<AE::Real>				*blendWeights3;
				AE::Graphics::BufferChangeFrequency	bufferChangeFrequency;
				AE::Graphics::BufferUsage			bufferUsage;
				std::vector<AE::Graphics::RGBA>		*diffuseColors;
				std::vector<AE::Math::Vector3>		*normals;
				std::vector<AE::Math::Vector3>		*positions;
				std::vector<AE::Graphics::RGBA>		*specularColors;
				std::vector<AE::Math::Vector2>		*textureCoordinates0;
				std::vector<AE::Math::Vector2>		*textureCoordinates1;
				std::vector<AE::Math::Vector2>		*textureCoordinates2;
				std::vector<AE::Math::Vector2>		*textureCoordinates3;
				bool								useShadowBuffer;
				AE::uint							vertexElements;
			};

			class VertexBuffer
			{
			public:
				VertexBuffer() : mVertexDeclaration(0) { }
				virtual ~VertexBuffer() { }

				virtual size_t getOffset() = 0;
				virtual size_t getSize() = 0;
				virtual size_t getStrideInBytes() = 0;
				AE::uint getVertexDeclaration() { return mVertexDeclaration; }
				virtual AE::uchar* getVertexElement(VertexElement elementType) = 0;

			protected:
				AE::uint mVertexDeclaration;
			};
		}
	}
}


#endif