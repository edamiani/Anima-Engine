#ifndef __AE_SCENE_X3D__VERTEX_ATTRIBUTE_NODE__
#define __AE_SCENE_X3D__VERTEX_ATTRIBUTE_NODE__

#include "AnimaSceneX3D_GeometricPropertyNode.h"

namespace AE
{
	namespace Scene
	{
		namespace X3D
		{
			class _VertexAttributeNode : public _GeometricPropertyNode
			{
			public:
				_VertexAttributeNode() {}
				virtual ~_VertexAttributeNode() {}

			protected:
				std::string mName;
			};
		}
	}
}

#endif