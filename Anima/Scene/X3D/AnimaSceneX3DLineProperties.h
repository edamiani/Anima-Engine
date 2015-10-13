#ifndef __AE_SCENE_X3D_LINE_PROPERTIES__
#define __AE_SCENE_X3D_LINE_PROPERTIES__

#include "AnimaSceneX3D_AppearanceChildNode.h"

namespace AE
{
	namespace Scene
	{
		namespace X3D
		{
			class LineProperties : public AE::Scene::X3D::_AppearanceChildNode
			{
			public:
				LineProperties() 
					: mApplied(true), mLineType(1), mLineWidthScaleFactor(0) {}
				virtual ~LineProperties() {}

				bool getApplied() { return mApplied; }
				AE::int32 getLineType() { return mLineType; }
				AE::Real getLineWidthScaleFactor() { return mLineWidthScaleFactor; }
				void setApplied(bool isApplied) { mApplied = isApplied; }
				void setLineType(AE::int32 lineType) { mLineType = lineType; }
				void setLineWidthScaleFactor(AE::Real lineWidthScaleFactor) { mLineWidthScaleFactor = lineWidthScaleFactor; }

			protected:
				bool	mApplied;
				AE::int32 mLineType;
				AE::Real mLineWidthScaleFactor;
			};
		}
	}
}

#endif