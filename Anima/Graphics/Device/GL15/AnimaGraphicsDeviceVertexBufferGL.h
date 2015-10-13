#ifndef __ANIMA_GRAPHICS_DEVICE_VERTEX_BUFFER_GL__
#define __ANIMA_GRAPHICS_DEVICE_VERTEX_BUFFER_GL__

#include "AnimaGraphicsDeviceVertexBuffer.h"

#ifdef WIN32
	#include <windows.h>
	#include <Wingdi.h>
	#include <gl/GL.h>
	
	#include "AnimaGraphicsOpenGLExtensions.h"
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
				VertexBufferGL(VertexBufferDesc &vertexBufferDesc);
				virtual ~VertexBufferGL() { glDeleteBuffers(1, &mBufferId); }

				size_t		getOffset() { return mOffset; }
				size_t		getSize() { return mNumberOfVertices; }
				size_t		getStrideInBytes() { return mOffset; }
				AE::uchar*	getVertexElement(VertexElement elementType);

				void		_activateBufferStates();
				void		_deactivateBufferStates();
				GLuint		_getVertexBuffer() { return mBufferId; }

			private:
				GLuint mBufferId;
				size_t mNumberOfVertices;
				size_t mOffset;
				size_t mOffsetBlendWeight0, mOffsetBlendWeight1, mOffsetBlendWeight2, mOffsetBlendWeight3,
					mOffsetNormal, mOffsetDiffuse, mOffsetSpecular, mOffsetTextureCoordinate0, mOffsetTextureCoordinate1,
					mOffsetTextureCoordinate2, mOffsetTextureCoordinate3;
			};
		}
	}
}


#endif