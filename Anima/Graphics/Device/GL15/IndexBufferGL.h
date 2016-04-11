#ifndef __ANIMA_GRAPHICS_DEVICE_INDEX_BUFFER_GL__
#define __ANIMA_GRAPHICS_DEVICE_INDEX_BUFFER_GL__

#include "Anima/Graphics/Device/IndexBuffer.h"

#include <vector>

#include "Anima/Graphics/Device/GL15/GLHeaders.h"

#ifdef WIN32
	#include <windows.h>
	#include <Wingdi.h>
#endif

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class IndexBufferGL : public IndexBuffer
			{
			public:
				IndexBufferGL(std::vector<AE::ushort> &indices, BufferUsage bufferUsage, BufferChangeFrequency bufferChangeFrequency);
				~IndexBufferGL() {  }

				size_t getSize() { return mNumberOfIndices; }

				GLuint _getBufferId() { return mBufferId; }

			private:
				GLuint mBufferId;
				size_t mNumberOfIndices;
			};
		}
	}
}


#endif