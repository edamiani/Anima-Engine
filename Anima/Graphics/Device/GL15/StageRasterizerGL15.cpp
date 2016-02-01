#include "Anima/Graphics/Device/GL15/StageRasterizerGL15.h"

#include "Anima/Graphics/Device/Context.h"
#include "Anima/Graphics/Device/GL15/GLHeaders.h"
#include "Anima/Graphics/Device/FrameBuffer.h"
#include "Anima/Graphics/Device/Subpipeline.h"

#include <list>

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			StageRasterizerGL15::StageRasterizerGL15(AE::Graphics::Device::Subpipeline *parentSubpipeline, AE::Graphics::Device::FrameBuffer *frameBuffer)
				: StageRasterizer(parentSubpipeline, frameBuffer)
			{
				mPipeline = static_cast<AE::Graphics::Device::PipelineGL15 *>((*mParentSubpipelines.begin())->getParentPipeline());
			}

			StageRasterizerGL15::StageRasterizerGL15(std::list<AE::Graphics::Device::Subpipeline *> &parentSubpipelines, AE::Graphics::Device::FrameBuffer *frameBuffer)
				: StageRasterizer(parentSubpipelines, frameBuffer)
			{
			}

			StageRasterizerGL15::~StageRasterizerGL15()
			{
			}

			void StageRasterizerGL15::run()
			{
				glDisable(GL_DEPTH_TEST);

				glMatrixMode(GL_PROJECTION);
				glPushMatrix();	
				glLoadIdentity();

				AE::Math::Point2<AE::uint> dimensions = mFrameBuffer->getDimensions();
				gluOrtho2D(0, dimensions.x, 0, dimensions.y);

				AE::Graphics::ColorBuffer *colorBuffer;
				while(!mPipeline->mColorBuffers.empty())
				{
					colorBuffer = mPipeline->mColorBuffers.front();
					mFrameBuffer->blitFrom(colorBuffer, AE::Math::Point2<AE::uint>(0, 0), AE::Math::Point2<AE::uint>(colorBuffer->getDimensions().x, colorBuffer->getDimensions().y), AE::Math::Point2<AE::int32>(0, 0));
					mPipeline->mColorBuffers.pop();
				}

				glMatrixMode(GL_PROJECTION);
				glPopMatrix();

				glEnable(GL_DEPTH_TEST);
			}
		}
	}
}