#ifndef __ANIMA_GRAPHICS_SURFACE_DX9__
#define __ANIMA_GRAPHICS_SURFACE_DX9__

#include "AnimaGraphicsSurface.h"

#include <d3d9.h>

namespace AE
{
	namespace Graphics
	{
		class SurfaceDX9;

		class BlitFunctorDX9
		{
		public:
			BlitFunctorDX9(AE::Graphics::SurfaceDX9* object, void (AE::Graphics::SurfaceDX9::*function)(void *, const AE::Math::Point2 &, const AE::Math::Point2 &))
			{ 
				mObject = object;  
				mFunction = function; 
			};

			void operator()(void *source, const AE::Math::Point2 &dimensions, const AE::Math::Point2 &position)
			{ 
				(*mObject.*mFunction)(source, dimensions, position); // execute member function
			}

			void call(void *source, const AE::Math::Point2 &dimensions, const AE::Math::Point2 &position)
			{ 
				(*mObject.*mFunction)(source, dimensions, position); // execute member function
			}

			void setFunction(void (AE::Graphics::SurfaceDX9::*function)(void *, const AE::Math::Point2 &, const AE::Math::Point2 &))
			{
				mFunction = function; 
			}

		private:
			void (AE::Graphics::SurfaceDX9::*mFunction)(void *, const AE::Math::Point2 &, const AE::Math::Point2 &);
			AE::Graphics::SurfaceDX9* mObject;
		};

		class BlitFromSurfaceFunctorDX9
		{
		public:
			BlitFromSurfaceFunctorDX9(AE::Graphics::SurfaceDX9* object, void (AE::Graphics::SurfaceDX9::*function)(AE::Graphics::Surface *, const AE::Math::Point2 &, const AE::Math::Point2 &))
			{ 
				mObject = object;  
				mFunction = function; 
			};

			void operator()(AE::Graphics::Surface *sourceSurface, const AE::Math::Point2 &dimensions, const AE::Math::Point2 &position)
			{ 
				(*mObject.*mFunction)(sourceSurface, dimensions, position); // execute member function
			}

			void call(AE::Graphics::Surface *sourceSurface, const AE::Math::Point2 &dimensions, const AE::Math::Point2 &position)
			{ 
				(*mObject.*mFunction)(sourceSurface, dimensions, position); // execute member function
			}

			void setFunction(void (AE::Graphics::SurfaceDX9::*function)(AE::Graphics::Surface *, const AE::Math::Point2 &, const AE::Math::Point2 &))
			{
				mFunction = function; 
			}

		private:
			void (AE::Graphics::SurfaceDX9::*mFunction)(AE::Graphics::Surface *, const AE::Math::Point2 &, const AE::Math::Point2 &);
			AE::Graphics::SurfaceDX9* mObject;
		};

		class SurfaceDX9 : public AE::Graphics::Surface
		{
		public:
			SurfaceDX9(IDirect3DSurface9 *surfaceDX9);
			~SurfaceDX9();

			void blit(AE::Graphics::Surface *sourceSurface, const AE::Math::Point2 &dimensions, const AE::Math::Point2 &position);
			void blit(void *source, const AE::Math::Point2 &dimensions, const AE::Math::Point2 &position);
			void clear(const AE::Graphics::Color &backgroundColor);
			void* getData();
			AE::Math::Point2 getDimensions();
			void lock(AE::Graphics::LockType lockType);
			void plot(const AE::Graphics::Color &color, const AE::Math::Point2 &position);
			void plot32(const AE::uint32 color, const AE::Math::Point2 &position);
			void unlock();

			void _blit(AE::Graphics::Surface *sourceSurface, const AE::Math::Point2 &dimensions, const AE::Math::Point2 &position);
			void _blitAlpha(void *source, const AE::Math::Point2 &dimensions, const AE::Math::Point2 &position);
			void _blitNoAlpha(void *source, const AE::Math::Point2 &dimensions, const AE::Math::Point2 &position);
			IDirect3DSurface9* _getSurfaceDX9() { return mSurfaceDX9; }

		protected:
			BlitFunctorDX9				*mBlitFunctor;
			BlitFromSurfaceFunctorDX9	*mBlitFromSurfaceFunctor;
			D3DLOCKED_RECT				mLockedRect;
			AE::uint32					mPitch;
			D3DSURFACE_DESC				mSurfaceDesc;
			IDirect3DSurface9			*mSurfaceDX9;
		};
	}
}

#endif