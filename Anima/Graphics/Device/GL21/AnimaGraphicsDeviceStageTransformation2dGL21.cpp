#include "../include/AnimaGraphicsDeviceStageTransformation2dGL21.h"

#include "../include/AnimaGraphicsAxesConvention2d.h"
#include "../include/AnimaGraphicsDeviceGLHeaders.h"
#include "../include/AnimaMathMatrix4.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			StageTransformation2dGL21::StageTransformation2dGL21(AE::Graphics::Device::Subpipeline *parentSubpipeline)
					: AE::Graphics::Device::Stage(AE::Graphics::Device::ST_TRANSFORMATION_2D, parentSubpipeline) 
			{
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
			}

			StageTransformation2dGL21::~StageTransformation2dGL21() 
			{
			}

			void StageTransformation2dGL21::composeModelMatrix(AE::Math::Matrix4 const &modelMatrix)
			{
				mModelMatrix = mModelMatrix * modelMatrix;

				glMatrixMode(GL_MODELVIEW);
				glLoadMatrixf(mModelMatrix.multiply(mViewMatrix)._m);
			}

			void StageTransformation2dGL21::composeViewMatrix(AE::Math::Matrix4 const &viewMatrix)
			{
				// Stores the inverted matrix to avoid unnecessary calculations later
				mViewMatrix = mViewMatrix * (viewMatrix.inverse());

				glMatrixMode(GL_MODELVIEW);
				glLoadMatrixf(mViewMatrix.multiply(mModelMatrix)._m);
			}

			AE::Math::Matrix4 StageTransformation2dGL21::getModelViewMatrix()
			{
				float m[16];
				glGetFloatv(GL_MODELVIEW_MATRIX, m);
				return AE::Math::Matrix4(
					m[0],  m[1],  m[2],  m[3],
					m[4],  m[5],  m[6],  m[7],
					m[8],  m[9],  m[10], m[11],
					m[12], m[13], m[14], m[15]);
			}

			void StageTransformation2dGL21::popModelViewMatrix()
			{
				glMatrixMode(GL_MODELVIEW);
				glPopMatrix();
				glGetFloatv(GL_MODELVIEW_MATRIX, mModelMatrix._m);
			}

			void StageTransformation2dGL21::pushModelViewMatrix()
			{
				glMatrixMode(GL_MODELVIEW);
				glPushMatrix();
			}

			void StageTransformation2dGL21::rotate(AE::Graphics::Image *image, AE::Real angle)
			{
			}

			void StageTransformation2dGL21::run()
			{
				/*if(AE::Graphics::AxesConvention2d::verticalDirection == AE::Graphics::VD_TOP_TO_BOTTOM)

				if(transformedColorBuffer.shouldResetModelMatrix())
					setModelMatrix(transformedColorBuffer.getModelMatrix());
				else
					composeModelMatrix(transformedColorBuffer.getModelMatrix());*/

				mNextStage->run();
			}

			void StageTransformation2dGL21::scale(AE::Graphics::Image *image, const AE::Math::Point2<AE::int32> &scale)
			{
			}

			void StageTransformation2dGL21::setViewport(const AE::Math::Rectangle &viewport)
			{
			}

			void StageTransformation2dGL21::setModelMatrix(AE::Math::Matrix4 const &modelMatrix)
			{
				mModelMatrix = modelMatrix;

				glMatrixMode(GL_MODELVIEW);
				glLoadMatrixf(mModelMatrix.multiply(mViewMatrix)._m);
			}

			void StageTransformation2dGL21::setViewMatrix(AE::Math::Matrix4 const &viewMatrix)
			{
				// Stores the inverted matrix to avoid unnecessary calculations later
				mViewMatrix = viewMatrix.inverse();

				glMatrixMode(GL_MODELVIEW);
				glLoadMatrixf(mViewMatrix.multiply(mModelMatrix)._m);
			}
		}
	}
}