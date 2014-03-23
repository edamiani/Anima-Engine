#ifndef __AE_PLUGIN_GROUP_ALLEGRO__
#define __AE_PLUGIN_GROUP_ALLEGRO__

#include "AnimaPluginGroup.h"

#include "allegro5/allegro.h"

namespace AE
{	
	class PluginGroupAllegro : public AE::PluginGroup
	{
	public:
		PluginGroupAllegro();
		~PluginGroupAllegro();

		AE::Plugin* createPlugin(const std::string &pluginName, AE::PluginType pluginType);
		void destroyPlugin(const std::string &pluginName);
		//bool install(const std::string &pluginName, AE::uint options);
		//bool uninstall();

	protected:
	};
}

#endif