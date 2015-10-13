#ifndef __AE_SCENE_VIEWPOINT_NODE__
#define __AE_SCENE_VIEWPOINT_NODE__

#include "AnimaMathMatrix4.h"
#include "AnimaMathTrigonometry.h"
#include "AnimaMathVector2.h"
#include "AnimaMathVector3.h"
#include "AnimaMathVector4.h"

#include "AnimaSceneBindableNode.h"

namespace AE
{
	namespace Scene
	{
		class ViewpointNode : public AE::Scene::BindableNode
		{
		public:
			ViewpointNode(AE::Scene::Node *parentNode = 0) 
				: BindableNode(parentNode) {}

			virtual ~ViewpointNode() {}

			AE::Math::Vector3& getPosition() { return mPosition; }
			const AE::Math::Matrix4& getViewMatrix() { return mViewMatrix; }
			void getWindowDimensions(AE::Math::Vector2 &bottomLeft, AE::Math::Vector2 &topRight) { bottomLeft = mBottomLeft; topRight = mTopRight; }
			AE::Real getWindowHeight() { return (mTopRight.y - mBottomLeft.y); }
			AE::Real getWindowWidth() { return (mTopRight.x - mBottomLeft.x); }
			void initEuler() {}
			void initUVN() {}
			virtual void setPosition(const AE::Math::Vector3 &position) = 0;
			void setViewMatrix(const AE::Math::Matrix4 &viewMatrix) { mViewMatrix = viewMatrix; }
			virtual void setWindowDimensions(AE::Math::Vector2 const &bottomLeft, AE::Math::Vector2 const &topRight) = 0;

		protected:
			AE::Math::Vector3 mDirection;
			AE::Math::Vector3 mPosition;
			AE::Math::Vector3 mTarget;
			AE::Math::Vector3 mU, mV, mN;

			AE::Real mAspectRatio;
			AE::Real mHorizontalViewDistance, mVerticalViewDistance;
			AE::Math::Vector2 mBottomLeft, mTopRight;

			AE::Math::Matrix4 mViewMatrix;
		};
	}
}

#endif