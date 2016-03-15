#ifndef __ANIMA_GRAPHICS_DEVICE_VERTEX_BUFFER_GL__
#define __ANIMA_GRAPHICS_DEVICE_VERTEX_BUFFER_GL__

#include "Anima/Graphics/Device/VertexBuffer.h"

#include "Anima/Graphics/Device/GL15/GLHeaders.h"

#ifdef WIN32
	#include <windows.h>
	#include <Wingdi.h>
	#include <gl/GL.h>
#endif

#define AE_GL_BUFFER_OFFSET(i) ((char*)NULL + (i))

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class VertexBufferGL : public VertexBuffer
			{
			public:
				VertexBufferGL();
				VertexBufferGL(GLuint id, AE::uint vertexDeclaration, AE::Graphics::BufferUsage bufferUsage, AE::Graphics::BufferChangeFrequency bufferChangeFrequency);
				VertexBufferGL(VertexBufferDesc &vertexBufferDesc);
				~VertexBufferGL() { glDeleteBuffers(1, &mBufferId); }

				void		addDiffuseColor(const AE::Graphics::Color &diffuseColor);
				void		addNormal(const AE::Math::Vector3 &normal);
				void		addPosition(const AE::Math::Vector3 &position);
				void		addVertex(const VertexDesc &vertex);
				void		lock();
				void		unlock();

				size_t		getOffset(AE::Graphics::VertexElement vertexElement) 
				{ 
					switch(vertexElement)
					{
					case VE_DIFFUSE:
						return mOffsetDiffuse;
						break;
					case VE_NORMAL:
						return mOffsetNormal;
						break;
					case VE_POSITION:
					default:
						return mOffset;
						break;
					}
				}

				size_t		getSize() { return mNumberOfVertices; }
				size_t		getStrideInBytes() { return mOffset; }
				AE::uchar*	getVertexElement(VertexElement elementType);

				void		_activateBufferStates();
				void		_deactivateBufferStates();
				GLuint		_getBufferId() { return mBufferId; }
				std::vector<AE::Math::Vector3> & _getPositions() { return mPositions; }

			private:
				GLuint		mBufferId;
				size_t		mNumberOfVertices;
				size_t		mOffset;
				size_t		mOffsetBlendWeight0, mOffsetBlendWeight1, mOffsetBlendWeight2, mOffsetBlendWeight3,
							mOffsetNormal, mOffsetDiffuse, mOffsetSpecular, mOffsetTextureCoordinate0, mOffsetTextureCoordinate1,
							mOffsetTextureCoordinate2, mOffsetTextureCoordinate3;

				std::vector<GLfloat>			mDiffuseColors;
				std::vector<AE::Math::Vector3>	mNormals;
				std::vector<AE::Math::Vector3>	mPositions;
			};
		}
	}
}


#endif