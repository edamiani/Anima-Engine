#ifndef __ANIMA_GRAPHICS_SPRITE_OGRE__
#define __ANIMA_GRAPHICS_SPRITE_OGRE__

#include "AnimaGraphicsSprite.h"
#include "AnimaGraphicsManagerOgre.h"

namespace AE
{
	namespace Graphics
	{
		class SpriteOgre : public AE::Graphics::Sprite
		{
		public:
			SpriteOgre(Ogre::Entity *entity, AE::Math::Vector3 position, AE::Math::Quaternion orientation) 
				: mOgreEntity(entity) 
			{ 
				mOgreSceneNode = mOgreEntity->getParentSceneNode(); 
				setPosition(position);
				setOrientation(orientation);
			}
			~SpriteOgre() { mOgreEntity = 0; mOgreSceneNode = 0;  }

			void setOrientation(AE::Math::Quaternion orientation)
			{
				mOrientation.x = orientation.x;
				mOrientation.y = orientation.y;
				mOrientation.z = orientation.z;
				mOrientation.w = orientation.w;

				Ogre::Quaternion ogreOrientation = Ogre::Quaternion(orientation.w, orientation.x, orientation.y, orientation.z);
				mOgreSceneNode->setOrientation(ogreOrientation);
			}

			void setOrientation(AE::Real x, AE::Real y, AE::Real z, AE::Real w)
			{
				mOrientation.x = x;
				mOrientation.y = y;
				mOrientation.z = z;
				mOrientation.w = w;

				Ogre::Quaternion ogreOrientation = Ogre::Quaternion(w, x, y, z);
				mOgreSceneNode->setOrientation(ogreOrientation);
			}

			void setPosition(AE::Math::Vector3 position)
			{
				mPosition.x = position.x;
				mPosition.y = position.y;
				mPosition.z = position.z;

				Ogre::Vector3 ogrePosition = Ogre::Vector3(position.x, position.y, position.z);
				mOgreSceneNode->setPosition(ogrePosition);
			}

			void setPosition(AE::Real x, AE::Real y, AE::Real z)
			{
				mPosition.x = x;
				mPosition.y = y;
				mPosition.z = z;

				Ogre::Vector3 ogrePosition = Ogre::Vector3(x, y, z);
				mOgreSceneNode->setPosition(ogrePosition);
			}

			Ogre::Entity* _getOgreEntity() { return mOgreEntity; }

		protected:
			Ogre::Entity *mOgreEntity;
			Ogre::SceneNode *mOgreSceneNode;
		};
	}
}


#endif