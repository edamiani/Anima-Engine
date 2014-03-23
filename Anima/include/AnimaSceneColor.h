#ifndef __AE_SCENE_COLOR__
#define __AE_SCENE_COLOR__

#include "AnimaSceneX3DColorNode.h"
#include "AnimaSceneTypedefs.h"

namespace AE
{
	namespace Scene
	{
		class Color : public X3DColorNode
		{
		public:
			Color(){ }
			~Color() {}

			MFColor& getColorVector() { return mColorVector; }
			void setColorVector(MFColor& &colorVector) { mColorVector = colorVector; }

		protected:
			MFColor mColorVector;
		};
	}
}

#endif