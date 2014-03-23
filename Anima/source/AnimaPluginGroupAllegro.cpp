#include "../include/AnimaPluginGroupAllegro.h"

#include "../include/AnimaException.h"
#include "../include/AnimaGraphicsDeviceManagerAllegro.h"
#include "../include/AnimaOSWindowManagerAllegro.h"
#include "../include/AnimaPluginManager.h"

#include <cassert>

namespace AE
{
	PluginGroupAllegro::PluginGroupAllegro() 
	{
		al_init();
	}

	PluginGroupAllegro::~PluginGroupAllegro()
	{
		std::map<std::string, AE::Plugin *>::iterator i;

		for(i = mChildPlugins.begin(); i != mChildPlugins.end(); i++)
		{
			if((*i).second->isInstalled())
				(*i).second->uninstall();

			delete (*i).second;
		}

		al_uninstall_system();
	}

	AE::Plugin* PluginGroupAllegro::createPlugin(const std::string &pluginName, AE::PluginType pluginType)
	{
		AE::Plugin *pluginToAttach;
		switch(pluginType)
		{
		case(AE::PT_OS_WINDOW_MANAGER):
			pluginToAttach = new AE::OS::WindowManagerAllegro();
			break;
		case(AE::PT_GRAPHICS_DEVICE_MANAGER):
			pluginToAttach = new AE::Graphics::Device::ManagerAllegro();
			break;
		default:
			throw AE::Exception(AE::ET_NOT_FOUND, "AE::PluginGroup::attach(): This group cannot register this type of plugin.");
		}

		pluginToAttach->setParent(this);

		if(!AE::PluginManager::getInstance()->registerPlugin(pluginName, pluginToAttach))
			throw AE::Exception(AE::ET_ALREADY_EXISTS, "AE::PluginGroup::createPlugin(): A plugin with this name already exists in this group.");

		mChildPlugins[pluginName] = pluginToAttach;

		return pluginToAttach;
	}

	void PluginGroupAllegro::destroyPlugin(const std::string &pluginName)
	{
		std::map<std::string, AE::Plugin *>::iterator i = mChildPlugins.find(pluginName);

		if(i == mChildPlugins.end())
			throw AE::Exception(AE::ET_NOT_FOUND, "AE::PluginGroupAllegro::destroyPlugin(): there is no plugin with this name attached as a child of this group.");

		if((*i).second->isInstalled())
			(*i).second->uninstall();

		delete (*i).second;

		mChildPlugins.erase(i);

		AE::PluginManager::getInstance()->unregisterPlugin(pluginName);
	}
}