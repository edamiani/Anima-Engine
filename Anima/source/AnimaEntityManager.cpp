#include "../include/AnimaEntityDynamic.h"
#include "../include/AnimaEntityKinematic.h"
#include "../include/AnimaEntityManager.h"
#include "../include/AnimaFramework.h"
#include "../include/AnimaGraphicsManager.h"
#include "../include/AnimaPhysicsManager.h"
#include "../include/AnimaGraphicsSprite.h"
#include "../include/AnimaPhysicsRigidBody.h"

namespace AE
{
	namespace Entity
	{
		void Manager::createDynamicEntity(AE::Entity::EntityDesc &entityDesc)
		{
			/*switch(entityDesc->getType())
			{
			case AE::Entity::ET_DYNAMIC:
				AE::Graphics::Sprite *sprite = mFramework->getGraphicsManager()->createSprite(entityDesc.sprite);
				AE::Physics::CollisionShape *collisionShape = mFramework->getPhysicsManager()->createCollisionShape(entityDesc.collisionShape);
				entityDesc.rigidBody.collisionShape = collisionShape;
				AE::Physics::RigidBody *rigidBody = mFramework->getPhysicsManager()->createRigidBody(entityDesc.rigidBody);

				AE::Entity::Dynamic *dynamic = new AE::Entity::Dynamic(sprite, rigidBody);
				mDynamics[entityDesc.sprite.name] = dynamic;

				break;
			}*/

			AE::Graphics::SpriteDesc spriteDesc;
			spriteDesc.initialAnimation = entityDesc.initialAnimation;
			spriteDesc.isVisible = entityDesc.isVisible;
			spriteDesc.mesh = entityDesc.mesh;
			spriteDesc.name = entityDesc.name;
			spriteDesc.orientation = entityDesc.orientation;
			spriteDesc.position = entityDesc.position;
			spriteDesc.prefabType = entityDesc.prefabType;
			spriteDesc.scale = entityDesc.scale;
			spriteDesc.shadowCaster = entityDesc.shadowCaster;

			AE::Graphics::Sprite *sprite = mFramework->getGraphicsManager()->createSprite(spriteDesc);

			AE::Physics::RigidBodyDesc rigidBodyDesc;
			rigidBodyDesc.collisionShape = entityDesc.collisionShape;
			rigidBodyDesc.mass = entityDesc.mass;
			rigidBodyDesc.rigidBodyType = entityDesc.rigidBodyType;
			rigidBodyDesc.sprite = sprite;

			AE::Physics::RigidBody *rigidBody = mFramework->getPhysicsManager()->createRigidBody(rigidBodyDesc);

			AE::Entity::Dynamic *dynamic = new AE::Entity::Dynamic(sprite, rigidBody);
			mDynamics[spriteDesc.name] = dynamic;

			//return dynamic;
		}

		AE::Entity::Dynamic* Manager::createDynamicEntity(AE::Graphics::SpriteDesc &spriteDesc, AE::Physics::RigidBodyDesc &rigidBodyDesc)
		{
			AE::Graphics::Sprite *sprite = mFramework->getGraphicsManager()->createSprite(spriteDesc);

			rigidBodyDesc.sprite = sprite;
			AE::Physics::RigidBody *rigidBody = mFramework->getPhysicsManager()->createRigidBody(rigidBodyDesc);
			
			AE::Entity::Dynamic *dynamic = new AE::Entity::Dynamic(sprite, rigidBody);
			mDynamics[spriteDesc.name] = dynamic;

			return dynamic;
		}

		AE::Entity::Kinematic* Manager::createKinematicEntity(AE::Graphics::SpriteDesc &spriteDesc, AE::Physics::RigidBodyDesc &rigidBodyDesc)
		{
			AE::Graphics::Sprite *sprite = mFramework->getGraphicsManager()->createSprite(spriteDesc);

			rigidBodyDesc.sprite = sprite;
			AE::Physics::RigidBody *rigidBody = mFramework->getPhysicsManager()->createRigidBody(rigidBodyDesc);
			
			AE::Entity::Kinematic *kinematic = new AE::Entity::Kinematic(sprite, rigidBody);
			mKinematics[spriteDesc.name] = kinematic;

			return kinematic;
		}

		void Manager::destroyDynamicEntity(const std::string &name){}
		void Manager::destroyDynamicEntity(AE::Entity::Dynamic *dynamic){}
		void Manager::destroyKinematicEntity(AE::Entity::Kinematic *kinematic){}
		AE::Entity::Dynamic* Manager::getDynamicEntity(const std::string &name){return 0;}
		void Manager::initialize(AE::Framework *framework){}
	}
}