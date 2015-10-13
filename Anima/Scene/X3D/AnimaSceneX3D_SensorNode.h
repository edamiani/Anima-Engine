#ifndef __AE_SCENE_X3D__SENSOR_NODE__
#define __AE_SCENE_X3D__SENSOR_NODE__

#include "AnimaSceneX3D_ChildNode.h"

namespace AE
{
	namespace Scene
	{
		namespace X3D
		{
			class _SensorNode : public AE::Scene::X3D::_ChildNode
			{
			public:
				_SensorNode() {}
				virtual ~_SensorNode() {}

				virtual void setEnabled(bool enabled) { mEnabled = enabled; }
				virtual bool getEnabled() { return mEnabled; }
				virtual bool isActive() { return true; }

			protected:
				bool mEnabled;
			};
		}
	}
}

#endif