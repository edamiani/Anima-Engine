#ifndef __AE_PLUGIN_ROOT__
#define __AE_PLUGIN_ROOT__

#include "Anima/PluginGroup.h"

#include <map>

namespace AE
{	
	class PluginManager;

	class PluginRoot : public AE::PluginGroup
	{
	public:
		~PluginRoot();

		AE::Plugin* attach(AE::Plugin *pluginToAttach);
		AE::Plugin* attachAndInstall(AE::Plugin *pluginToAttach, AE::uint installOptions);
		void detach(const std::string &pluginName);

		friend class PluginManager;

	protected:
		PluginRoot();

		bool install(AE::uint options) { return true; }
		bool uninstall() { return true; }
	};
}

#endif