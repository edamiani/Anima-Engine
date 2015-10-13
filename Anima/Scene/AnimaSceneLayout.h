#ifndef __AE_SCENE_LAYOUT__
#define __AE_SCENE_LAYOUT__

#include "AnimaGraphicsSurface.h"

#include <string>

namespace AE
{
	namespace Scene
	{
		enum AlignMode
		{
			AM_BOTTOM,
			AM_CENTER,
			AM_LEFT,
			AM_RIGHT,
			AM_TOP
		};

		enum UnitType
		{
			UT_FRACTION,
			UT_NONE,
			UT_PIXEL,
			UT_STRETCH,
			UT_WORLD
		};

		class Layout
		{
		public:
			Layout() 
			{
				mAlign[0] = mAlign[1] = AE::Scene::AM_CENTER;
				mOffset[0] = mOffset[1] = 0;
				mOffsetUnits[0] = mOffsetUnits[1] = AE::Scene::UT_WORLD;
				mScaleMode[0] = mScaleMode[1] = AE::Scene::UT_NONE;
				mSize[0] = mSize[1] = 1;
				mSizeUnits[0] = mSizeUnits[1] = AE::Scene::UT_WORLD;
			}

			virtual ~Layout() {}

		protected:
			AE::Scene::AlignMode mAlign[2];
			float mOffset[2];
			AE::Scene::UnitType mOffsetUnits[2];
			AE::Scene::UnitType mScaleMode[2];
			float mSize[2];
			AE::Scene::UnitType mSizeUnits[2];

			AE::Graphics::Surface *mSurface;
		};
	}
}

#endif