#ifndef __AE_SCENE_LAYER_SET__
#define __AE_SCENE_LAYER_SET__

#include "AnimaTypes.h"
#include "AnimaSceneLayer.h"

#include <list>
#include <vector>

namespace AE
{
	namespace Scene
	{
		class LayerSet
		{
		public:
			LayerSet();
			~LayerSet();

			void addLayer(Layer* layer);
			void removeLayer(Layer* layer);
			void setActiveLayer(AE::uint layerNum);

		protected:
			AE::uint mActiveLayer;
			std::vector<AE::Scene::Layer *> mLayers;
			std::list<AE::uint> mOrder;
		};
	}
}

#endif