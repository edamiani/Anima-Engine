#ifndef __AE_GRAPHICS_CAMERA__
#define __AE_GRAPHICS_CAMERA__

#include "Anima/Math/Matrix4.h"
#include "Anima/Math/Vector2.h"
#include "Anima/Math/Vector3.h"
#include "Anima/Math/Vector4.h"
#include "Anima/Types.h"

namespace AE
{
	namespace Graphics
	{
		class Camera
		{
		public:
			Camera() {  }
			virtual ~Camera() {  }

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
			AE::Real mFieldOfView;
			AE::Real mNearClipPlane, mFarClipPlane;
			AE::Math::Vector2 mBottomLeft, mTopRight;

			AE::Math::Matrix4 mViewMatrix;
		};
	}
}

#endif