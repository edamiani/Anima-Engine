#ifndef __AE_GUI_WIDGET_FACTORY__
#define __AE_GUI_WIDGET_FACTORY__

#include "AnimaTypes.h"
#include "AnimaGuiWidgetDesc.h"

#include <map>
#include <string>

namespace AE
{
	namespace Gui
	{
		class Widget;
		class WidgetFactoryComponent;

		class WidgetFactory
		{
		public:
			virtual ~WidgetFactory();

			static AE::Gui::WidgetFactory*	getInstance() { assert(mInstance); return mInstance; }
			static AE::Gui::WidgetFactory*	initialize();
			static void shutdown();

			AE::Gui::Widget* create(const std::string &type, const AE::Gui::WidgetDesc &widgetDesc);
			void destroy(const std::string &type, AE::Gui::Widget *widget);
			AE::int32 getNewId() { return ++mSequentialId; }
			bool registerComponent(const std::string &name, AE::Gui::WidgetFactoryComponent *component);

		protected:
			WidgetFactory();

			static AE::Gui::WidgetFactory *mInstance;

			std::map<std::string, AE::Gui::WidgetFactoryComponent *> mFactories;
			AE::int32 mSequentialId;
		};
	}
}

#endif