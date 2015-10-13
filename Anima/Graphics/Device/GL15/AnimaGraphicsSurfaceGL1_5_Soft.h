#ifndef __ANIMA_GRAPHICS_SURFACE_GL1_5__
#define __ANIMA_GRAPHICS_SURFACE_GL1_5__

#include "AnimaGraphicsSurface.h"

#include "AnimaGraphicsAxesConvention2d.h"
#include "AnimaGraphicsEnums.h"
#include "AnimaGraphicsSurfaceDesc.h"
#include "AnimaPlatform.h"

#ifdef AE_PLATFORM_WIN32
#   include <gl/GL.h>
#   include <gl/GLU.h>
#   include "AnimaGraphicsOpenGLExtensions.h"
#elif defined(AE_PLATFORM_OSX)
#   include <AGL/AGL.h>
#   include <OpenGL/gl.h>
#   include <OpenGL/glu.h>
#   include "AnimaGraphicsOpenGLExtensions.h"
#elif defined(AE_PLATFORM_LINUX)
#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <GL/glx.h>
#   include "AnimaGraphicsOpenGLExtensions.h"
#endif

namespace AE
{
	namespace Graphics
	{
		class SurfaceGL1_5;

		class BlitFunctorGL1_5
		{
		public:
			BlitFunctorGL1_5(AE::Graphics::SurfaceGL1_5* object, void (AE::Graphics::SurfaceGL1_5::*function)(void *, const AE::Math::Point2 &, const AE::Math::Point2 &))
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

			void setFunction(void (AE::Graphics::SurfaceGL1_5::*function)(void *, const AE::Math::Point2 &, const AE::Math::Point2 &))
			{
				mFunction = function; 
			}

		private:
			void (AE::Graphics::SurfaceGL1_5::*mFunction)(void *, const AE::Math::Point2 &, const AE::Math::Point2 &);
			AE::Graphics::SurfaceGL1_5* mObject;
		};

		class BlitFromSurfaceFunctorGL1_5
		{
		public:
			BlitFromSurfaceFunctorGL1_5(AE::Graphics::SurfaceGL1_5* object, void (AE::Graphics::SurfaceGL1_5::*function)(AE::Graphics::Surface *, const AE::Math::Point2 &, const AE::Math::Point2 &))
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

			void setFunction(void (AE::Graphics::SurfaceGL1_5::*function)(AE::Graphics::Surface *, const AE::Math::Point2 &, const AE::Math::Point2 &))
			{
				mFunction = function; 
			}

		private:
			void (AE::Graphics::SurfaceGL1_5::*mFunction)(AE::Graphics::Surface *, const AE::Math::Point2 &, const AE::Math::Point2 &);
			AE::Graphics::SurfaceGL1_5* mObject;
		};

		class SurfaceGL1_5 : public AE::Graphics::Surface
		{
		public:
			//SurfaceGL1_5(const AE::Math::Point2 &dimensions, AE::Graphics::SurfaceFormat surfaceFormat);
			SurfaceGL1_5(const AE::Graphics::SurfaceDesc &surfaceDesc);
			~SurfaceGL1_5();

			void blit(AE::Graphics::Surface *sourceSurface, const AE::Math::Point2 &dimensions, const AE::Math::Point2 &position);
			void blit(void *source, const AE::Math::Point2 &dimensions, const AE::Math::Point2 &position);
			void clear(const AE::Graphics::Color &backgroundColor);
			void* getData();
			void lock(AE::Graphics::LockType lockType);
			void plot(const AE::Graphics::Color &color, const AE::Math::Point2 &position);
			void plot32(const AE::uint32 color, const AE::Math::Point2 &position);
			void unlock();

			void _blit(AE::Graphics::Surface *sourceSurface, const AE::Math::Point2 &dimensions, const AE::Math::Point2 &position);
			void _blitAlpha(void *source, const AE::Math::Point2 &dimensions, const AE::Math::Point2 &position);
			void _blitNoAlpha(void *source, const AE::Math::Point2 &dimensions, const AE::Math::Point2 &position);
			void _setOffScreen(bool isOffScreen) { mIsOffScreen = isOffScreen; }

		protected:
			BlitFunctorGL1_5			*mBlitFunctor;
			BlitFromSurfaceFunctorGL1_5	*mBlitFromSurfaceFunctor;
			bool						mIsOffScreen;
			GLenum						mPixelFormatGL;
			void						*mSurfaceGL;
			GLenum						mTypeGL;
		};
	}
}

#endif
