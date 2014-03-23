#ifndef __AE_GRAPHICS_DRAWING_CONTEXT_ALLEGRO__
#define __AE_GRAPHICS_DRAWING_CONTEXT_ALLEGRO__

#include "AnimaGraphicsDrawingContext.h"

#include "allegro5/allegro.h"

namespace AE
{
	namespace Graphics
	{
		class DrawingContextAllegro : public AE::Graphics::DrawingContext
		{
		public:
			DrawingContextAllegro(AE::Graphics::DeviceContext *parentDeviceContext, ALLEGRO_DISPLAY *allegroDisplay);
			virtual ~DrawingContextAllegro();

			ALLEGRO_DISPLAY* _getAllegroDisplay() { return mAllegroDisplay; }

		protected:
			ALLEGRO_DISPLAY *mAllegroDisplay;
		};
	}
}

#endif