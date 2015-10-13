#ifndef __AE_SCENE_X3D_LAYOUT__
#define __AE_SCENE_X3D_LAYOUT__

#include "AnimaSceneX3D_LayoutNode.h"

#include <string>

namespace AE
{
	namespace Scene
	{
		namespace X3D
		{
			class Layout: public _LayoutNode
			{
			public:
				Layout() {}
				virtual ~Layout() {}

			protected:
				char *mAlign[2];
				float mOffset[2];
				char *mOffsetUnits[2];
				char *mScaleMode[2];
				float mSize[2];
				char *mSizeUnits[2];
			};
		}
	}
}

#endif