#ifndef __ANIMA_GRAPHICS_SURFACE_OGRE__
#define __ANIMA_GRAPHICS_SURFACE_OGRE__

#include "AnimaGraphicsSurface.h"

#include "Ogre.h"

namespace AE
{
	namespace Graphics
	{
		class SurfaceOgre;

		class BlitFunctorOgre
		{
		public:
			BlitFunctorOgre(AE::Graphics::SurfaceOgre* object, void (AE::Graphics::SurfaceOgre::*function)(void *, const AE::Math::Point2 &, const AE::Math::Point2 &))
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

			void setFunction(void (AE::Graphics::SurfaceOgre::*function)(void *, const AE::Math::Point2 &, const AE::Math::Point2 &))
			{
				mFunction = function; 
			}

		private:
			void (AE::Graphics::SurfaceOgre::*mFunction)(void *, const AE::Math::Point2 &, const AE::Math::Point2 &);
			AE::Graphics::SurfaceOgre* mObject;
		};

		class BlitFromSurfaceFunctorOgre
		{
		public:
			BlitFromSurfaceFunctorOgre(AE::Graphics::SurfaceOgre* object, void (AE::Graphics::SurfaceOgre::*function)(AE::Graphics::Surface *, const AE::Math::Point2 &, const AE::Math::Point2 &))
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

			void setFunction(void (AE::Graphics::SurfaceOgre::*function)(AE::Graphics::Surface *, const AE::Math::Point2 &, const AE::Math::Point2 &))
			{
				mFunction = function; 
			}

		private:
			void (AE::Graphics::SurfaceOgre::*mFunction)(AE::Graphics::Surface *, const AE::Math::Point2 &, const AE::Math::Point2 &);
			AE::Graphics::SurfaceOgre* mObject;
		};

		class SurfaceOgre : public AE::Graphics::Surface
		{
		public:
			SurfaceOgre(/*ALLEGRO_BITMAP *allegroBitmap*/);
			~SurfaceOgre();

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
			//ALLEGRO_BITMAP* _getAllegroBitmap() { return mAllegroBitmap; }

		protected:
			//ALLEGRO_BITMAP				*mAllegroBitmap;
			BlitFunctorOgre			*mBlitFunctor;
			BlitFromSurfaceFunctorOgre	*mBlitFromSurfaceFunctor;
			AE::uint32					mPitch;
		};
	}
}

#endif