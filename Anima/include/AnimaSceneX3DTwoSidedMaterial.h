#ifndef __AE_SCENE_X3D_TWO_SIDED_MATERIAL__
#define __AE_SCENE_X3D_TWO_SIDED_MATERIAL__

#include "AnimaSceneX3D_MaterialNode.h"

namespace AE
{
	namespace Scene
	{
		namespace X3D
		{
			class TwoSidedMaterial : public AE::Scene::X3D::_MaterialNode
			{
			public:
				TwoSidedMaterial() 
					: mAmbientIntensity(0.2), mBackAmbientIntensity(0.2), mBackDiffuseColor(0.8, 0.8, 0.8), 
					  mBackEmissiveColor(0, 0, 0), mBackShininess(0.2), mBackSpecularColor(0, 0, 0), 
					  mBackTransparency(0), mDiffuseColor(0.8, 0.8, 0.8), mEmissiveColor(0, 0, 0), 
					  mSeparateBackColor(false), mShininess(0.2), mSpecularColor(0, 0, 0), mTransparency(0) {}
				virtual ~TwoSidedMaterial() {}

				AE::Real getAmbientIntensity() { return mAmbientIntensity; }
				AE::Real getBackAmbientIntensity() { return mBackAmbientIntensity; }
				AE::Graphics::Color& getBackDiffuseColor() { return mBackDiffuseColor; }
				AE::Graphics::Color& getBackEmissiveColor() { return mBackEmissiveColor; }
				AE::Real getBackShininess() { return mBackShininess; }
				AE::Graphics::Color& getBackSpecularColor() { return mBackSpecularColor; }
				AE::Real getBackTransparency() { return mBackTransparency; }	
				AE::Graphics::Color& getDiffuseColor() { return mDiffuseColor; }
				AE::Graphics::Color& getEmissiveColor() { return mEmissiveColor; }
				AE::Real getShininess() { return mShininess; }
				AE::Graphics::Color& getSpecularColor() { return mSpecularColor; }
				AE::Real getTransparency() { return mTransparency; }
				bool getUseSeparateBackColor() { return mUseSeparateBackColor; }
				void setAmbientIntensity(AE::Real ambientIntensity) { mAmbientIntensity = ambientIntensity; }
				void setBackAmbientIntensity(AE::Real backAmbientIntensity) { mBackAmbientIntensity = ambientIntensity; }
				void setBackDiffuseColor(AE::Graphics::Color &backDiffuseColor) { mBackDiffuseColor = backDiffuseColor; }
				void setBackEmissiveColor(AE::Graphics::Color &backEmissiveColor) { mBackEmissiveColor = backEmissiveColor; }
				void setBackShininess(AE::Real backShininess) { mBackShininess = backShininess; }
				void setBackSpecularColor(AE::Graphics::Color &backSpecularColor) { mBackSpecularColor = backSpecularColor; }
				void setBackTransparency(AE::Real backTransparency) { mBackTransparency = backTransparency; }
				void setDiffuseColor(AE::Graphics::Color &diffuseColor) { mDiffuseColor = diffuseColor; }
				void setEmissiveColor(AE::Graphics::Color &emissiveColor) { mEmissiveColor = emissiveColor; }
				void setShininess(AE::Real shininess) { mShininess = shininess; }
				void setSpecularColor(AE::Graphics::Color &specularColor) { mSpecularColor = specularColor; }
				void setTransparency(AE::Real transparency) { mTransparency = transparency; }
				void setUseSeparateBackColor(bool useSeparateBackColor) { mUseSeparateBackColor = useSeparateBackColor; }

			protected:
				AE::Real	mAmbientIntensity;
				AE::Real	mBackAmbientIntensity;
				AE::Graphics::Color mBackDiffuseColor;
				AE::Graphics::Color mBackEmissiveColor;
				AE::Real mBackShininess;
				AE::Graphics::Color mBackSpecularColor;
				AE::Real mBackTransparency;
				AE::Graphics::Color mDiffuseColor;
				AE::Graphics::Color mEmissiveColor;
				AE::Real mShininess;
				AE::Graphics::Color mSpecularColor;
				AE::Real mTransparency;
				bool	mUseSeparateBackColor;
			};
		}
	}
}

#endif