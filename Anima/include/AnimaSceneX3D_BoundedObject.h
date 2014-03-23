#ifndef __AE_SCENE_X3D__BOUNDED_OBJECT__
#define __AE_SCENE_X3D__BOUNDED_OBJECT__

#include "AnimaMathVector3.h"

namespace AE
{
	namespace Scene
	{
		namespace X3D
		{
			class _BoundedObject
			{
			public:
				_BoundedObject() : mBoundingBoxCenter(0, 0, 0), mBoundingBoxSize(-1, -1, -1) {}
				virtual ~_BoundedObject() {}

				AE::Math::Vector3& getBoundingBoxCenter() { return mBoundingBoxCenter; }
				AE::Math::Vector3& getBoundingBoxSize() { return mBoundingBoxSize; }
				void setBoundingBoxCenter(AE::Math::Vector3 &boundingBoxCenter) { mBoundingBoxCenter = boundingBoxCenter; }
				void setBoundingBoxSize(AE::Math::Vector3 &boundingBoxSize) { mBoundingBoxSize = boundingBoxSize; }

			protected:
				AE::Math::Vector3 mBoundingBoxCenter;
				AE::Math::Vector3 mBoundingBoxSize;
			};
		}
	}
}

#endif