#ifndef __AE_PLUGIN_GROUP__
#define __AE_PLUGIN_GROUP__

#include "AnimaPlugin.h"

#include <list>

namespace AE
{	
	class PluginGroup : public AE::Plugin
	{
	public:
		PluginGroup();
		PluginGroup(AE::PluginType pluginType);
		virtual ~PluginGroup();

		AE::Plugin*			attach(AE::Plugin *pluginToAttach);
		AE::Plugin*			attachAndInstall(AE::Plugin *pluginToAttach, AE::uint installOptions);
		void				detach(std::string const &pluginName);
		void				detach(AE::Plugin *child);
		void				detachAndUninstall(std::string const &pluginName);
		void				detachAndUninstall(AE::Plugin *child);
		AE::Plugin*			getChildByType(AE::PluginType pluginType);
		virtual bool		install(AE::uint options);
		virtual bool		uninstall();

	protected:
		std::list<AE::Plugin *> mChildren;
	};
}

#endif