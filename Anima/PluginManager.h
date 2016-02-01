#ifndef __AE_PLUGIN_MANAGER__
#define __AE_PLUGIN_MANAGER__

#include "Anima/Types.h"
#include "Anima/Plugin.h"
#include "Anima/PluginGroup.h"

#include <map>
#include <string>

namespace AE
{
	class PluginManager
	{
	public:
		~PluginManager();

		static AE::PluginManager*		getInstance() { assert(mInstance != 0); return mInstance; }
		static AE::PluginManager*		initialize();
		static void						shutdown();

		AE::Plugin*						find(const std::string &pluginName);
		AE::Plugin*						getInstalledPluginByType(AE::PluginType pluginType);
		AE::Plugin*						getPluginByName(const std::string &pluginName);
		AE::PluginGroup*				getRoot() { return mRoot; }
		AE::Plugin*						registerPlugin(const std::string &pluginName, AE::Plugin *plugin);
		void							unregisterPlugin(const std::string &pluginName);

	protected:
		PluginManager();

		static AE::PluginManager		*mInstance;

		std::map<std::string, AE::Plugin *> 
										mRegisteredPlugins;
		AE::PluginGroup					*mRoot;
	};
}

#endif
