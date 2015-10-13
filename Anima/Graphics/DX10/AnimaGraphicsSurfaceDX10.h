#ifndef __ANIMA_GRAPHICS_SURFACE_DX10__
#define __ANIMA_GRAPHICS_SURFACE_DX10__

#include "AnimaGraphicsSurface.h"

#include <d3d10.h>
#include <dxgi.h>

namespace AE
{
	namespace Graphics
	{
		class SurfaceDX10;

		class BlitFunctorDX10
		{
		public:
			BlitFunctorDX10(AE::Graphics::SurfaceDX10* object, void (AE::Graphics::SurfaceDX10::*function)(void *, const AE::Math::Point2 &, const AE::Math::Point2 &))
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

			void setFunction(void (AE::Graphics::SurfaceDX10::*function)(void *, const AE::Math::Point2 &, const AE::Math::Point2 &))
			{
				mFunction = function; 
			}

		private:
			void (AE::Graphics::SurfaceDX10::*mFunction)(void *, const AE::Math::Point2 &, const AE::Math::Point2 &);
			AE::Graphics::SurfaceDX10* mObject;
		};

		class BlitFromSurfaceFunctorDX10
		{
		public:
			BlitFromSurfaceFunctorDX10(AE::Graphics::SurfaceDX10* object, void (AE::Graphics::SurfaceDX10::*function)(AE::Graphics::Surface *, const AE::Math::Point2 &, const AE::Math::Point2 &))
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

			void setFunction(void (AE::Graphics::SurfaceDX10::*function)(AE::Graphics::Surface *, const AE::Math::Point2 &, const AE::Math::Point2 &))
			{
				mFunction = function; 
			}

		private:
			void (AE::Graphics::SurfaceDX10::*mFunction)(AE::Graphics::Surface *, const AE::Math::Point2 &, const AE::Math::Point2 &);
			AE::Graphics::SurfaceDX10* mObject;
		};

		class SurfaceDX10 : public AE::Graphics::Surface
		{
		public:
			SurfaceDX10(const AE::Math::Point2 &dimensions, IDXGISurface *DXGISurface);
			~SurfaceDX10();

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