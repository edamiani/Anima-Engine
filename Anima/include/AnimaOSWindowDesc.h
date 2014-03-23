#ifndef __AE_OS_WINDOW_DESC__
#define __AE_OS_WINDOW_DESC__

#include "AnimaGraphicsEnums.h"
#include "AnimaMathPoint2.h"
#include "AnimaTypes.h"

// TODO remove context attributes

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class Context;
		}
	}

	namespace OS
	{
		struct WindowDesc
		{
			WindowDesc() : deviceDriverNumber(0), dimensions(AE::Math::Point2<AE::uint>(0, 0)), fullScreen(false), 
				mColorFormat(AE::Graphics::CF_X8R8G8B8), mColorDepth(32),
				position(AE::Math::Point2<AE::int32>(0, 0)) {  }

			AE::uint					deviceDriverNumber;
			AE::Math::Point2<AE::uint>	dimensions;
			bool						fullScreen;
			AE::Math::Point2<AE::int32>	position;

			WindowDesc & operator=(WindowDesc &rhs)
			{
				dimensions = rhs.dimensions;
				position = rhs.position;

				mColorDepth = rhs.getColorDepth();
				//mSurfaceFormat = rhs.getSurfaceFormat();

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

			AE::uint8					getColorDepth() { return mColorDepth; }
			AE::Graphics::ColorFormat	getColorFormat() { return mColorFormat; }

		private:
			AE::uint8					mColorDepth;
			AE::Graphics::ColorFormat	mColorFormat;
		};
	}
}

#endif
