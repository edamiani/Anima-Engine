#include "AnimaGraphicsDeviceDriverGL15.h"
#include "AnimaGraphicsDeviceContextGL15.h"
#include "AnimaGraphicsDeviceVertexBufferGL.h"

#include "Anima/Graphics/AnimaGraphicsAxesConvention2d.h"
#include "Anima/Graphics/Device/AnimaGraphicsDeviceContextDesc.h"
#include "Anima/Graphics/Device/AnimaGraphicsDevicePipeline.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			DriverGL15::DriverGL15(AE::uint deviceId) 
				: Driver(deviceId, AE::Graphics::Device::DT_GL_15) 
			{
				AE::Graphics::AxesConvention2d::horizontalDirection = AE::Graphics::HD_LEFT_TO_RIGHT;
				AE::Graphics::AxesConvention2d::verticalDirection = AE::Graphics::VD_BOTTOM_TO_TOP;
			}

			DriverGL15::~DriverGL15() 
			{
			}

			AE::Graphics::Device::Context* DriverGL15::createDeviceContext(AE::Graphics::Device::ContextDesc &contextDesc, const std::string &contextName)
			{
				AE::Graphics::Device::Context *deviceContext = new AE::Graphics::Device::ContextGL15(contextDesc, this);

				/*if (contextDesc.parentWindow) 
					contextDesc.parentWindow->attachDeviceContext(deviceContext);*/

				mDeviceContexts.push_back(deviceContext);

				return deviceContext;
			}

			AE::Graphics::Device::VertexBuffer* DriverGL15::createEmptyVertexBuffer(AE::uint vertexDeclaration, AE::Graphics::BufferUsage bufferUsage, AE::Graphics::BufferChangeFrequency bufferChangeFrequency)
			{
				AE::uint id;
				glGenBuffers(1, (GLuint *)&id);

				glBindBuffer(GL_ARRAY_BUFFER, id);
				glBufferData(GL_ARRAY_BUFFER, 0, 0, GL_STREAM_READ);

				AE::Graphics::Device::VertexBuffer *vertexBuffer = new AE::Graphics::Device::VertexBufferGL(id, vertexDeclaration, bufferUsage, bufferChangeFrequency);

				glBindBuffer(GL_ARRAY_BUFFER, 0);

				return vertexBuffer;
			}

			void DriverGL15::destroyVertexBuffer(AE::Graphics::Device::VertexBuffer *vertexBuffer)
			{
				delete vertexBuffer;
			}
		}
	}
}