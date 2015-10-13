#include "../include/AnimaGraphicsManager.h"

#include "../include/AnimaGraphicsAxesConvention2d.h"
#include "../include/AnimaGraphicsDeviceContext.h"
#include "../include/AnimaGraphicsDeviceDriver.h"
#include "../include/AnimaGraphicsDeviceManagerGL15.h"
#include "../include/AnimaGraphicsDeviceManagerGL21.h"
#include "../include/AnimaGraphicsEnums.h"
#include "../include/AnimaGraphicsFontManagerFT.h"
#include "../include/AnimaGraphicsImageFactory.h"
#include "../include/AnimaPluginManager.h"

AE::Graphics::Manager* AE::Graphics::Manager::mInstance = 0;

namespace AE
{
	namespace Graphics
	{
		Manager::Manager() : 
			AE::PluginGroup(AE::PT_GRAPHICS_MANAGER),
			mDeviceManager(0), mFontManager(0), mImageManager(0)
		{
			mInstance = this;
		}

		Manager::~Manager() 
		{
			mInstance = 0;
		}

		bool Manager::install(AE::uint options)
		{
			if(mParent != 0)
			{
				AE::PluginManager *pluginManager = AE::PluginManager::getInstance();

				if(options & AE::Graphics::GMO_GL15)
				{
					mDeviceManager = static_cast<AE::Graphics::Device::Manager *>(pluginManager->registerPlugin("deviceManagerGL15", new AE::Graphics::Device::ManagerGL15()));
					attachAndInstall(mDeviceManager, AE::NO_OPTIONS);
					mDeviceManager->acquireDeviceDriver(0, AE::Graphics::Device::DT_GL_15);
				}
				else if(options & AE::Graphics::GMO_GL21)
				{
					mDeviceManager = static_cast<AE::Graphics::Device::Manager *>(pluginManager->registerPlugin("deviceManagerGL21", new AE::Graphics::Device::ManagerGL21()));
					attachAndInstall(mDeviceManager, AE::NO_OPTIONS);
					mDeviceManager->acquireDeviceDriver(0, AE::Graphics::Device::DT_GL_21);
				}
#			ifdef AE_PLATFORM_WIN32
				else if(options & AE::Graphics::GMO_D3D9)
				{
					//mDeviceManager = static_cast<AE::Graphics::Device::Manager *>(pluginManager->registerPlugin("deviceManagerGL15", new AE::Graphics::Device::ManagerGL15()));
					//attachAndInstall(mDeviceManager, AE::NO_OPTIONS);
					//mDeviceManager->acquireDeviceDriver(0, AE::Graphics::Device::DT_D3D9);
				}
#			endif
				
				AE::uint imageOptions = AE::NO_OPTIONS;
				if(options & AE::Graphics::GMO_IMAGE_PNG) 
					imageOptions |= AE::Graphics::IT_PNG;
					
				if(imageOptions != AE::NO_OPTIONS)
				{
					mImageManager = static_cast<AE::Graphics::ImageManager *>(pluginManager->registerPlugin("imageManagerAE", new AE::Graphics::ImageManagerAE()));
					attachAndInstall(mImageManager, imageOptions);
				}

				if(options & AE::Graphics::GMO_FONT_FT)
				{
					mFontManager = static_cast<AE::Graphics::Font::Manager *>(pluginManager->registerPlugin("fontManagerFT", new AE::Graphics::Font::ManagerFT()));
					attachAndInstall(mFontManager, AE::NO_OPTIONS);
				}

				mIsInstalled = true;

				return true;
			}
			else
				return false;
		}

		bool Manager::uninstall()
		{
			if(mFontManager)
			{
				detachAndUninstall(mFontManager);
				delete mFontManager;
			}

			if(mImageManager)
			{
				detachAndUninstall(mImageManager);
				delete mImageManager;
			}

			if(mDeviceManager)
			{
				detachAndUninstall(mDeviceManager);
				delete mDeviceManager;
			}

			return true;
		}
	}
}