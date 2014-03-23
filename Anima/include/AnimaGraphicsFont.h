#ifndef __AE_GRAPHICS_FONT__
#define __AE_GRAPHICS_FONT__

#include "AnimaPrerequisites.h"

namespace AE
{
	namespace Graphics
	{
		enum FontType
		{
			FT_TRUETYPE,
			FT_IMAGE
		};

		class Font
		{
		public:
			Font() { }
			virtual ~Font() { }

		protected:
			AE::uint				mDpi;
			std::string				mFontFace;
			AE::Graphics::FontType	mFontType;
			AE::uint				mSizeInPoints;
		};
	}
}

#endif