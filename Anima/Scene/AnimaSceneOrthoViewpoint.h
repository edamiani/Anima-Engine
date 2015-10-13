#ifndef __AE_SCENE_ORTHO_VIEWPOINT__
#define __AE_SCENE_ORTHO_VIEWPOINT__

#include "AnimaSceneViewpointNode.h"

namespace AE
{
	namespace Scene
	{
		class OrthoViewpoint : public AE::Scene::ViewpointNode
		{
		public:
			OrthoViewpoint(bool isRHS = false, AE::Scene::Node *parentNode = 0) 
				: ViewpointNode(parentNode), mIsRHS(isRHS), mMinimumFieldOfView(-1, -1), mMaximumFieldOfView(1, 1) 
			{
				mViewMatrix.setIdentity();

				if(mIsRHS)
					// Inverts z-axis to correspond to the right-hand system (RHS), since,
					// by convention, Anima expects vertices to be on left-hand system (LHS)
					mViewMatrix[2][2] = -mViewMatrix[2][2];
			}

			virtual ~OrthoViewpoint() {}

			void setPosition(const AE::Math::Vector3 &position) 
			{ 
				mPosition.x = position.x;
				mPosition.y = position.z;

				mViewMatrix[3][0] = -mPosition.x;
				mViewMatrix[3][1] = -mPosition.y;
			}

			void setWindowDimensions(AE::Math::Vector2 const &bottomLeft, AE::Math::Vector2 const &topRight)
			{
				mBottomLeft = bottomLeft;
				mTopRight = topRight;
			}

		protected:
			bool mIsRHS;

			AE::Math::Vector2 mMinimumFieldOfView;
			AE::Math::Vector2 mMaximumFieldOfView;
		};
	}
}

#endif