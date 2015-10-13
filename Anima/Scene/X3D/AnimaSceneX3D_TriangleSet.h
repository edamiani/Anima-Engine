#ifndef __AE_SCENE_X3D__TRIANGLE_SET__
#define __AE_SCENE_X3D__TRIANGLE_SET__

#include "AnimaSceneX3D_ComposedGeometryNode.h"

namespace AE
{
	namespace Graphics
	{
		class VertexBuffer;
	}

	namespace Scene
	{
		namespace X3D
		{
			class _TriangleSet : public _ComposedGeometryNode
			{
			public:
				_TriangleSet(Coordinate *coordinates);
				virtual ~_TriangleSet() {}

			private:
				AE::Graphics::VertexBuffer *mVertexBuffer;
			};
		}
	}
}

#endif