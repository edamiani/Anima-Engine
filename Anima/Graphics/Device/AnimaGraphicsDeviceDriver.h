#ifndef __AE_GRAPHICS_DEVICE_DRIVER__
#define __AE_GRAPHICS_DEVICE_DRIVER__

#include "AnimaGraphicsDeviceContextDesc.h"
#include "AnimaGraphicsDeviceVertexBuffer.h"

#include "Anima/Graphics/AnimaGraphicsEnums.h"
#include "Anima/Math/AnimaMathPoint2.h"

#include <list>
#include <string>
#include <vector>

namespace AE
{
	namespace OS
	{
		class Window;
	}

	namespace Graphics
	{
		namespace Device
		{
			class Context;
			class Pipeline;
			class PixelBuffer;

			class Driver
			{
			public:
				Driver(AE::uint deviceId, AE::Graphics::Device::DriverType driverType) 
					: mBufferIdCount(-1), mDeviceId(deviceId), mType(driverType), mRenderablePixelBufferId(0) {}
				~Driver() {}

				virtual AE::Graphics::Device::Context*		createDeviceContext(AE::Graphics::Device::ContextDesc &contextDesc, const std::string &contextName = "") = 0;
				virtual AE::Graphics::Device::VertexBuffer*	createEmptyVertexBuffer(AE::uint vertexDeclaration, AE::Graphics::BufferUsage bufferUsage, AE::Graphics::BufferChangeFrequency bufferChangeFrequency) = 0;
				virtual void								destroyVertexBuffer(AE::Graphics::Device::VertexBuffer *vertexBuffer) = 0;
				AE::Graphics::Device::Context*				getDeviceContext(AE::uint index) { return mDeviceContexts[index]; }
				AE::uint									getDeviceId() { return mDeviceId; }
				AE::Graphics::Device::DriverType			getType() { return mType; }

			protected:
				AE::int32									mBufferIdCount;
				std::vector<AE::Graphics::Device::Context *> 
															mDeviceContexts;
				AE::uint									mDeviceId;
				AE::uint									mRenderablePixelBufferId;
				AE::Graphics::Device::DriverType			mType;
			};
		}
	}
}

#endif