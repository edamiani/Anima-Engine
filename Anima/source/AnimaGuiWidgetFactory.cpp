#include "../include/AnimaGuiWidgetFactory.h"

#include "../include/AnimaException.h"

#include "../include/AnimaGuiWidget.h"
#include "../include/AnimaGuiWidgetContentGeometry.h"
#include "../include/AnimaGuiWidgetContentImage.h"
#include "../include/AnimaGuiWidgetContentText.h"
#include "../include/AnimaGuiWidgetFactoryComponent.h"


AE::Gui::WidgetFactory* AE::Gui::WidgetFactory::mInstance = 0;

namespace AE
{
	namespace Gui
	{
		WidgetFactory::WidgetFactory()
			: mSequentialId(-1)
		{
		}

		WidgetFactory::~WidgetFactory()
		{
			mFactories.clear();
		}

		AE::Gui::WidgetFactory* WidgetFactory::initialize()
		{
			if(!mInstance)
				mInstance = new AE::Gui::WidgetFactory();

			return mInstance;
		}

		void WidgetFactory::shutdown()
		{
			if(mInstance)
			{
				delete mInstance;
				mInstance = 0;
			}
		}

		AE::Gui::Widget* WidgetFactory::create(const std::string &factoryComponent, const AE::Gui::WidgetDesc &widgetDesc)
		{
			std::map<std::string, AE::Gui::WidgetFactoryComponent *>::iterator i = mFactories.find(factoryComponent);
			
			if(i == mFactories.end())
				return 0;
			else
				return (*i).second->create(widgetDesc);
		}

		void WidgetFactory::destroy(const std::string &factoryComponent, AE::Gui::Widget *widget)
		{
			std::map<std::string, AE::Gui::WidgetFactoryComponent *>::iterator i = mFactories.find(factoryComponent);
			
			if(i == mFactories.end())
			{
				throw(AE::Exception(AE::ET_NOT_FOUND, "FactoryComponent not found"));
			}
			else
				(*i).second->destroy(widget);
		}

		bool WidgetFactory::registerComponent(const std::string &name, AE::Gui::WidgetFactoryComponent *component)
		{
			std::map<std::string, AE::Gui::WidgetFactoryComponent *>::iterator i = mFactories.find(name);
			if(i == mFactories.end())
			{
				mFactories[name] = component;
				return true;
			}
			else
				return false;
		}
	}
}