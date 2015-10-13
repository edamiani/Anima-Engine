#ifndef __AE_GRAPHICS_DEVICE_CONTEXT_DESC__
#define __AE_GRAPHICS_DEVICE_CONTEXT_DESC__

#include "AnimaGraphicsEnums.h"
#include "../Math/AnimaMathPoint2.h"
#include "../AnimaTypes.h"

namespace AE
{
	namespace OS
	{
		class Window;
	}

	namespace Graphics
	{
		namespace Device
		{
			struct ContextDesc
			{
				ContextDesc()
					: dimensions(0, 0), fullScreen(false), parentWindow(0) {  }

				ContextDesc(AE::Graphics::ColorFormat _colorFormat, AE::Math::Point2<AE::uint> _dimensions)
					: dimensions(_dimensions), mColorFormat(_colorFormat)
				{
					switch(mColorFormat)
					{
					case AE::Graphics::CF_A8R8G8B8:
					case AE::Graphics::CF_X8R8G8B8:
						mColorDepth = 32;
						break;
					case AE::Graphics::CF_A1R5G5B5:
					case AE::Graphics::CF_X1R5G5B5:
					case AE::Graphics::CF_R5G6B5:
						mColorDepth = 16;
						break;
					default:
						break;
					}
				}

				AE::Math::Point2<AE::uint> dimensions;
				bool fullScreen;
				AE::OS::Window *parentWindow;

				ContextDesc & operator=(ContextDesc &rhs)
				{
					dimensions = rhs.dimensions;
					parentWindow = rhs.parentWindow;

					mColorDepth = rhs.getColorDepth();
					mColorFormat = rhs.getColorFormat();

					return *this;
				}

				void setColorFormat(AE::Graphics::ColorFormat colorFormat)
				{
					mColorFormat = colorFormat;

					switch(mColorFormat)
					{
					case AE::Graphics::CF_A8R8G8B8:
					case AE::Graphics::CF_R8G8B8A8:
					case AE::Graphics::CF_X8R8G8B8:
						mColorDepth = 32;
						break;
					case AE::Graphics::CF_A1R5G5B5:
					case AE::Graphics::CF_X1R5G5B5:
					case AE::Graphics::CF_R5G6B5:
						mColorDepth = 16;
						break;
					default:
						break;
					}
				}

				AE::uint8 getColorDepth() { return mColorDepth; }
				AE::Graphics::ColorFormat getColorFormat() { return mColorFormat; }

			private:
				AE::uint8 mColorDepth;
				AE::Graphics::ColorFormat mColorFormat;
			};
		}
	}
}

#endif
