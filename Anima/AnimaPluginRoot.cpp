#include "Anima/PluginRoot.h"
#include "Anima/PluginManager.h"

#include "Anima/Exception.h"

namespace AE
{
	PluginRoot::PluginRoot()
		: PluginGroup(AE::PT_ROOT)
	{
	}

	PluginRoot::~PluginRoot()
	{
		/*std::list<AE::Plugin *>::iterator i;
		for(i = mChildren.begin(); i != mChildren.end(); i++)
		{
			if((*i)->isInstalled())
				(*i)->uninstall();

			delete (*i);
		}*/
	}

	AE::Plugin* PluginRoot::attach(AE::Plugin *pluginToAttach)
	{
		pluginToAttach->setParent(this);

		mChildren.push_back(pluginToAttach);

		return pluginToAttach;
	}

	AE::Plugin* PluginRoot::attachAndInstall(AE::Plugin *pluginToAttach, AE::uint installOptions)
	{
		pluginToAttach->setParent(this);

		mChildren.push_back(pluginToAttach);

		pluginToAttach->install(installOptions);

		return pluginToAttach;
	}

	void PluginRoot::detach(const std::string &pluginName)
	{
		AE::Plugin *plugin = AE::PluginManager::getInstance()->find(pluginName);

		if(!plugin)
			throw AE::Exception(AE::ET_NOT_FOUND, "AE::PluginRoot::detach(): there is no plugin with this name attached as a root's child.");

		if(plugin->isInstalled())
			plugin->uninstall();

		mChildren.remove(plugin);
	}
}
