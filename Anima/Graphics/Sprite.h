#ifndef __ANIMA_GRAPHICS_SPRITE__
#define __ANIMA_GRAPHICS_SPRITE__

#include "Anima/Prerequisites.h"
#include "Anima/Math/Math.h"
#include "Anima/Math/Quaternion.h"

namespace AE
{
	namespace Graphics
	{
		enum AnimationBlendMode
		{
			ANIMBLEND_AVERAGE,
			ANIMBLEND_CUMULATIVE
		};

		enum PrefabType
		{
			PF_NONE,
			PF_CUBE
		};

		struct SpriteDesc
		{
		public:
			std::string					initialAnimation;
			bool						isVisible;
			std::string					mesh;
			std::string					name;
			//AE::Scene::Node*			node;
			AE::Math::Quaternion		orientation;
			AE::Math::Vector3			position;
			AE::Graphics::PrefabType	prefabType;
			AE::Math::Vector3			scale;
			bool						shadowCaster;
			
			SpriteDesc()
			{
				initialAnimation = "";
				isVisible = true;
				mesh = "";
				name = "";
				//node = 0;
				orientation = AE::Math::Quaternion::IDENTITY;
				position = AE::Math::Vector3::ZERO;
				prefabType = AE::Graphics::PF_NONE;
				scale = AE::Math::Vector3::UNIT_SCALE;
				shadowCaster = false;
			}

			~SpriteDesc() { }
		};

		class Sprite
		{
		public:
			Sprite() { }
			virtual ~Sprite() { }

			//TR::AxisAlignedBox& getBoundingBox() { return mBoundingBox; }
			//TR::Real getBoundingRadius() { return mBoundingRadius; }
			AE::Math::Quaternion&	getOrientation() { return mOrientation; }
			AE::Math::Vector3&		getPosition() { return mPosition; }
			const					std::string& getName() { return mName; }
			void					setName(const std::string& name) { mName = name; }
			void					setVisible(bool isVisible) { mIsVisible = isVisible; }
			virtual void			setOrientation(AE::Math::Quaternion orientation) = 0;
			virtual void			setOrientation(AE::Real x, AE::Real y, AE::Real z, AE::Real w) = 0;
			virtual void			setPosition(AE::Math::Vector3 position) = 0;
			virtual void			setPosition(AE::Real x, AE::Real y, AE::Real z) = 0;

		protected:
			//TR::AxisAlignedBox		mBoundingBox;
			//TR::Real				mBoundingRadius;
			bool					mIsVisible;
			std::string				mName;
			AE::Math::Quaternion	mOrientation;
			AE::Math::Vector3		mPosition;
		};
	}
}


#endif