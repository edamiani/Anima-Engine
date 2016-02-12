#include "Anima/OS/Allegro/WindowAllegro.h"
#include "Anima/Graphics/Device/Allegro/ContextAllegro.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_windows.h>

#include <cassert>

namespace AE
{
	namespace OS
	{
		WindowAllegro::WindowAllegro(const std::string &windowTitle, const AE::OS::WindowDesc &windowDesc)
			: Window(windowTitle, windowDesc)
		{
		}

		WindowAllegro::~WindowAllegro() 
		{
		}

		void WindowAllegro::attachDeviceContext(AE::Graphics::Device::Context *deviceContext)
		{
			mDeviceContext = deviceContext;
		}

		size_t WindowAllegro::getWindowHandle() 
		{
			size_t winHandle = 0;
#ifdef AE_PLATFORM_WIN32
			AE::Graphics::Device::ContextAllegro *deviceContext = static_cast<AE::Graphics::Device::ContextAllegro *>(mDeviceContext);
			winHandle = (size_t)(al_get_win_window_handle(deviceContext->_getAllegroDisplay()));
#endif
			return winHandle;
		}
	}
}