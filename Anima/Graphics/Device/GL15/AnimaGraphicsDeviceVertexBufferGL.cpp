#include "AnimaGraphicsDeviceVertexBufferGL.h"
#include "Anima/Math/AnimaMathVector3.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			VertexBufferGL::VertexBufferGL()
			{

			}

			VertexBufferGL::VertexBufferGL(GLuint id, AE::uint vertexDeclaration, AE::Graphics::BufferUsage bufferUsage, AE::Graphics::BufferChangeFrequency bufferChangeFrequency)
			{
				mBufferId = id;
				mVertexDeclaration = vertexDeclaration;
				mBufferUsage = bufferUsage;
			}

			VertexBufferGL::VertexBufferGL(VertexBufferDesc &vertexBufferDesc) 
				: mOffset(0)
			{
				mOffsetBlendWeight0 = mOffsetBlendWeight1 = mOffsetBlendWeight2 = mOffsetBlendWeight3 =
					mOffsetNormal = mOffsetDiffuse = mOffsetSpecular = mOffsetTextureCoordinate0 = mOffsetTextureCoordinate1 = 
					mOffsetTextureCoordinate2 =  mOffsetTextureCoordinate3 = 0;

				mOffset += (sizeof(float) * 3);
				mVertexDeclaration |= VE_POSITION;
				
				if(vertexBufferDesc.vertexElements & VE_BLEND_WEIGHT0)
				{
					mOffsetBlendWeight0 = mOffset;
					mOffset += sizeof(float);
					mVertexDeclaration |= VE_BLEND_WEIGHT0;
				}

				if(vertexBufferDesc.vertexElements & VE_BLEND_WEIGHT1)
				{
					mOffsetBlendWeight1 = mOffset;
					mOffset += sizeof(float);
					mVertexDeclaration |= VE_BLEND_WEIGHT1;
				}

				if(vertexBufferDesc.vertexElements & VE_BLEND_WEIGHT2)
				{
					mOffsetBlendWeight2 = mOffset;
					mOffset += sizeof(float);
					mVertexDeclaration |= VE_BLEND_WEIGHT2;
				}

				if(vertexBufferDesc.vertexElements & VE_BLEND_WEIGHT3)
				{
					mOffsetBlendWeight3 = mOffset;
					mOffset += sizeof(float);
					mVertexDeclaration |= VE_BLEND_WEIGHT3;
				}

				if(vertexBufferDesc.vertexElements & VE_NORMAL)
				{
					mOffsetNormal = mOffset;
					mOffset += (sizeof(float) * 3);
					mVertexDeclaration |= VE_NORMAL;
				}

				if(vertexBufferDesc.vertexElements & VE_DIFFUSE)
				{
					mOffsetDiffuse = mOffset;
					mOffset += (3 * (sizeof(GLubyte)));
					mVertexDeclaration |= VE_DIFFUSE;
				}

				if(vertexBufferDesc.vertexElements & VE_SPECULAR)
				{
					mOffsetSpecular = mOffset;
					mOffset += (3 * (sizeof(GLubyte)));
					mVertexDeclaration |= VE_SPECULAR;
				}

				if(vertexBufferDesc.vertexElements & VE_TEX_COORD0)
				{
					mOffsetTextureCoordinate0 = mOffset;
					mOffset += (sizeof(float) * 2);
					mVertexDeclaration |= VE_TEX_COORD0;
				}
				
				if(vertexBufferDesc.vertexElements & VE_TEX_COORD1)
				{
					mOffsetTextureCoordinate1 = mOffset;
					mOffset += (sizeof(float) * 2);
					mVertexDeclaration |= VE_TEX_COORD1;
				}
				
				if(vertexBufferDesc.vertexElements & VE_TEX_COORD2)
				{
					mOffsetTextureCoordinate2 = mOffset;
					mOffset += (sizeof(float) * 2);
					mVertexDeclaration |= VE_TEX_COORD2;
				}
				
				if(vertexBufferDesc.vertexElements & VE_TEX_COORD3)
				{
					mOffsetTextureCoordinate3 = mOffset;
					mOffset += (sizeof(float) * 2);
					mVertexDeclaration |= VE_TEX_COORD3;
				}

				GLuint bufferUsageGL = 0;
				switch(vertexBufferDesc.bufferUsage)
				{
					case BU_USER_WRITE:
						if(vertexBufferDesc.bufferChangeFrequency == AE::Graphics::BCF_STATIC)
							bufferUsageGL = GL_STATIC_DRAW;
						else if(vertexBufferDesc.bufferChangeFrequency == AE::Graphics::BCF_DYNAMIC)
							bufferUsageGL = GL_DYNAMIC_DRAW;
						else if(vertexBufferDesc.bufferChangeFrequency == AE::Graphics::BCF_STREAM)
							bufferUsageGL = GL_STREAM_DRAW;
						break;
					case BU_USER_READ: 
						if(vertexBufferDesc.bufferChangeFrequency == AE::Graphics::BCF_STATIC)
							bufferUsageGL = GL_STATIC_READ;
						else if(vertexBufferDesc.bufferChangeFrequency == AE::Graphics::BCF_DYNAMIC)
							bufferUsageGL = GL_DYNAMIC_READ;
						else if(vertexBufferDesc.bufferChangeFrequency == AE::Graphics::BCF_STREAM)
							bufferUsageGL = GL_STREAM_READ;
						break;
					case BU_CPU_COPY:
						if(vertexBufferDesc.bufferChangeFrequency == AE::Graphics::BCF_STATIC)
							bufferUsageGL = GL_STATIC_COPY;
						else if(vertexBufferDesc.bufferChangeFrequency == AE::Graphics::BCF_DYNAMIC)
							bufferUsageGL = GL_DYNAMIC_COPY;
						else if(vertexBufferDesc.bufferChangeFrequency == AE::Graphics::BCF_STREAM)
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

				glBindBuffer(GL_ARRAY_BUFFER, mBufferId);
				glBufferData(GL_ARRAY_BUFFER, vertexBufferDesc.positions->size() * mOffset, 0, bufferUsageGL);
				
				// Buffer filling process
				AE::uchar *pBytes = (AE::uchar *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
				{
					AE::uint sizeofFloat = sizeof(float);
					AE::uint sizeOfFloatTimesTwo = sizeofFloat * 2;
					AE::uint sizeOfFloatTimesThree = sizeofFloat * 3;
					AE::uint sizeofColor = 3 * sizeof(GLubyte);

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

					mNumberOfVertices = vertexBufferDesc.positions->size();

					glUnmapBuffer(GL_ARRAY_BUFFER);
				}

				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}

			void VertexBufferGL::addDiffuseColor(const AE::Graphics::Color &diffuseColor)
			{
				GLubyte colorChannels[4];
				colorChannels[0] = diffuseColor.R;
				colorChannels[1] = diffuseColor.G;
				colorChannels[2] = diffuseColor.B;
				colorChannels[3] = diffuseColor.A;

				mDiffuseColors.push_back(colorChannels);
			}

			void VertexBufferGL::addNormal(const AE::Math::Vector3 &normal)
			{
				mNormals.push_back(normal);
			}

			void VertexBufferGL::addPosition(const AE::Math::Vector3 &position)
			{
				mPositions.push_back(position);
			}

			void VertexBufferGL::addVertex(const VertexDesc &vertex)
			{
				if(mVertexDeclaration & VE_POSITION)
				{
					mPositions.push_back(vertex.position);
				}

				if(mVertexDeclaration & VE_NORMAL)
				{
					mNormals.push_back(vertex.normal);
				}

				if(mVertexDeclaration & VE_DIFFUSE)
				{
					GLubyte colorChannels[4];
					colorChannels[0] = vertex.diffuseColor.R;
					colorChannels[1] = vertex.diffuseColor.G;
					colorChannels[2] = vertex.diffuseColor.B;
					colorChannels[3] = vertex.diffuseColor.A;

					mDiffuseColors.push_back(colorChannels);
				}
			}

			void VertexBufferGL::lock()
			{
				glBindBuffer(GL_ARRAY_BUFFER, mBufferId);
			}

			void VertexBufferGL::unlock()
			{
				// First, find the vertex data's total size and properly set the offsets
				AE::uint currentOffset = 0;

				AE::uint dataSize = sizeof(AE::Math::Vector3) * mPositions.size();

				if(mVertexDeclaration | AE::Graphics::VE_NORMAL)
				{
					mOffsetNormal = currentOffset;
					currentOffset += sizeof(AE::Math::Vector3) * mPositions.size();

					dataSize += sizeof(AE::Math::Vector3) * mPositions.size();
				}

				if(mVertexDeclaration | AE::Graphics::VE_DIFFUSE)
				{
					mOffsetDiffuse = currentOffset;
					currentOffset += 4 * sizeof(GLubyte) * mDiffuseColors.size();

					dataSize += 4 * sizeof(GLubyte) * mDiffuseColors.size();
				}

				// Now allocate the correct size in the buffer
				glBufferData(GL_ARRAY_BUFFER, dataSize, 0, GL_STREAM_READ);

				// Fill in buffer data
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(AE::Math::Vector3) * mPositions.size(), mPositions.data());

				currentOffset = sizeof(AE::Math::Vector3) * mPositions.size();

				if(mVertexDeclaration | AE::Graphics::VE_NORMAL)
				{
					glBufferSubData(GL_ARRAY_BUFFER, currentOffset, sizeof(AE::Math::Vector3) * mNormals.size(), mNormals.data());
				}

				if(mVertexDeclaration | AE::Graphics::VE_DIFFUSE)
				{
					glBufferSubData(GL_ARRAY_BUFFER, currentOffset, sizeof(AE::Math::Vector3) * mDiffuseColors.size(), mDiffuseColors.data());
				}

				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}

			AE::uchar* VertexBufferGL::getVertexElement(VertexElement elementType)
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
					sizeOfElement = 3 * sizeof(GLubyte);
					break;
				case VE_SPECULAR: 
					mOffsetSpecular ? offset = mOffsetSpecular : -1; 
					sizeOfElement = 3 * sizeof(GLubyte);
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

				AE::uchar *buffer = new AE::uchar[mNumberOfVertices * sizeOfElement];
				glBindBuffer(GL_ARRAY_BUFFER, mBufferId);
				
				AE::uchar *pBytes = (AE::uchar *)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
				if(pBytes)
				{
					pBytes += offset;
					for(AE::uint i = 0; i < mNumberOfVertices; i++)
					{
						memcpy(buffer, pBytes, sizeOfElement);
						pBytes += mOffset;
						buffer += mOffset;
					}

					glUnmapBuffer(GL_ARRAY_BUFFER);

					return buffer;
				}
				else
					return 0;
			}

			void VertexBufferGL::_activateBufferStates()
			{
				// Position
				glVertexPointer(3, GL_FLOAT, mOffset, AE_GL_BUFFER_OFFSET(0));
				glEnableClientState(GL_VERTEX_ARRAY);

				// Blend weights


				// Normal
				if(mOffsetNormal)
				{
					glNormalPointer(GL_FLOAT, mOffset, AE_GL_BUFFER_OFFSET(mOffsetNormal));
					glEnableClientState(GL_NORMAL_ARRAY);
				}

				// Diffuse/specular colors
				if(mOffsetDiffuse)
				{
					glColorPointer(3, GL_UNSIGNED_BYTE, mOffset, AE_GL_BUFFER_OFFSET(mOffsetDiffuse));
					glEnableClientState(GL_COLOR_ARRAY);
				}

				if(mOffsetSpecular)
				{
					glColorPointer(3, GL_UNSIGNED_BYTE, mOffset, AE_GL_BUFFER_OFFSET(mOffsetSpecular));
					glEnableClientState(GL_SECONDARY_COLOR_ARRAY);
				}

				// Texture coordinates
				if(mOffsetTextureCoordinate0)
				{
					glClientActiveTexture(GL_TEXTURE0_ARB);
					glTexCoordPointer(2, GL_FLOAT, mOffset, AE_GL_BUFFER_OFFSET(mOffsetTextureCoordinate0));

					if(mOffsetTextureCoordinate1)
					{
						glClientActiveTexture(GL_TEXTURE1_ARB);
						glTexCoordPointer(2, GL_FLOAT, mOffset, AE_GL_BUFFER_OFFSET(mOffsetTextureCoordinate1));

						if(mOffsetTextureCoordinate2)
						{
							glClientActiveTexture(GL_TEXTURE2_ARB);
							glTexCoordPointer(2, GL_FLOAT, mOffset, AE_GL_BUFFER_OFFSET(mOffsetTextureCoordinate2));

							if(mOffsetTextureCoordinate3)
							{
								glClientActiveTexture(GL_TEXTURE3_ARB);
								glTexCoordPointer(2, GL_FLOAT, mOffset, AE_GL_BUFFER_OFFSET(mOffsetTextureCoordinate3));
							}
						}
					}

					glEnableClientState(GL_TEXTURE_COORD_ARRAY); 
				}
			}

			void VertexBufferGL::_deactivateBufferStates()
			{
				// Position
				glDisableClientState(GL_VERTEX_ARRAY);

				// Blend weights


				// Normal
				if(mOffsetNormal)
					glDisableClientState(GL_NORMAL_ARRAY);

				// Diffuse/specular colors
				if(mOffsetDiffuse)
					glDisableClientState(GL_COLOR_ARRAY);

				if(mOffsetSpecular)
					glDisableClientState(GL_SECONDARY_COLOR_ARRAY);

				// Texture coordinates
				if(mOffsetTextureCoordinate0)
					glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			}
		}
	}
}