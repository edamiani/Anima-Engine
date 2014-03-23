#ifndef __ANIMA_GRAPHICS_SURFACE__
#define __ANIMA_GRAPHICS_SURFACE__

#include "AnimaTypes.h"
#include "AnimaGraphicsColor.h"
#include "AnimaGraphicsEnums.h"
#include "AnimaGraphicsSurfaceDesc.h"
#include "AnimaMathPoint2.h"

namespace AE
{
	namespace Graphics
	{
		class Surface
		{
		public:
			Surface(const AE::Math::Point2<AE::uint> &dimensions) : 
			  mDimensions(dimensions), mUsesColorKey(false) { }
			virtual ~Surface() { }

			virtual void				blit(void *source, const AE::Math::Point2<AE::uint> &dimensions, const AE::Math::Point2<AE::int32> &position) = 0;
			virtual void				blit(AE::Graphics::Surface *source, const AE::Math::Point2<AE::uint> &dimensions, const AE::Math::Point2<AE::int32> &position) = 0;
			virtual void				clear(const AE::Graphics::Color &backgroundColor) = 0;
			AE::uint8					getColorDepth() { return mPixelFormat.colorDepth; }
			AE::Graphics::Color&		getColorKey() { return mColorKey; }
			virtual void*				getData() = 0;
			virtual AE::Math::Point2<AE::uint>	
										getDimensions() { return mDimensions; }
			AE::Graphics::SurfaceFormat getFormat() { return mSurfaceFormat; }
			virtual void				lock(AE::Graphics::LockType lockType) = 0;
			virtual void				plot(const AE::Graphics::Color &color, const AE::Math::Point2<AE::int32> &position) = 0;
			virtual void				plot32(const AE::uint32 color, const AE::Math::Point2<AE::int32> &position) = 0;
			void						setColorKey(const AE::Graphics::Color &colorKey) { mColorKey = colorKey; mUsesColorKey = true; }
			virtual void				unlock() = 0;

			virtual void				_blit(AE::Graphics::Surface *source, const AE::Math::Point2<AE::uint> &dimensions, const AE::Math::Point2<AE::int32> &position) = 0;
			virtual void				_blitAlpha(void *source, const AE::Math::Point2<AE::uint> &dimensions, const AE::Math::Point2<AE::int32> &position) = 0;
			virtual void				_blitNoAlpha(void *source, const AE::Math::Point2<AE::uint> &dimensions, const AE::Math::Point2<AE::int32> &position) = 0;

			struct PixelFormat
			{
				AE::uint8 colorDepth;
				AE::int8 redShift;
				AE::int8 greenShift;
				AE::int8 blueShift;
				AE::int8 alphaShift;
			};

		protected:
			AE::Graphics::AllocationType	mAllocationType;
			AE::Graphics::Color				mColorKey;
			AE::Math::Point2<AE::uint>		mDimensions;
			AE::Graphics::Device::PixelBufferType
											mPixelBufferType;
			PixelFormat						mPixelFormat;
			AE::Graphics::SurfaceFormat		mSurfaceFormat;
			bool							mUsesColorKey;
		};
	}
}

#endif