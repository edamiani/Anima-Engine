#include "../include/AnimaPlugin.h"

namespace AE
{
	Plugin::Plugin(AE::PluginType pluginType)
		: mPluginType(pluginType), mIsAttached(false), mIsInstalled(false), mParent(0)
	{
	}

	Plugin::~Plugin()
	{
		if(mParent)
			mParent = 0;
	}
}
