#ifndef __AE_SCENE_LAYOUT_LAYER__
#define __AE_SCENE_LAYOUT_LAYER__

#include "AnimaSceneLayer.h"
#include "AnimaSceneLayout.h"
#include "AnimaSceneLayoutGroup.h"

namespace AE
{
	namespace Scene
	{
		class LayoutLayer : public AE::Scene::Layer
		{
		public:
			LayoutLayer() 
			{
				mLayout = new AE::Scene::Layout();
			}

			virtual ~LayoutLayer() 
			{
				delete mLayout;
			}

			void addLayoutGroup(AE::Scene::LayoutGroup *layoutGroup) { mLayoutGroups.push_back(layoutGroup); }
			void removeLayoutGroup(AE::Scene::LayoutGroup *layoutGroup) { mLayoutGroups.remove(layoutGroup); }

		protected:
			AE::Scene::Layout *mLayout;
			std::list<AE::Scene::LayoutGroup *> mLayoutGroups;
		};
	}
}

#endif