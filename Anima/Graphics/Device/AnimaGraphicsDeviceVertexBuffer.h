#ifndef __AE_GRAPHICS_DEVICE_VERTEX_BUFFER__
#define __AE_GRAPHICS_DEVICE_VERTEX_BUFFER__

#include "Anima/AnimaTypes.h"
#include "Anima/Graphics/AnimaGraphicsColor.h"
#include "Anima/Graphics/AnimaGraphicsEnums.h"
#include "Anima/Math/AnimaMathVector2.h"
#include "Anima/Math/AnimaMathVector3.h"

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
				std::vector<AE::Graphics::Color>	*diffuseColors;
				std::vector<AE::Math::Vector3>		*normals;
				std::vector<AE::Math::Vector3>		*positions;
				std::vector<AE::Graphics::Color>	*specularColors;
				std::vector<AE::Math::Vector2>		*textureCoordinates0;
				std::vector<AE::Math::Vector2>		*textureCoordinates1;
				std::vector<AE::Math::Vector2>		*textureCoordinates2;
				std::vector<AE::Math::Vector2>		*textureCoordinates3;
				bool								useShadowBuffer;
				AE::uint							vertexElements;
			};

			struct VertexDesc
			{
				VertexDesc() :
					blendWeight0(0), blendWeight1(0), blendWeight2(0), blendWeight3(0),
					diffuseColor(AE::Graphics::Color(0, 0, 0, 0)), normal(AE::Math::Vector3::ZERO), 
					position(AE::Math::Vector3::ZERO), specularColor(AE::Graphics::Color(0, 0, 0, 0)),
					textureCoordinate0(AE::Math::Vector2::ZERO), textureCoordinate1(AE::Math::Vector2::ZERO), 
					textureCoordinate2(AE::Math::Vector2::ZERO), textureCoordinate3(AE::Math::Vector2::ZERO)
					{ }

				~VertexDesc() { }

				AE::Real				blendWeight0;
				AE::Real				blendWeight1;
				AE::Real				blendWeight2;
				AE::Real				blendWeight3;
				AE::Graphics::Color		diffuseColor;
				AE::Math::Vector3		normal;
				AE::Math::Vector3		position;
				AE::Graphics::Color		specularColor;
				AE::Math::Vector2		textureCoordinate0;
				AE::Math::Vector2		textureCoordinate1;
				AE::Math::Vector2		textureCoordinate2;
				AE::Math::Vector2		textureCoordinate3;
			};

			class VertexBuffer
			{
			public:
				VertexBuffer() : mVertexDeclaration(0) { }
				virtual ~VertexBuffer() { }

				virtual void		addDiffuseColor(const AE::Graphics::Color &diffuseColor) = 0;
				virtual void		addNormal(const AE::Math::Vector3 &normal) = 0;
				virtual void		addPosition(const AE::Math::Vector3 &position) = 0;
				virtual void		addVertex(const VertexDesc &vertex) = 0;

				virtual size_t		getOffset() = 0;
				virtual size_t		getSize() = 0;
				virtual size_t		getStrideInBytes() = 0;
				AE::uint			getVertexDeclaration() { return mVertexDeclaration; }
				virtual AE::uchar*	getVertexElement(VertexElement elementType) = 0;

			protected:
				AE::uint			mVertexDeclaration;
			};
		}
	}
}

#endif