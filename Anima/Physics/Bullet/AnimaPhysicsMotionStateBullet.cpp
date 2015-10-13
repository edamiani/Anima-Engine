#include "../include/AnimaPhysicsMotionStateBullet.h"
#include "../include/AnimaGraphicsSprite.h"

namespace AE
{
	namespace Physics
	{
		void MotionStateBullet::setWorldTransform(const btTransform &worldTrans) 
		{
			if(NULL == mSprite) return; // silently return before we set a node
			
			btQuaternion rot = worldTrans.getRotation();
			mSprite->setOrientation(rot.x(), rot.y(), rot.z(), rot.w());
			
			btVector3 pos = worldTrans.getOrigin();
			mSprite->setPosition(pos.x(), pos.y(), pos.z());
		}
	}
}