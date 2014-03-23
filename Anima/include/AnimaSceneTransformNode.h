#ifndef __AE_SCENE_TRANSFORM_NODE__
#define __AE_SCENE_TRANSFORM_NODE__

#include "AnimaSceneGroupingNode.h"
#include "AnimaMathMatrix4.h"
#include "AnimaMathVector3.h"

#include <list>

namespace AE
{
	namespace Scene
	{
		class TransformNode : public AE::Scene::GroupingNode
		{
		public:
			TransformNode(AE::Scene::GroupingNode *parentNode = 0) 
				: GroupingNode(parentNode) 
			{
				mType = (AE::Scene::NodeType)(mType | AE::Scene::NT_TRANSFORM);
				mLocalTransformationMatrix.setIdentity();

				if(parentNode)
				{
					parentNode->addChild(this);
					/*if(parentNode->getType() == AE::Scene::NT_TRANSFORM)
						mLocalTransformationMatrix = mLocalTransformationMatrix * static_cast<AE::Scene::TransformNode *>(parentNode)->getTransformationMatrix();*/
				}
			}

			virtual ~TransformNode() {}

			AE::Math::Matrix4 getTransformationMatrix() { return mLocalTransformationMatrix; }
			void setTransformationMatrix(const AE::Math::Matrix4 &m) { mLocalTransformationMatrix = m; }
			
			void translate(const AE::Math::Vector3 &translation)
			{
				mLocalTransformationMatrix[3][0] += translation.x;
				mLocalTransformationMatrix[3][1] += translation.y;
			}

		protected:
			AE::Math::Vector3 mLocalPosition;
			AE::Math::Matrix4 mLocalTransformationMatrix;
		};
	}
}

#endif