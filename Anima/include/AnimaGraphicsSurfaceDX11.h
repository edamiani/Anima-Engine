#ifndef __ANIMA_GRAPHICS_SURFACE_DX11__
#define __ANIMA_GRAPHICS_SURFACE_DX11__

#include "AnimaGraphicsSurface.h"

#include <d3d11.h>
#include <dxgi.h>

namespace AE
{
	namespace Graphics
	{
		class SurfaceDX11;

		class BlitFunctorDX11
		{
		public:
			BlitFunctorDX11(AE::Graphics::SurfaceDX11* object, void (AE::Graphics::SurfaceDX11::*function)(void *, const AE::Math::Point2 &, const AE::Math::Point2 &))
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

			void setFunction(void (AE::Graphics::SurfaceDX11::*function)(void *, const AE::Math::Point2 &, const AE::Math::Point2 &))
			{
				mFunction = function; 
			}

		private:
			void (AE::Graphics::SurfaceDX11::*mFunction)(void *, const AE::Math::Point2 &, const AE::Math::Point2 &);
			AE::Graphics::SurfaceDX11* mObject;
		};

		class BlitFromSurfaceFunctorDX11
		{
		public:
			BlitFromSurfaceFunctorDX11(AE::Graphics::SurfaceDX11* object, void (AE::Graphics::SurfaceDX11::*function)(AE::Graphics::Surface *, const AE::Math::Point2 &, const AE::Math::Point2 &))
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

			void setFunction(void (AE::Graphics::SurfaceDX11::*function)(AE::Graphics::Surface *, const AE::Math::Point2 &, const AE::Math::Point2 &))
			{
				mFunction = function; 
			}

		private:
			void (AE::Graphics::SurfaceDX11::*mFunction)(AE::Graphics::Surface *, const AE::Math::Point2 &, const AE::Math::Point2 &);
			AE::Graphics::SurfaceDX11* mObject;
		};

		class SurfaceDX11 : public AE::Graphics::Surface
		{
		public:
			SurfaceDX11(IDXGISurface *DXGISurface);
			~SurfaceDX11();

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
			IDXGISurface* _getDXGISurface() { return mDXGISurface; }

		protected:
			BlitFunctorDX10				*mBlitFunctor;
			BlitFromSurfaceFunctorDX10	*mBlitFromSurfaceFunctor;
			//D3DLOCKED_RECT				mLockedRect;
			AE::uint32					mPitch;
			//D3DSURFACE_DESC				mSurfaceDesc;
			IDXGISurface				*mDXGISurface;
		};
	}
}

#endif