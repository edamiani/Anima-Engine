#ifndef __AE_GRAPHICS_DEVICE_CONTEXT__
#define __AE_GRAPHICS_DEVICE_CONTEXT__

#include "AnimaTypes.h"
#include "AnimaGraphicsSurface.h"

#include <vector>

namespace AE
{
	namespace OS
	{
		class Window;
	}

	namespace Graphics
	{
		class Viewport;

		namespace Device
		{
			class Driver;
			class FrameBuffer;
			class Pipeline;

			class Context
			{
			public:
				Context(AE::Graphics::Device::Driver *deviceDriver) : mDeviceDriver(deviceDriver) { }
				virtual ~Context() { }

				virtual bool						beginRendering() = 0;
				virtual bool						beginRendering(const AE::Graphics::Color &clearColor) = 0;
				virtual void						endRendering() = 0;
				AE::Graphics::Device::Driver*		getDeviceDriver() { return mDeviceDriver; }
				AE::Graphics::Device::FrameBuffer*	getFrameBuffer() { return mFrameBuffer; }
				AE::OS::Window*						getParentWindow() { return mParentWindow; }
				AE::Graphics::Device::Pipeline*		getPipeline() { return mPipeline; }
				virtual void						render() = 0;
				void								setParentWindow(AE::OS::Window *parentWindow) { mParentWindow = parentWindow; }
				void								setViewport(AE::Graphics::Viewport *viewport) { mViewport = viewport; }


			protected:
				AE::Graphics::Device::Driver		*mDeviceDriver;
				AE::Graphics::Device::FrameBuffer	*mFrameBuffer;
				AE::Graphics::Viewport				*mViewport;
				AE::OS::Window						*mParentWindow;
				AE::Graphics::Device::Pipeline		*mPipeline;
			};
		}
	}
}

#endif
