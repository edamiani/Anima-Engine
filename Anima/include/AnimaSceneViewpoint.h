#ifndef __AE_SCENE_VIEWPOINT__
#define __AE_SCENE_VIEWPOINT__

#include "AnimaSceneViewpointNode.h"

namespace AE
{
	namespace Scene
	{
		class Viewpoint : public AE::Scene::ViewpointNode
		{
		public:
			Viewpoint(AE::Real fieldOfView = AE::Math::PI_BY_4, AE::Scene::Node *parentNode = 0) 
				: ViewpointNode(parentNode), mFieldOfView(fieldOfView) {}

			virtual ~Viewpoint() {}

			void setPosition(const AE::Math::Vector3 &position) {}
			void setWindowDimensions(AE::Math::Vector2 const &bottomLeft, AE::Math::Vector2 const &topRight) {}

		protected:
			AE::Real mFieldOfView;
		};
	}
}

#endif