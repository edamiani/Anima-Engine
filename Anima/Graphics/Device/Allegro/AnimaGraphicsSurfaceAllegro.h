#ifndef __ANIMA_GRAPHICS_SURFACE_ALLEGRO__
#define __ANIMA_GRAPHICS_SURFACE_ALLEGRO__

#include "AnimaGraphicsSurface.h"

#include "allegro5/allegro.h"

namespace AE
{
	namespace Graphics
	{
		class SurfaceAllegro;

		class BlitFunctorAllegro
		{
		public:
			BlitFunctorAllegro(AE::Graphics::SurfaceAllegro* object, void (AE::Graphics::SurfaceAllegro::*function)(void *, const AE::Math::Point2 &, const AE::Math::Point2 &))
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

			void setFunction(void (AE::Graphics::SurfaceAllegro::*function)(void *, const AE::Math::Point2 &, const AE::Math::Point2 &))
			{
				mFunction = function; 
			}

		private:
			void (AE::Graphics::SurfaceAllegro::*mFunction)(void *, const AE::Math::Point2 &, const AE::Math::Point2 &);
			AE::Graphics::SurfaceAllegro* mObject;
		};

		class BlitFromSurfaceFunctorAllegro
		{
		public:
			BlitFromSurfaceFunctorAllegro(AE::Graphics::SurfaceAllegro* object, void (AE::Graphics::SurfaceAllegro::*function)(AE::Graphics::Surface *, const AE::Math::Point2 &, const AE::Math::Point2 &))
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

			void setFunction(void (AE::Graphics::SurfaceAllegro::*function)(AE::Graphics::Surface *, const AE::Math::Point2 &, const AE::Math::Point2 &))
			{
				mFunction = function; 
			}

		private:
			void (AE::Graphics::SurfaceAllegro::*mFunction)(AE::Graphics::Surface *, const AE::Math::Point2 &, const AE::Math::Point2 &);
			AE::Graphics::SurfaceAllegro* mObject;
		};

		class SurfaceAllegro : public AE::Graphics::Surface
		{
		public:
			SurfaceAllegro(ALLEGRO_BITMAP *allegroBitmap);
			~SurfaceAllegro();

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
			ALLEGRO_BITMAP* _getAllegroBitmap() { return mAllegroBitmap; }

		protected:
			ALLEGRO_BITMAP				*mAllegroBitmap;
			BlitFunctorAllegro			*mBlitFunctor;
			BlitFromSurfaceFunctorAllegro	*mBlitFromSurfaceFunctor;
			AE::uint32					mPitch;
		};
	}
}

#endif