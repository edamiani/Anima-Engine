#ifndef __AE_SCENE_X3D_COORDINATE__
#define __AE_SCENE_X3D_COORDINATE__

#include "AnimaMathVector3.h"
#include "AnimaSceneX3D_CoordinateNode.h"

#include <vector>

namespace AE
{
	namespace Scene
	{
		namespace X3D
		{
			class Coordinate : public _CoordinateNode
			{
			public:
				Coordinate(const std::vector<AE::Math::Vector3> &points) { mPoints = points; }
				virtual ~Coordinate() {}

				std::vector<AE::Math::Vector3>& getPoints() { return mPoints; }

			private:
				std::vector<AE::Math::Vector3> mPoints;
			};
		}
	}
}

#endif