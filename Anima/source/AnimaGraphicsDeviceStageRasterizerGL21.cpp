#include "../include/AnimaGraphicsDeviceStageRasterizerGL21.h"

#include "../include/AnimaGraphicsDeviceContext.h"
#include "../include/AnimaGraphicsDeviceGLHeaders.h"
#include "../include/AnimaGraphicsDeviceFrameBuffer.h"
#include "../include/AnimaGraphicsDeviceSubpipeline.h"

#include <list>

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			StageRasterizerGL21::StageRasterizerGL21(AE::Graphics::Device::Subpipeline *parentSubpipeline, AE::Graphics::Device::FrameBuffer *frameBuffer)
				: StageRasterizer(parentSubpipeline, frameBuffer)
			{
				mPipeline = static_cast<AE::Graphics::Device::PipelineGL21 *>((*mParentSubpipelines.begin())->getParentPipeline());
			}

			StageRasterizerGL21::StageRasterizerGL21(std::list<AE::Graphics::Device::Subpipeline *> &parentSubpipelines, AE::Graphics::Device::FrameBuffer *frameBuffer)
				: StageRasterizer(parentSubpipelines, frameBuffer)
			{
			}

			StageRasterizerGL21::~StageRasterizerGL21()
			{
			}

			void StageRasterizerGL21::run()
			{
				glDisable(GL_DEPTH_TEST);

				glMatrixMode(GL_PROJECTION);
				glPushMatrix();	
				glLoadIdentity();

				AE::Math::Point2<AE::uint> dimensions = mFrameBuffer->getDimensions();
				gluOrtho2D(0, dimensions.x, 0, dimensions.y);

				float m[16];
				glGetFloatv(GL_MODELVIEW_MATRIX, m);

				AE::Graphics::ColorBuffer *colorBuffer;
				while(!mPipeline->mColorBuffers.empty())
				{
					colorBuffer = mPipeline->mColorBuffers.front();

					mFrameBuffer->blitFrom(colorBuffer, AE::Math::Point2<AE::uint>(0, 0), AE::Math::Point2<AE::uint>(colorBuffer->getDimensions().x, colorBuffer->getDimensions().y), AE::Math::Point2<AE::int32>(m[12], m[13]));
					
					mPipeline->mColorBuffers.pop();
				}

				glMatrixMode(GL_PROJECTION);
				glPopMatrix();

				glEnable(GL_DEPTH_TEST);
			}
		}
	}
}