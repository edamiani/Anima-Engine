#ifndef __AE_SCENE_X3D_INDEXED_LINE_SET__
#define __AE_SCENE_X3D_INDEXED_LINE_SET__

#include "AnimaSceneX3D_GeometryNode.h"
#include "AnimaSceneX3DCoordinate.h"

#include <vector>

namespace AE
{
	namespace Graphics
	{
		class IndexBuffer;
		class VertexBuffer;
	}

	namespace Scene
	{
		namespace X3D
		{
			class IndexedLineSet : public AE::Scene::X3D::_GeometryNode
			{
			public:
				IndexedLineSet(Coordinate *coordinates, const std::vector<AE::int32> &coordinateIndices);
				virtual ~IndexedLineSet() {}

			private:
				Coordinate *mCoordinates;
				std::vector<AE::int32> mCoordinateIndices;
			};
		}
	}
}

#endif