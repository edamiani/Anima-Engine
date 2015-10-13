#ifndef __AE_SCENE_X3D__SHADER_NODE__
#define __AE_SCENE_X3D__SHADER_NODE__

#include "AnimaSceneX3D_AppearanceNode.h"

namespace AE
{
	namespace Scene
	{
		namespace X3D
		{
			class _ShaderNode : public _AppearanceNode
			{
			public:
				_ShaderNode() : mActivate(false), mIsSelected(false), mIsValid(false) {}
				virtual ~_ShaderNode() {}

				SFBool activate(SFBool activate) { mActivate = activate; }
				SFBool getIsSelected() { return mIsSelected; }
				SFBool getIsValid() { return mIsValid; }
				void setIsSelected(SFBool isSelected) { mIsSelected = isSelected; }
				void setIsValid(SFBool isValid) { mIsValid = isValid; }

			protected:
				SFBool mActivate;
				SFBool mIsSelected;
				SFBool mIsValid;
				SFString mLanguage;
			};
		}
	}
}

#endif