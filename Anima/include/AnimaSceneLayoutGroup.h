#ifndef __AE_SCENE_LAYOUT_GROUP__
#define __AE_SCENE_LAYOUT_GROUP__

#include "AnimaSceneGroupingNode.h"
#include "AnimaSceneLayout.h"
#include "AnimaSceneViewport.h"

#include <list>

namespace AE
{
	namespace Scene
	{
		class LayoutGroup : public AE::Scene::GroupingNode
		{
		public:
			LayoutGroup(AE::Scene::Node *parentNode = 0)
				: GroupingNode(parentNode)
			{
				mLayout = new AE::Scene::Layout();
				mViewport = new AE::Scene::Viewport();
			}

			virtual ~LayoutGroup() 
			{
				delete mViewport;
				delete mLayout;
			}

		protected:
			AE::Scene::Layout *mLayout;
			AE::Scene::Viewport *mViewport;
		};
	}
}

#endif