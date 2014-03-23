/*
-----------------------------------------------------------------------------
Module: AE::Physics2d

Class: PhysicsManager

Description: 2d physics manager, used to create and retain instances of 
2d physical objects
-----------------------------------------------------------------------------
*/

#ifndef __AE_PHYSICS2D_MANAGER__
#define __AE_PHYSICS2D_MANAGER__

#include "AnimaMathVector2.h"

namespace AE
{
	namespace Physics2d
	{
		struct Limit
		{
			AE::Vector2 position;
			//AE::Vector3 plane;

			Limit()
			{
				position = AE::Vector2::ZERO;
				plane = AE::Vector2::ZERO;
			}
		};

		struct RotationLimits
		{
			bool			enabled;
			Limit			high;
			Limit			low;
			AE::Vector2		offset;

			RotationLimits()
				: offset(0.0f, 0.0f) { }
		};

		struct TranslationLimits
		{
			bool	enabled;
			Limit	high;
			Limit	low;
		};

		struct JointDesc
		{
			AE::Vector2					anchor;
			AE::Vector2					axes[2];
			std::string					child;
			AE::Physics::jointType		jointType;
			std::string					parent;
			RotationLimits				rotationLimits;
			TranslationLimits			translationLimits;

			JointDesc()
			{
				anchor = AE::Vector2::ZERO;
				axes[0] = axes[1] = AE::Vector2::ZERO;
				child = "";
				jointType = AE::Physics::JT_FIXED;
				parent = "";
				rotationLimits.enabled = false;
				translationLimits.enabled = false;
			}

			~JointDesc() { }
		};

		class Manager
		{
		public:
												Manager() {  }
			virtual								~Manager() {  }

			virtual AE::Physics2d::Body*		createBody(const AE::Physics2d::BodyDesc &bodyDesc) = 0;
			virtual AE::Physics2d::Dynamic*		createDynamicBody(AE::Entity::SpriteDesc &spriteDesc, const AE::Physics2d::BodyDesc &bodyDesc) = 0;
			virtual void						createJoint(const JointDesc &jointDesc) = 0;
			virtual AE::Physics2d::Kinematic*	createKinematicBody(AE::Entity::SpriteDesc &spriteDesc, const AE::Physics2d::BodyDesc &bodyDesc) = 0;
			virtual AE::Physics2d::Material*	createMaterial(const AE::Physics::MaterialDesc &material) = 0;
			virtual AE::Physics2d::Static*		createStaticBody(AE::Entity::SpriteDesc &spriteDesc, const AE::Physics2d::BodyDesc &bodyDesc) = 0;
			virtual AE::Physics2d::Trigger*		createTrigger(AE::Entity::SpriteDesc &spriteDesc, const AE::Physics2d::BodyDesc &bodyDesc) = 0;
			virtual AE::Physics2d::World*		createWorld(const std::string &name, const AE::Math::Vector2 &gravity) = 0;
			virtual void						destroyBody(AE::Physics2d::Body *body) = 0;
			virtual void						destroyDynamicBody(AE::Physics2d::Dynamic *dynamic) = 0;
			virtual void						destroyKinematicBody(AE::Physics2d::Kinematic *kinematic) = 0;
			virtual void						destroyStaticBody(AE::Physics2d::Static *staticEntity) = 0;
			virtual AE::Physics2d::Body*		getBody(const std::string &name) = 0;
			virtual AE::Physics2d::Material*	getDefaultMaterial() = 0;
			virtual AE::Real					getDistanceFromClosestObject(AE::Vector2 position, AE::Vector3 direction, AE::Real rayDistance = 3000.0) = 0;
			virtual AE::Physics2d::Material*	getMaterial(const std::string &name) = 0;
			virtual void						initialize(AE::Framework *framework) = 0;
			virtual bool						isPointInCircle(const AE::Vector3 &sphereCenter, AE::Real sphereRadius, const AE::Vector3 &point) = 0;
			virtual AE::uint32					raycastClosestObject(AE::Vector3 position, AE::Vector3 direction, AE::Real rayDistance = 3000.0) = 0;
			virtual void						setCollisionPairFlags(AE::Physics2d::Body *body1, AE::Physics2d::Body *body2, AE::uint32 collisionNotify) = 0;
			virtual void						setGravity(AE::Real gravity) = 0;
			virtual void						setBodyGroup(AE::Physics2d::Body *body, AE::uint16 group) = 0;
			virtual void						stepSimulation(AE::Real dt) = 0;
		};
	}
}

#endif