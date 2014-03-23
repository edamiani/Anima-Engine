#ifndef __AE_SCENE_X3D_ORTHO_VIEWPOINT__
#define __AE_SCENE_X3D_ORTHO_VIEWPOINT__

#include "AnimaMathVector2.h"
#include "AnimaSceneX3D_ViewpointNode.h"

namespace AE
{
	namespace Scene
	{
		namespace X3D
		{
			class OrthoViewpoint : public AE::Scene::X3D::_ViewpointNode
			{
			public:
				OrthoViewpoint() : mMinimumFieldOfView(-1, -1), mMaximumFieldOfView(1, 1) {}
				virtual ~OrthoViewpoint() {}

			protected:
				AE::Math::Vector2 mMinimumFieldOfView;
				AE::Math::Vector2 mMaximumFieldOfView;
			};
		}
	}
}

#endif