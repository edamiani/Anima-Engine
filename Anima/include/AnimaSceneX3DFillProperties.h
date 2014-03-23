#ifndef __AE_SCENE_X3D_FILL_PROPERTIES__
#define __AE_SCENE_X3D_FILL_PROPERTIES__

#include "AnimaGraphicsColor.h"
#include "AnimaSceneX3D_AppearanceChildNode.h"

namespace AE
{
	namespace Scene
	{
		namespace X3D
		{
			class FillProperties : public AE::Scene::X3D::_AppearanceChildNode
			{
			public:
				FillProperties() 
					: mHatchColor(255, 255, 255), mHatchStyle(1), mIsFilled(true), mIsHatched(true) {}
				virtual ~FillProperties() {}

				AE::Graphics::Color& getHatchColor() { return mHatchColor; }
				AE::int32 getHatchStyle() { return mHatchStyle; }
				bool getIsFilled() { return mIsFilled; }
				bool getIsHatched() { return mIsHatched; }
				void setHatchColor(AE::Graphics::Color &hatchColor) { mHatchColor = hatchColor; }
				void setHatchStyle(AE::int32 hatchStyle) { mHatchStyle = hatchStyle; }
				void setIsFilled(bool isFilled) { mIsFilled = isFilled; }
				void setIsHatched(bool isHatched) { mIsHatched = isHatched; }

			protected:
				AE::Graphics::Color	mHatchColor;
				AE::int32 mHatchStyle;
				bool mIsFilled;
				bool mIsHatched;
			};
		}
	}
}

#endif