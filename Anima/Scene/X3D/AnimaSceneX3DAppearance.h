#ifndef __AE_SCENE_X3D_APPEARANCE__
#define __AE_SCENE_X3D_APPEARANCE__

#include "AnimaSceneX3D_AppearanceNode.h"
#include "AnimaSceneX3D_FillProperties.h"
#include "AnimaSceneX3D_LineProperties.h"
#include "AnimaSceneX3D_MaterialNode.h"
#include "AnimaSceneX3D_ShaderNode.h"
#include "AnimaSceneX3D_TextureNode.h"
#include "AnimaSceneX3D_TextureTransformNode.h"

#include <vector>

namespace AE
{
	namespace Scene
	{
		namespace X3D
		{
			class Appearance : public _AppearanceNode
			{
			public:
				Appearance() 
					: mFillProperties(0), mLineProperties(0), mMaterial(0), mTexture(0), mTextureTransform(0) {}
				virtual ~Appearance() {}

			protected:
				_FillProperties *mFillProperties;
				_LineProperties *mLineProperties;
				_MaterialNode *mMaterial;
				std::vector<_ShaderNode *> mShaders;
				_TextureNode *mTexture;
				_TextureTransformNode *mTextureTransform;
			};
		}
	}
}

#endif