#ifndef __AE_GRAPHICS_AXES_CONVENTION_2D__
#define __AE_GRAPHICS_AXES_CONVENTION_2D__

#include <cassert>

namespace AE
{
	namespace Graphics
	{
		enum HorizontalDirection
		{
			HD_LEFT_TO_RIGHT,
			HD_RIGHT_TO_LEFT
		};

		enum VerticalDirection
		{
			VD_BOTTOM_TO_TOP,
			VD_TOP_TO_BOTTOM
		};

		class AxesConvention2d
		{
		public:
			AxesConvention2d() { }
			~AxesConvention2d() { }

			static AE::Graphics::HorizontalDirection horizontalDirection;
			static AE::Graphics::VerticalDirection verticalDirection;

			/*AE::Graphics::HorizontalDirection getHorizontalDirection() { return mHorizontalDirection; }
			AE::Graphics::VerticalDirection getVerticalDirection() { return mVerticalDirection; }
			void setHorizontalDirection(AE::Graphics::HorizontalDirection horizontalDirection) { mHorizontalDirection = horizontalDirection; }
			void setVerticalDirection(AE::Graphics::VerticalDirection verticalDirection) { mVerticalDirection = verticalDirection; }*/
		};
	}
}

#endif