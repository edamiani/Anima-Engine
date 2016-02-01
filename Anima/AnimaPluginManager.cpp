#include "Anima/PluginManager.h"

#include "Anima/Exception.h"
#include "Anima/PluginRoot.h"

AE::PluginManager* AE::PluginManager::mInstance = 0;

namespace AE
{
	PluginManager::PluginManager()
	{
		mRoot = new AE::PluginGroup(AE::PT_ROOT);
	}

	PluginManager::~PluginManager()
	{
		delete mRoot;
	}

	AE::PluginManager* PluginManager::initialize()
	{
		if(!mInstance)
			mInstance = new AE::PluginManager();

		return mInstance;
	}

	void PluginManager::shutdown()
	{
		if(mInstance)
		{
			delete mInstance;
			mInstance = 0;
		}
	}

	AE::Plugin* PluginManager::find(const std::string &pluginName) 
	{
		std::map<std::string, AE::Plugin *>::iterator i = mRegisteredPlugins.find(pluginName);

		if(i == mRegisteredPlugins.end())
			return 0;
		else
			return (*i).second;
	}

	AE::Plugin* PluginManager::getInstalledPluginByType(AE::PluginType pluginType)
	{
		assert(pluginType != AE::PT_ALL && pluginType != AE::PT_GROUP && pluginType != AE::PT_IRRELEVANT && pluginType != AE::PT_ROOT);

		std::map<std::string, AE::Plugin *>::iterator i;

		for(i = mRegisteredPlugins.begin(); i != mRegisteredPlugins.end(); i++)
		{
			if((*i).second->getType() == pluginType && (*i).second->isInstalled())
				return (*i).second;
		}

		return 0;
	}

	AE::Plugin* PluginManager::getPluginByName(const std::string &pluginName)
	{
		if(mRegisteredPlugins.find(pluginName) != mRegisteredPlugins.end())
			return 0;

		return mRegisteredPlugins[pluginName];
	}

	AE::Plugin* PluginManager::registerPlugin(const std::string &pluginName, AE::Plugin *plugin)
	{
		if(mRegisteredPlugins.find(pluginName) != mRegisteredPlugins.end())
			return 0;

		mRegisteredPlugins[pluginName] = plugin;

		return plugin;
	}

	void PluginManager::unregisterPlugin(const std::string &pluginName)
	{
		std::map<std::string, AE::Plugin *>::iterator i = mRegisteredPlugins.find(pluginName);

		if(i == mRegisteredPlugins.end())
			throw AE::Exception(AE::ET_NOT_FOUND, "AE::PluginManager::unregisterPlugin(): there is no plugin registered with this name.");

		if((*i).second->isInstalled())
			(*i).second->uninstall();

		mRegisteredPlugins.erase(i);
	}
}
