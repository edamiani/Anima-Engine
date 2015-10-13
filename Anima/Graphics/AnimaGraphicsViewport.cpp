#include "../include/AnimaGraphicsViewport.h"
#include "../include/AnimaGraphicsCamera.h"

namespace AE
{
	namespace Graphics
	{
		AE::Math::Matrix4 Viewport::getProjectionMatrix()
		{
			AE::Math::Matrix4 viewToViewportScale;
			AE::Math::Matrix4 viewportTranslation;

			viewToViewportScale.setIdentity();
			viewportTranslation.setIdentity();

			viewToViewportScale[0][0] = (mUpperRight.x - mLowerLeft.x) / (mCamera->getWindowWidth() - mCamera->getPosition().x);
			viewToViewportScale[1][1] = (mUpperRight.y - mLowerLeft.y) / (mCamera->getWindowHeight() - mCamera->getPosition().y);

			//viewportTranslation[3][0] = mLowerLeft.x;
			//viewportTranslation[3][1] = mLowerLeft.y;

			AE::Math::Matrix4 viewportMatrix;
			viewportMatrix.setIdentity();
			viewportMatrix = viewToViewportScale * viewportTranslation;

			// Set z = 0, so it becomes an orthographic projection
			// parallel to the z-axis
			// NB: in this way, near and far planes are NOT taken into account
			viewportMatrix.m[2][2] = 0;

			return viewportMatrix;
		}

		void Viewport::setDimensions(const AE::Math::Vector2 &lowerLeft, const AE::Math::Vector2 &upperRight)
		{
			mLowerLeft = lowerLeft;
			mUpperRight = upperRight;
		}

		void Viewport::setBackgroundColor(AE::Graphics::Color backgroundColor)
		{
			mBackgroundColor = backgroundColor;
		}
	}
}