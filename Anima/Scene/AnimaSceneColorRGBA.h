#ifndef __AE_SCENE_COLOR_RGBA__
#define __AE_SCENE_COLOR_RGBA__

#include "AnimaSceneX3DColorNode.h"
#include "AnimaSceneTypedefs.h"

namespace AE
{
	namespace Scene
	{
		class ColorRGBA : public X3DColorNode
		{
		public:
			ColorRGBA(){ }
			~ColorRGBA() {}

			MFColorRGBA& getColorVector() { return mColorVector; }
			void setColorVector(MFColorRGBA& &colorVector) { mColorVector = colorVector; }

		protected:
			MFColorRGBA mColorVector;
		};
	}
}

#endif