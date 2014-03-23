#ifndef __AE_GUI_LAYOUT__
#define __AE_GUI_LAYOUT__

#include "AnimaMathPoint2.h"

namespace AE
{
	namespace Gui
	{
		class Container;

		class Layout
		{
		public:
			Layout(const AE::Math::Point2 &position, const AE::Math::Point2 &dimensions);
			virtual ~Layout() {}

			AE::Gui::Container* getRoot() { return mRoot; }
			void render();

		protected:
			AE::Gui::Container *mRoot;
		};
	}
}

#endif