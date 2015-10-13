#ifndef __AE_SCENE_X3D_VIEWPOINT__
#define __AE_SCENE_X3D_VIEWPOINT__

#include "AnimaMathTrigonometry.h"
#include "AnimaSceneX3D_ViewpointNode.h"

namespace AE
{
	namespace Scene
	{
		namespace X3D
		{
			class Viewpoint : public AE::Scene::X3D::_ViewpointNode
			{
			public:
				Viewpoint() : mFieldOfView(AE::Math::PI_BY_4) {}
				virtual ~Viewpoint() {}

			protected:
				AE::Real mFieldOfView;
			};
		}
	}
}

#endif