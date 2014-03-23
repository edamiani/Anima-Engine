/*
-------------------------------------------------------------------------------

Class: ManagerBox2d

Module: AE::Physics2d

Description: Realization of the Box2d plugin

-------------------------------------------------------------------------------
*/

#ifndef __AE_PHYSICS2D_MANAGER_BOX2D__
#define __AE_PHYSICS2D_MANAGER_BOX2D__

#include "AnimaPhysics2dManagerBox2d.h"

#include <map>
#include <string>

namespace AE
{
	namespace Physics2d
	{
		class World;

		class ManagerBox2d : public AE::Physics2d::Manager
		{
		public:
										ManagerBox2d();
										~ManagerBox2d();

			AE::Physics2d::Body*		createBody(const AE::Physics2d::BodyDesc &bodyDesc);
			AE::Physics2d::Dynamic*		createDynamicBody(AE::Entity::SpriteDesc &spriteDesc, const AE::Physics2d::BodyDesc &bodyDesc);
			void						createJoint(const JointDesc &jointDesc);
			AE::Physics2d::Kinematic*	createKinematicBody(AE::Entity::SpriteDesc &spriteDesc, const AE::Physics2d::BodyDesc &bodyDesc);
			AE::Physics2d::Material*	createMaterial(const AE::Physics2d::MaterialDesc &material);
			AE::Physics2d::Static*		createStaticBody(AE::Entity::SpriteDesc &spriteDesc, const AE::Physics2d::BodyDesc &bodyDesc);
			AE::Physics2d::Trigger*		createTrigger(AE::Entity::SpriteDesc &spriteDesc, const AE::Physics2d::BodyDesc &bodyDesc);
			AE::Physics2d::World*		createWorld(const std::string &name, const AE::Math::Vector2 &gravity);
			void						destroyBody(AE::Physics2d::Body *body);
			void						destroyDynamicEntity(AE::Entity::Dynamic *dynamic);
			void						destroyKinematicEntity(AE::Entity::Kinematic *kinematic);
			void						destroyStaticEntity(AE::Entity::Static *staticEntity);
			AE::Physics2d::Body*		getBody(const std::string &name);
			AE::Physics2d::Material*	getDefaultMaterial();
			AE::Real					getDistanceFromClosestObject(AE::Vector2 position, AE::Vector3 direction, AE::Real rayDistance = 3000.0);
			AE::Physics2d::Material*	getMaterial(const std::string &name);
			void						initialize(AE::Framework *framework);
			bool						isPointInCircle(const AE::Vector3 &sphereCenter, AE::Real sphereRadius, const AE::Vector3 &point);
			AE::uint32					raycastClosestObject(AE::Vector3 position, AE::Vector3 direction, AE::Real rayDistance = 3000.0);
			void						setCollisionPairFlags(AE::Physics2d::Body *body1, AE::Physics2d::Body *body2, AE::uint32 collisionNotify);
			void						setGravity(AE::Real gravity);
			void						setBodyGroup(AE::Physics2d::Body *body, AE::uint16 group);
			void						stepSimulation(AE::Real dt);

		private:
			std::map<std::string, AE::Physics2d::World *> mWorlds;
		};
	}
}

#endif