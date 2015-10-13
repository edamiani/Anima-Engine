#include "../include/AnimaGuiLayoutFactory.h"

#include "../include/AnimaGuiLayout.h"

AE::Gui::LayoutFactory* AE::Gui::LayoutFactory::mInstance = 0;

namespace AE
{
	namespace Gui
	{
		LayoutFactory::LayoutFactory()
		{
		}

		AE::Gui::LayoutFactory* LayoutFactory::initialize()
		{
			if(!mInstance)
				mInstance = new AE::Gui::LayoutFactory();

			return mInstance;
		}

		void LayoutFactory::shutdown()
		{
			if(mInstance)
			{
				delete mInstance;
				mInstance = 0;
			}
		}

		AE::Gui::Layout* LayoutFactory::createLayout(const AE::Math::Point2 &position, const AE::Math::Point2 &dimensions)
		{
			AE::Gui::Layout *layout = new AE::Gui::Layout(position, dimensions);

			return layout;
		}

		void LayoutFactory::destroyLayout(AE::Gui::Layout *layout)
		{
			assert(layout);
			delete layout;
		}
	}
}