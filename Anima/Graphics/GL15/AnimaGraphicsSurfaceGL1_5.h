#ifndef __ANIMA_GRAPHICS_SURFACE_GL1_5__
#define __ANIMA_GRAPHICS_SURFACE_GL1_5__

#include "AnimaGraphicsSurface.h"

#include "AnimaGraphicsAxesConvention2d.h"
#include "AnimaGraphicsDeviceGLHeaders.h"
#include "AnimaGraphicsEnums.h"
#include "AnimaGraphicsSurfaceDesc.h"
#include "AnimaPlatform.h"

namespace AE
{
	namespace Graphics
	{
		class SurfaceGL1_5 : public AE::Graphics::Surface
		{
		public:
			//SurfaceGL1_5(const AE::Math::Point2 &dimensions, AE::Graphics::SurfaceFormat surfaceFormat);
			SurfaceGL1_5(const AE::Graphics::SurfaceDesc &surfaceDesc);
			~SurfaceGL1_5();

			void blit(AE::Graphics::Surface *sourceSurface, const AE::Math::Point2<AE::uint> &dimensions, const AE::Math::Point2<AE::int32> &position);
			void blit(void *source, const AE::Math::Point2<AE::uint> &dimensions, const AE::Math::Point2<AE::int32> &position);
			void clear(const AE::Graphics::Color &backgroundColor);
			void* getData();
			void lock(AE::Graphics::LockType lockType);
			void plot(const AE::Graphics::Color &color, const AE::Math::Point2<AE::int32> &position);
			void plot32(const AE::uint32 color, const AE::Math::Point2<AE::int32> &position);
			void unlock();

			void _blit(AE::Graphics::Surface *sourceSurface, const AE::Math::Point2<AE::uint> &dimensions, const AE::Math::Point2<AE::int32> &position);
			void _blitAlpha(void *source, const AE::Math::Point2<AE::uint> &dimensions, const AE::Math::Point2<AE::int32> &position);
			void _blitNoAlpha(void *source, const AE::Math::Point2<AE::uint> &dimensions, const AE::Math::Point2<AE::int32> &position);
			//void _setOffScreen(bool isOffScreen) { mIsOffScreen = isOffScreen; }

		protected:
			void	*mData;
			GLuint	mTextureGL; // Pixel buffer ID
			GLenum	mPixelFormatGL;
			GLenum	mTypeGL;
		};
	}
}

#endif
