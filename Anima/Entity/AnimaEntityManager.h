#ifndef __AE_ENTITY_MANAGER__
#define __AE_ENTITY_MANAGER__

#include "AnimaPrerequisites.h"
#include "AnimaMathAxisAlignedBox.h"
#include "AnimaGraphicsSprite.h"
#include "AnimaPhysicsManager.h"
#include "AnimaPhysicsRigidBody.h"
#include "AnimaPhysicsCollisionShape.h"

namespace AE
{
	namespace Entity
	{
		enum EntityType
		{
			ET_DYNAMIC,
			ET_KINEMATIC,
			ET_SPRITE,
			ET_STATIC,
			ET_TRIGGER,
			ET_VEHICLE
		};

		/*struct EntityDesc
		{
		public:
			EntityDesc(AE::Entity::EntityType type) : _type(type) 
			{
				switch(type)
				{
					case AE::Entity::ET_DYNAMIC: rigidBody.rigidBodyType = AE::Physics::RB_DYNAMIC; break;
					case AE::Entity::ET_KINEMATIC: rigidBody.rigidBodyType = AE::Physics::RB_KINEMATIC; break;
					case AE::Entity::ET_STATIC: rigidBody.rigidBodyType = AE::Physics::RB_STATIC; break;
				}
			}
			~EntityDesc() {}

			AE::Graphics::SpriteDesc sprite;
			AE::Physics::CollisionShapeDesc collisionShape;
			AE::Physics::RigidBodyDesc rigidBody;

			AE::Entity::EntityType getType() { return _type; }
		protected:
			AE::Entity::EntityType _type;
		};*/

		/*struct DynamicEntityDesc : public EntityDesc
		{
			AE::Graphics::SpriteDesc sprite;
			AE::Physics::CollisionShapeDesc collisionShape;
			AE::Physics::RigidBodyDesc rigidBody;

			DynamicEntityDesc() 
			{ 
				_type = AE::Entity::ET_DYNAMIC;
				rigidBody.rigidBodyType = AE::Physics::RB_DYNAMIC;
			}
			~DynamicEntityDesc() {}
		};

		struct KinematicEntityDesc : public EntityDesc
		{
			AE::Graphics::SpriteDesc sprite;
			AE::Physics::CollisionShapeDesc collisionShape;
			AE::Physics::RigidBodyDesc rigidBody;

			KinematicEntityDesc() 
			{ 
				_type = AE::Entity::ET_KINEMATIC;
				rigidBody.mass = 0.0f;
				rigidBody.rigidBodyType = AE::Physics::RB_KINEMATIC;
			}
		};

		struct StaticEntityDesc : public EntityDesc
		{
			AE::Graphics::SpriteDesc sprite;
			AE::Physics::CollisionShapeDesc collisionShape;

			StaticEntityDesc() 
			{
				_type = AE::Entity::ET_STATIC; 
			}
		};*/

		struct EntityDesc
		{
		public:
			AE::Math::AxisAlignedBox	boundingBox;
			AE::Real					boundingRadius;
			AE::Physics::CollisionShape	*collisionShape;
			std::string					initialAnimation;
			bool						isVisible;
			AE::Real					mass;
			std::string					mesh;
			std::string					name;
			//AE::Scene::Node*			node;
			AE::Math::Quaternion		orientation;
			AE::Math::Vector3			position;
			AE::Graphics::PrefabType	prefabType;
			AE::Physics::RigidBodyType	rigidBodyType;
			AE::Math::Vector3			scale;
			bool						shadowCaster;
			AE::Graphics::Sprite		*sprite;
			AE::Entity::EntityType		type;

			EntityDesc()
			{
				collisionShape = 0;
				initialAnimation = "";
				isVisible = true;
				mass = 0.0f;
				mesh = "";
				name = "";
				//node = 0;
				orientation = AE::Math::Quaternion::IDENTITY;
				position = AE::Math::Vector3::ZERO;
				prefabType = AE::Graphics::PF_NONE;
				scale = AE::Math::Vector3::UNIT_SCALE;
				shadowCaster = false;
				sprite = 0;
				type = AE::Entity::ET_SPRITE;
			}

			~EntityDesc() { }
		};

		class Manager
		{
		public:
										Manager(AE::Framework *framework) : mFramework(framework) { }
										~Manager() {  }
			
			void						createDynamicEntity(AE::Entity::EntityDesc &entityDesc);
			AE::Entity::Dynamic*		createDynamicEntity(AE::Graphics::SpriteDesc &spriteDesc, AE::Physics::RigidBodyDesc &rigidBodyDesc);
			AE::Entity::Kinematic*		createKinematicEntity(AE::Graphics::SpriteDesc &spriteDesc, AE::Physics::RigidBodyDesc &rigidBodyDesc);			
			//AE::Entity::Static*			createStaticEntity(AE::Graphics::SpriteDesc &spriteDesc, const AE::Physics::RigidBodyDesc &rigidBodyDesc);
			void						destroyDynamicEntity(const std::string &name);
			void						destroyDynamicEntity(AE::Entity::Dynamic *dynamic);
			void						destroyKinematicEntity(AE::Entity::Kinematic *kinematic);
			//void						destroyStaticEntity(AE::Entity::Static *staticEntity);
			AE::Entity::Dynamic*		getDynamicEntity(const std::string &name);
			//AE::Entity::Kinematic*		getKinematicEntity(const std::string &name);
			//AE::Entity::Static*			getStaticEntity(const std::string &name);
			void						initialize(AE::Framework *framework);
			//void						updateEntities(unsigned long timeSinceLastFrame);

		private:
			AE::Framework												*mFramework;

			std::map<std::string, AE::Entity::Dynamic*>					mDynamics;
			std::map<std::string, AE::Entity::Dynamic*>::iterator		mDynamicsIterator;
			std::map<std::string, AE::Entity::Kinematic*>				mKinematics;
			std::map<std::string, AE::Entity::Kinematic*>::iterator		mKinematicsIterator;
			/*std::map<std::string, AE::Entity::Static*>					mStatics;
			std::map<std::string, AE::Entity::Static*>::iterator		mStaticsIterator;*/
		};
	}
}

#endif