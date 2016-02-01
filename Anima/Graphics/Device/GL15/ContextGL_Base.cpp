#include "Anima/Graphics/Device/GL15/ContextGL_Base.h"

#include "Anima/Platform.h"
#include "Anima/Graphics/Device/PixelBufferDesc.h"
#include "Anima/OS/Win/WindowWin.h"

#include <cassert>
#include <string>

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			ContextGL_Base::ContextGL_Base(AE::Graphics::Device::Driver *deviceDriver)
				: Context(deviceDriver)
			{

			}

			ContextGL_Base::~ContextGL_Base()
			{

			}

			bool ContextGL_Base::beginRendering()
			{
				glClearColor(0.0, 0.0, 0.0, 1.0);
				glClearDepth(1.0f);

				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glShadeModel(GL_SMOOTH);

				return true;
			}

			bool ContextGL_Base::beginRendering(const AE::Graphics::Color &clearColor)
			{
				glClearColor(clearColor.R / 255.0f, clearColor.G / 255.0f, clearColor.B / 255.0f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glClearDepth(1.0f);

				glShadeModel(GL_SMOOTH);

				AE::Math::Point2<AE::uint> dimensions = mParentWindow->getDimensions();

				gluOrtho2D(0, dimensions.x, 0, dimensions.y);

				return true;
			}

		}
	}
}