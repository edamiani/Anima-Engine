#ifndef __AE_GUI_LAYOUT_FACTORY__
#define __AE_GUI_LAYOUT_FACTORY__

#include "AnimaTypes.h"
#include "AnimaMathPoint2.h"

#include <string>

namespace AE
{
	namespace Gui
	{
		class Layout;

		class LayoutFactory
		{
		public:
			virtual ~LayoutFactory() {}

			static AE::Gui::LayoutFactory*	getInstance() { assert(mInstance); return mInstance; }
			static AE::Gui::LayoutFactory*	initialize();
			static void shutdown();

			AE::Gui::Layout* createLayout(const AE::Math::Point2 &position, const AE::Math::Point2 &dimensions);
			void destroyLayout(AE::Gui::Layout *layout);

		protected:
			LayoutFactory();

			static AE::Gui::LayoutFactory *mInstance;
		};
	}
}

#endif