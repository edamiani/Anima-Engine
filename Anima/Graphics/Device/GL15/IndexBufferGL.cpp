#include "Anima/Graphics/Device/GL15/IndexBufferGL.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			IndexBufferGL::IndexBufferGL(std::vector<AE::ushort> &indices, BufferUsage bufferUsage, BufferChangeFrequency bufferChangeFrequency)
			{
				GLuint bufferUsageGL = 0;
				switch(bufferUsage)
				{
					case BU_USER_WRITE:
						if(bufferChangeFrequency == AE::Graphics::BCF_STATIC)
							bufferUsageGL = GL_STATIC_DRAW;
						else if(bufferChangeFrequency == AE::Graphics::BCF_DYNAMIC)
							bufferUsageGL = GL_DYNAMIC_DRAW;
						else if(bufferChangeFrequency == AE::Graphics::BCF_STREAM)
							bufferUsageGL = GL_STREAM_DRAW;
						break;
					case BU_USER_READ: 
						if(bufferChangeFrequency == AE::Graphics::BCF_STATIC)
							bufferUsageGL = GL_STATIC_READ;
						else if(bufferChangeFrequency == AE::Graphics::BCF_DYNAMIC)
							bufferUsageGL = GL_DYNAMIC_READ;
						else if(bufferChangeFrequency == AE::Graphics::BCF_STREAM)
							bufferUsageGL = GL_STREAM_READ;
						break;
					case BU_CPU_COPY:
						if(bufferChangeFrequency == AE::Graphics::BCF_STATIC)
							bufferUsageGL = GL_STATIC_COPY;
						else if(bufferChangeFrequency == AE::Graphics::BCF_DYNAMIC)
							bufferUsageGL = GL_DYNAMIC_COPY;
						else if(bufferChangeFrequency == AE::Graphics::BCF_STREAM)
							bufferUsageGL = GL_STREAM_COPY;
						break;
					default: 
						bufferUsageGL = GL_STATIC_DRAW;
						break;
				}

				// Allocate memory
				GLuint bufferId[1];
				glGenBuffers(1, bufferId);
				mBufferId = bufferId[0];

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBufferId);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(AE::uchar), &indices[0], bufferUsageGL);

				// Buffer filling process
				/*AE::uchar *pIndices = (AE::uchar *)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
				{
					for (AE::uint i = 0; i < indices.size(); i++)
					{
						*pIndices++ = indices[i];
					}

					glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
				}*/

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

				mNumberOfIndices = indices.size();
			}
		}
	}
}