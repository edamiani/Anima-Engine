#ifndef __AE_GRAPHICS_CAMERA_2D__
#define __AE_GRAPHICS_CAMERA_2D__

#include "AnimaGraphicsCamera.h"

namespace AE
{
	namespace Graphics
	{
		class Camera2d : public AE::Graphics::Camera
		{
		public:
			Camera2d(bool isRHS = false) : mIsRHS(isRHS)
			{
				mViewMatrix.setIdentity();

				if(mIsRHS)
					// Inverts z-axis to correspond to the right-hand system (RHS), since,
					// by convention, Anima expects vertices to be on left-hand system (LHS)
					mViewMatrix[2][2] = -mViewMatrix[2][2];
			}
			virtual ~Camera2d() {  }

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

			//AE::Math::Vector3 mDirection;
			//AE::Math::Vector3 mPosition;
			//AE::Math::Vector3 mTarget;
			//AE::Math::Vector3 mU, mV, mN;

			//AE::Real mAspectRatio;
			//AE::Real mHorizontalViewDistance, mVerticalViewDistance;
			//AE::Real mFieldOfView;
			//AE::Real mNearClipPlane, mFarClipPlane;
			//AE::Math::Vector2 mBottomLeft, mTopRight;

			//AE::Math::Matrix4 mViewMatrix;
		};
	}
}

#endif