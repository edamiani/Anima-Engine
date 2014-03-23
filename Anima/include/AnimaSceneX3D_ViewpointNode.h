#ifndef __AE_SCENE_X3D__VIEWPOINT_NODE__
#define __AE_SCENE_X3D__VIEWPOINT_NODE__

#include "AnimaMathQuaternion.h"
#include "AnimaMathVector3.h"
#include "AnimaSceneX3D_BindableNode.h"

#include <string>

namespace AE
{
	namespace Scene
	{
		namespace X3D
		{
			class _ViewpointNode : public AE::Scene::X3D::_BindableNode
			{
			public:
				_ViewpointNode() : mCenterOfRotation(0, 0, 0), mJump(true), mOrientation(0, 0, 1, 0), mPosition(0, 0, 10), mRetainUserOffsets(false) {}
				virtual ~_ViewpointNode() {}

			protected:
				AE::Math::Vector3 mCenterOfRotation;
				std::string mDescription;
				bool mJump;
				AE::Math::Quaternion mOrientation;
				AE::Math::Vector3 mPosition;
				bool mRetainUserOffsets;
			};
		}
	}
}

#endif