#ifndef __AE_OS_WINDOW__
#define __AE_OS_WINDOW__

#include "AnimaGraphicsDeviceContext.h"
#include "AnimaOSWindowDesc.h"
//#include "AnimaInputContext.h"

#include <string>

namespace AE
{
	namespace Graphics
	{
		class Manager;

		namespace Device
		{
			class Context;
		}
	}

	namespace OS
	{
		class Window
		{
		public:
			Window(const std::string &windowTitle, const AE::OS::WindowDesc &windowDesc);
			virtual ~Window() {}

			virtual void					attachDeviceContext(AE::Graphics::Device::Context *deviceContext);
			virtual void					close() = 0;
			AE::Graphics::ColorFormat		getColorFormat() { return mColorFormat; }
			AE::Graphics::Device::Context*	getDeviceContext() { return mDeviceContext; }
			AE::Math::Point2<AE::uint>		getDimensions() { return mDimensions; }
			AE::uint8						getId() { return mId; }
			//AE::Input::Context*			getInputContext() { return mInputContext; }
			AE::Math::Point2<AE::int32>		getPosition() { return mPosition; }
			virtual size_t					getWindowHandle() = 0;
			bool							isFullScreen() { return mIsFullScreen; }
			virtual void                	render() = 0;
			void							setFullScreen(bool isFullScreen) { mIsFullScreen = isFullScreen; }
			virtual void					show() = 0;

		protected:
			AE::Graphics::ColorFormat		mColorFormat;
			AE::Graphics::Device::Context	*mDeviceContext;
			AE::Math::Point2<AE::uint>		mDimensions;
			AE::uint8						mId;
			//AE::Input::Context			*mInputContext;
			bool							mIsFullScreen;
			AE::Math::Point2<AE::int32>		mPosition;
			std::string						mWindowTitle;
		};
	}
}

#endif
