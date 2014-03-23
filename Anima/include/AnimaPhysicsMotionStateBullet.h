#ifndef __AE_ANIMA_PHYSICS_MANAGER_BULLET__
#define __AE_ANIMA_PHYSICS_MANAGER_BULLET__

#include "AnimaPrerequisites.h"

#include "btBulletDynamicsCommon.h"
#include "btVector3.h"

namespace AE
{
	namespace Physics
	{
		class MotionStateBullet : public btMotionState 
		{
		public:
			MotionStateBullet(const btTransform &initialPosition, AE::Graphics::Sprite *sprite) 
			{
				mSprite = sprite;
				mTransform = initialPosition;
			}
			
			virtual ~MotionStateBullet() { }
			
			//void setNode(Ogre::SceneNode *node) { mVisibleobj = node; }
			
			virtual void getWorldTransform(btTransform &worldTrans) const { worldTrans = mTransform; }
			
			virtual void setWorldTransform(const btTransform &worldTrans);

		private:
			AE::Graphics::Sprite* mSprite;
			btTransform mTransform;
		};
	}
}

#endif