#ifndef __AE_SCENE_NODE__
#define __AE_SCENE_NODE__

#include <list>

namespace AE
{
	namespace Scene
	{
		enum NodeType
		{
			NT_UNDEFINED	= 0,
			NT_GROUP		= 1,
			NT_TRANSFORM	= 2,
			NT_SHAPE		= 4,
			NT_BINDABLE		= 8,
			NT_BOUNDED		= 16,
			NT_ROOT			= 32,
			NT_CHILD		= 64,
			NT_LAYER		= 128
		};

		class Node
		{
		public:
			Node(AE::Scene::Node *parentNode = 0) 
				: mParentNode(parentNode), mType(NT_UNDEFINED) { }
			virtual ~Node() {}

			AE::Scene::NodeType getType() { return mType; }
			AE::Scene::Node* getParentNode() { return mParentNode; }
			void setParentNode(AE::Scene::Node *parentNode) { mParentNode = parentNode; }
			virtual void traverse() = 0;

		protected:
			AE::Scene::NodeType mType;
			AE::Scene::Node *mParentNode;
		};
	}
}

#endif