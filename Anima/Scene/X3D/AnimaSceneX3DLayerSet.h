#ifndef __AE_SCENE_X3D_LAYER_SET__
#define __AE_SCENE_X3D_LAYER_SET__

#include "AnimaSceneX3D_Node.h"
#include "AnimaSceneX3DLayer.h"

#include <list>
#include <vector>

namespace AE
{
	namespace Scene
	{
		namespace X3D
		{
			class LayerSet : public _Node
			{
			public:
				LayerSet();
				~LayerSet();

				void addLayer(Layer* layer);
				void removeLayer(Layer* layer);
				void setActiveLayer(AE::uint layerNum);

			protected:
				AE::uint mActiveLayer;
				std::vector<AE::Scene::X3D::Layer *> mLayers;
				std::list<AE::uint> mOrder;
			};
		}
	}
}

#endif