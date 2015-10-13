#ifndef __AE_GRAPHICS_FONT_FACE_FT__
#define __AE_GRAPHICS_FONT_FACE_FT__

#include "AnimaGraphicsFontFace.h"
#include "AnimaGraphicsFontFaceDesc.h"

#include "ft2build.h"
#include FT_FREETYPE_H 

namespace AE
{
	namespace Graphics
	{
		namespace Font
		{
			class FaceFT : public AE::Graphics::Font::Face
			{
			public:
				FaceFT(FT_Face face, const AE::Graphics::Font::FaceDesc &faceDesc);
				~FaceFT();

				AE::int16	getAscender() { return mFaceFT->ascender >> 6; }
				AE::int16	getDescender() { return mFaceFT->descender >> 6; }
				void		print(AE::Graphics::Device::PixelBuffer *destination, const std::wstring &text, const AE::Math::Point2<AE::int32> &position, const AE::Graphics::Color &color);

			private:
				FT_Bitmap					mBitmap;
				AE::Math::Point2<AE::uint>	mDimensions;
				FT_Face						mFaceFT;
				AE::uint32					mOriginLine;
			};
		}
	}
}

#endif