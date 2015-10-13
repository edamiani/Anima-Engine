#ifndef __AE_GRAPHICS_FONT_FACE__
#define __AE_GRAPHICS_FONT_FACE__

#include "AnimaGraphicsColor.h"
#include "AnimaMathPoint2.h"

#include <string>

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class PixelBuffer;
		}

		namespace Font
		{
			class Face
			{
			public:
				Face(AE::uint32 fontOptions) : mFontOptions(fontOptions) {}
				virtual ~Face() {}

				virtual AE::int16	getAscender() = 0;
				virtual AE::int16	getDescender() = 0;
				virtual AE::Graphics::Device::PixelBuffer 
									*getPixelBuffer() { return mPixelBuffer; }
				virtual void		print(AE::Graphics::Device::PixelBuffer *destination, const std::wstring &text, const AE::Math::Point2<AE::int32> &position, const AE::Graphics::Color &color) = 0;

			protected:
				AE::uint32		mFontOptions;
				AE::Graphics::Device::PixelBuffer *mPixelBuffer;
			};
		}
	}
}

#endif