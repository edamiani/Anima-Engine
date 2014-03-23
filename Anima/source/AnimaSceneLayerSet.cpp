#include "../include/AnimaSceneLayerSet.h"

namespace AE
{
	namespace Scene
	{
		LayerSet::LayerSet() : mActiveLayer(0) 
		{
		}

		LayerSet::~LayerSet() 
		{
		}

		void LayerSet::addLayer(Layer* layer) 
		{ 
			mLayers.push_back(layer);
			mOrder.push_back(mLayers.size() - 1);
		}

		void LayerSet::removeLayer(Layer* layer) 
		{
			std::vector<AE::Scene::Layer *>::iterator i = mLayers.begin();
			AE::uint layerCount = 0;
			for(i; i != mLayers.end(); i++)
			{
				if(*i == layer)
				{
					mLayers.erase(i);

					std::list<AE::uint>::iterator j = mOrder.begin();
					for(j; j != mOrder.end(); j++)
					{
						if(*j == layerCount)
							j = mOrder.erase(j);
					}

					break;
				}

				layerCount++;
			}
		}
		
		void LayerSet::setActiveLayer(AE::uint layerNum) 
		{ 
			mActiveLayer = layerNum; 
		}
	}
}