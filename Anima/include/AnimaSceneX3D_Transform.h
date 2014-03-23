#ifndef __AE_SCENE_X3D_TRANSFORM__
#define __AE_SCENE_X3D_TRANSFORM__

#include "AnimaSceneTransformNode.h"
#include "AnimaSceneX3D_GroupingNode.h"

namespace AE
{
	namespace Scene
	{
		namespace X3D
		{
			class _Transform: public AE::Scene::TransformNode, public AE::Scene::_GroupingNode
			{
			public:
				_Transform() {}
				virtual ~_Transform() {}

			protected:
				/*SFVec3f mCenter;
				SFRotation mRotation;
				SFVec3f mScale;
				SFRotation mScaleOrientation;
				SFVec3f mTranslation;*/
			};
		}
	}
}

#endif