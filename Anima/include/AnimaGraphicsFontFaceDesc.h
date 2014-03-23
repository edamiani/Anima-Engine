#ifndef __AE_GRAPHICS_FONT_FACE_DESC__
#define __AE_GRAPHICS_FONT_FACE_DESC__

#include "AnimaGraphicsEnums.h"
#include "AnimaMathPoint2.h"
#include "AnimaTypes.h"

#include <string>

namespace AE
{
	namespace Graphics
	{
		namespace Font
		{
			struct FaceDesc
			{
			public:
				FaceDesc() : fontOptions(0) {}

				AE::uint32					fontOptions;
				AE::Graphics::FontType		fontType;
				AE::Math::Point2<AE::uint>	glyphDimensions;
				AE::uint16					horizontalResolution;
				std::string					registeredFontName;
				AE::uint16					verticalResolution;
			};
		}
	}
}

#endif