#ifndef __AE_SCENE_X3D_VIEWPORT__
#define __AE_SCENE_X3D_VIEWPORT__

#include "AnimaSceneX3D_ViewportNode.h"

namespace AE
{
	namespace Scene
	{
		namespace X3D
		{
			class Viewport : public _ViewportNode
			{
			public:
				Viewport() : mClipBoundary(1, 0, 0, 1) {}
				~Viewport() {}

			protected:
				struct clipBoundary
				{
					clipBoundary(t, l, b, r) : top(t), left(l), bottom(b), right(r) {}

					AE::Real top;
					AE::Real left;
					AE::Real bottom;
					AE::Real right;
				} mClipBoundary;
			};
		}
	}
}

#endif