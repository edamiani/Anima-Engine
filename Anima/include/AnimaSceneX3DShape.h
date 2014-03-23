#ifndef __AE_SCENE_X3D_SHAPE__
#define __AE_SCENE_X3D_SHAPE__

#include "AnimaSceneX3D_AppearanceNode.h"
#include "AnimaSceneX3D_ShapeNode.h"

namespace AE
{
	namespace Scene
	{
		namespace X3D
		{
			class Shape : public AE::Scene::X3D::_ShapeNode
			{
			public:
				_Shape() : mAppearance(0), mGeometry(0) {}
				_Shape(_AppearanceNode *appearance, _GeometryNode *geometry)
					: mAppearance(appearance), mGeometry(geometry) {}
				virtual ~_Shape() {}

				_AppearanceNode* getAppearance() { return mAppearance; }
				_GeometryNode* getGeometry() { return mGeometry; }
				void setAppearance(AE::Scene::X3D::_AppearanceNode *appearance) { mAppearance = appearance; }
				void setGeometry(AE::Scene::X3D::_GeometryNode *geometry) { mGeometry = geometry; }

			protected:
				AE::Scene::X3D::_AppearanceNode	*mAppearance;
				AE::Scene::X3D::_GeometryNode	*mGeometry;
			};
		}
	}
}

#endif