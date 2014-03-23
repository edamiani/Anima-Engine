#ifndef __AE_SCENE_X3D__NODE__
#define __AE_SCENE_X3D__NODE__

#include "AnimaSceneNode.h"
#include "AnimaSceneX3D_MetadataObject.h"

namespace AE
{
	namespace Scene
	{
		namespace X3D
		{
			class _Node : public AE::Scene::Node
			{
			public:
				_Node() : mMetadata(0) { }
				virtual ~_Node() {}

				AE::Scene::X3D::_MetadataObject* getMetadata() { return mMetadata; }
				void setMetadata(AE::Scene::X3D::_MetadataObject *metadata) { mMetadata = metadata; }

			protected:
				AE::Scene::X3D::_MetadataObject	*mMetadata;
			};
		}
	}
}

#endif