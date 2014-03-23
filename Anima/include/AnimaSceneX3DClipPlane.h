#ifndef __AE_SCENE_X3D_CLIP_PLANE__
#define __AE_SCENE_X3D_CLIP_PLANE__

#include "AnimaSceneX3D_ChildNode.h"
#include "AnimaMathVector4.h"

namespace AE
{
	namespace Scene
	{
		namespace X3D
		{
			class ClipPlane : public _ChildNode
			{
			public:
				ClipPlane() : enabled(false)
				{ 
					mPlane.x = 0; 
					mPlane.y = 0; 
					mPlane.z = 0; 
					mPlane.w = 0; 
				}

				ClipPlane(Vector4 &plane) : enabled(false)
				{ 
					mPlane = plane; 
				}

				~ClipPlane() {}

				Vector4& getPlane() { return mPlane; }
				bool isEnabled() { return mEnabled; }
				void setEnabled (bool enabled) { mEnabled = enabled; }
				void setPlane(AE::Math::Vector4 &plane) { mPlane = plane; }

			protected:
				bool mEnabled;
				AE::Math::Vector4 mPlane;
			};
		}
	}
}

#endif