#include "../include/AnimaOSConfig.h"

#include "../include/AnimaOSEnums.h"

#include "../include/AnimaGraphicsFontFactory.h"
#include "../include/AnimaGraphicsGeometryFactory.h"
#include "../include/AnimaGraphicsImageFactory.h"
#include "../include/AnimaGraphicsSurfaceFactory.h"

#include "../include/AnimaGuiLayoutFactory.h"
#include "../include/AnimaGuiWidgetFactory.h"

#include "../include/AnimaXmlDocumentFactory.h"

namespace AE
{
	namespace OS
	{
		Config::Config(AE::uint options)
			: mOptions(options)
		{
			AE::OS::DeviceManager::initialize();
			//AE::OS::EventManager::initialize();
			//AE::OS::WindowManager::initialize(0);

			//AE::Graphics::SurfaceFactory::initialize();

			if(options & AE::OS::CO_GUI)
			{
				AE::Graphics::FontFactory::initialize();
				AE::Graphics::GeometryFactory::initialize();
				AE::Graphics::ImageFactory::initialize();

				AE::Gui::LayoutFactory::initialize();
				AE::Gui::WidgetFactory::initialize();
			}
			else
			{
				if(options & AE::OS::CO_FONT)
					AE::Graphics::FontFactory::initialize();

				if(options & AE::OS::CO_GEOMETRY)
					AE::Graphics::GeometryFactory::initialize();

				if(options & AE::OS::CO_IMAGE)
					AE::Graphics::ImageFactory::initialize();
			}

			if(options & AE::OS::CO_XML)
				//Ad hoc solution: MUST be changed ASAP!!!
				AE::Xml::DocumentFactory::initialize(AE::Xml::DFT_RAPID_XML);
		}

		Config::~Config()
		{
			if(mOptions & AE::OS::CO_XML)
				AE::Xml::DocumentFactory::shutdown();

			if(mOptions & AE::OS::CO_GUI)
			{
				AE::Graphics::FontFactory::shutdown();
				AE::Graphics::GeometryFactory::shutdown();
				AE::Graphics::ImageFactory::shutdown();

				AE::Gui::LayoutFactory::shutdown();
				AE::Gui::WidgetFactory::shutdown();
			}
			else
			{
				if(mOptions & AE::OS::CO_IMAGE)
					AE::Graphics::ImageFactory::shutdown();

				if(mOptions & AE::OS::CO_GEOMETRY)
					AE::Graphics::GeometryFactory::shutdown();

				if(mOptions & AE::OS::CO_FONT)
					AE::Graphics::FontFactory::shutdown();
			}

			//AE::Graphics::SurfaceFactory::shutdown();

			//AE::OS::WindowManager::shutdown();
			//AE::OS::EventManager::shutdown();
			AE::OS::DeviceManager::shutdown();
		}
	}
}
