#ifndef __AE_SCENE_VIEWPORT__
#define __AE_SCENE_VIEWPORT__

namespace AE
{
	namespace Scene
	{
		class Viewport
		{
		public:
			Viewport() : mClipBoundary(1, 0, 0, 1) {}
			~Viewport() {}

		protected:
			struct clipBoundary
			{
				clipBoundary(AE::Real t, AE::Real l, AE::Real b, AE::Real r) : top(t), left(l), bottom(b), right(r) {}

				AE::Real top;
				AE::Real left;
				AE::Real bottom;
				AE::Real right;
			} mClipBoundary;
		};
	}
}

#endif