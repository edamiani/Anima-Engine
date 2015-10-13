#ifndef __AE_SCENE_X3D_MATERIAL__
#define __AE_SCENE_X3D_MATERIAL__

#include "AnimaGraphicsColor.h"
#include "AnimaSceneX3D_MaterialNode.h"

namespace AE
{
	namespace Scene
	{
		namespace X3D
		{
			class Material : public AE::Scene::X3D::_MaterialNode
			{
			public:
				Material() 
					: mAmbientIntensity(0.2), mDiffuseColor(0.8, 0.8, 0.8), mEmissiveColor(0, 0, 0),
					  mShininess(0.2), mSpecularColor(0, 0, 0), mTransparency(0) {}
				virtual ~_Material() {}

				AE::Real getAmbientIntensity() { return mAmbientIntensity; }
				AE::Graphics::Color& getDiffuseColor() { return mDiffuseColor; }
				AE::Graphics::Color& getEmissiveColor() { return mEmissiveColor; }
				AE::Real getShininess() { return mShininess; }
				AE::Graphics::Color& getSpecularColor() { return mSpecularColor; }
				AE::Real getTransparency() { return mTransparency; }				
				void setAmbientIntensity(AE::Real ambientIntensity) { mAmbientIntensity = ambientIntensity; }
				void setDiffuseColor(AE::Graphics::Color &diffuseColor) { mDiffuseColor = diffuseColor; }
				void setEmissiveColor(AE::Graphics::Color &emissiveColor) { mEmissiveColor = emissiveColor; }
				void setShininess(AE::Real shininess) { mShininess = shininess; }
				void setSpecularColor(AE::Graphics::Color &specularColor) { mSpecularColor = specularColor; }
				void setTransparency(AE::Real transparency) { mTransparency = transparency; }

			protected:
				AE::Real mAmbientIntensity;
				AE::Graphics::Color mDiffuseColor;
				AE::Graphics::Color mEmissiveColor;
				AE::Real mShininess;
				AE::Graphics::Color mSpecularColor;
				AE::Real mTransparency;
			};
		}
	}
}

#endif