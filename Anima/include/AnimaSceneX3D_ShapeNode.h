#ifndef __AE_SCENE_X3D__SHAPE_NODE__
#define __AE_SCENE_X3D__SHAPE_NODE__

#include "AnimaSceneX3D_AppearanceNode.h"
#include "AnimaSceneX3D_BoundedObject.h"
#include "AnimaSceneX3D_ChildNode.h"
#include "AnimaSceneX3D_GeometryNode.h"

namespace AE
{
	namespace Scene
	{
		namespace X3D
		{
			class _ShapeNode : public _ChildNode, public _BoundedObject
			{
			public:
				_ShapeNode() : mAppearance(0), mGeometry(0) {}
				_ShapeNode(_AppearanceNode *appearance, _GeometryNode *geometry)
					: mAppearance(appearance), mGeometry(geometry) {}
				virtual ~_ShapeNode() {}

				_AppearanceNode* getAppearance() { return mAppearance; }
				_GeometryNode* getGeometry() { return mGeometry; }
				void setAppearance(_AppearanceNode *appearance) { mAppearance = appearance; }
				void setGeometry(_GeometryNode *geometry) { mGeometry = geometry; }

			protected:
				_AppearanceNode	*mAppearance;
				_GeometryNode		*mGeometry;
			};
		}
	}
}

#endif