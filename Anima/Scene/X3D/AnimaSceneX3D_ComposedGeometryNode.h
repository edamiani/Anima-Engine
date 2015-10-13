#ifndef __AE_SCENE_X3D__COMPOSED_GEOMETRY_NODE__
#define __AE_SCENE_X3D__COMPOSED_GEOMETRY_NODE__

#include "AnimaSceneX3D_GeometryNode.h"

namespace AE
{
	namespace Scene
	{
		namespace X3D
		{
			class _ComposedGeometryNode : public AE::Scene::X3D::_GeometryNode
			{
			public:
				_ComposedGeometryNode() {}
				virtual ~_ComposedGeometryNode() {}

				_ColorNode* getColorList();
				_CoordinateNode* getCoordinateList();
				_TextureCoordinateNode* getTextureCoordinateList();
				_NormalNode* getNormalList();
				bool hasColorPerVertex();
				bool hasNormalPerVertex();
				bool isCCW();
				bool isSolid();
				void setColor(_ColorNode *node);
				void setColor(_ProtoInstance *comp);
				void setCoord(_CoordinateNode *node);
				void setCoord(_ProtoInstance *node);
				void setNormal(_NormalNode *node);
				void setNormal(_ProtoInstance *node);
				void setTexCoord(_TextureCoordinateNode *node);
				void setTexCoord(_ProtoInstance *node);
				void setCCW(bool CCW);
				void setColorPerVertex(bool perVertex);
				void setNormalPerVertex(bool perVertex);
				void setSolid(bool solid);

			protected:
				bool mCCW;
				bool mColorPerVertex;
				bool mNormalPerVertex;
				bool mSolid;
			};
		}
	}
}

#endif