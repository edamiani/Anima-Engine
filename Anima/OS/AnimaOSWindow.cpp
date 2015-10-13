#include "AnimaOSWindow.h"

#include "Graphics/AnimaGraphicsDeviceContext.h"

#include <cassert>

namespace AE
{
	namespace OS
	{
		Window::Window(const std::string &windowTitle, const AE::OS::WindowDesc &windowDesc)
				: mWindowTitle(windowTitle), mIsFullScreen(false)
		{
			mDimensions = windowDesc.dimensions;
			mPosition = windowDesc.position;
			mColorFormat = const_cast<AE::OS::WindowDesc &>(windowDesc).getColorFormat();
		}

		void Window::attachDeviceContext(AE::Graphics::Device::Context *deviceContext)
		{
			mDeviceContext = deviceContext;
			mDeviceContext->setParentWindow(this);
		}
	}
}
