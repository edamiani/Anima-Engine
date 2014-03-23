#ifndef __ANIMA_GRAPHICS_SURFACE_GL__
#define __ANIMA_GRAPHICS_SURFACE_GL__

#include "AnimaPlatform.h"
#include "AnimaGraphicsSurface.h"
#include "AnimaGraphicsManagerGL.h"

#ifdef AE_PLATFORM_WIN32
	#include <gl/GL.h>
	#include <gl/GLU.h>
	#include "AnimaGraphicsOpenGLExtensions.h"
#elif defined(MAC_OS_X_VERSION_10_0)
	#include <OpenGL/gl.h>
	#include "AnimaGraphicsOpenGLExtensions.h"
#endif

namespace AE
{
	namespace Graphics
	{
		class SurfaceGL;

		class BlitFunctorGL
		{
		public:
			BlitFunctorGL(AE::Graphics::SurfaceGL* object, void (AE::Graphics::SurfaceGL::*function)(void *, const AE::Math::Point2 &, const AE::Math::Point2 &))
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

			void setFunction(void (AE::Graphics::SurfaceGL::*function)(void *, const AE::Math::Point2 &, const AE::Math::Point2 &))
			{
				mFunction = function; 
			}

		private:
			void (AE::Graphics::SurfaceGL::*mFunction)(void *, const AE::Math::Point2 &, const AE::Math::Point2 &);
			AE::Graphics::SurfaceGL* mObject;
		};

		class BlitFromSurfaceFunctorGL
		{
		public:
			BlitFromSurfaceFunctorGL(AE::Graphics::SurfaceGL* object, void (AE::Graphics::SurfaceGL::*function)(AE::Graphics::Surface *, const AE::Math::Point2 &, const AE::Math::Point2 &))
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

			void setFunction(void (AE::Graphics::SurfaceGL::*function)(AE::Graphics::Surface *, const AE::Math::Point2 &, const AE::Math::Point2 &))
			{
				mFunction = function; 
			}

		private:
			void (AE::Graphics::SurfaceGL::*mFunction)(AE::Graphics::Surface *, const AE::Math::Point2 &, const AE::Math::Point2 &);
			AE::Graphics::SurfaceGL* mObject;
		};

		class SurfaceGL : public AE::Graphics::Surface
		{
		public:
			SurfaceGL(AE::uint16 width, AE::uint16 height, AE::Graphics::SurfaceFormat surfaceFormat);
			~SurfaceGL();

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
			void _setOffScreen(bool isOffScreen) { mIsOffScreen = isOffScreen; }

		protected:
			BlitFunctorGL				*mBlitFunctor;
			BlitFromSurfaceFunctorGL	*mBlitFromSurfaceFunctor;
			bool						mIsOffScreen;
			GLenum						mPixelFormatGL;
			void						*mSurfaceGL;
			GLenum						mTypeGL;
			AE::uint16					mWidth, mHeight;
		};
	}
}

#endif