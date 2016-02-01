#ifndef __AE_PLUGIN__
#define __AE_PLUGIN__

#include "Anima/Types.h"

#include <list>

namespace AE
{	
	enum PluginType
	{
		PT_ALL,

		PT_AI_MANAGER,
		PT_ANIMATION_MANAGER,
		PT_AUDIO_MANAGER,
		PT_DATABASE_MANAGER,
		PT_FONT_MANAGER,
		PT_GRAPHICS_MANAGER,
		PT_GRAPHICS_DEVICE_MANAGER,
		PT_GUI_MANAGER,
		PT_IMAGE_MANAGER,
		PT_INPUT_MANAGER,
		PT_MATH_MANAGER,
		PT_MUSIC_MANAGER,
		PT_NATURE_MANAGER,
		PT_NETWORK_MANAGER,
		PT_OS_MANAGER,
		PT_OS_TIMER_MANAGER,
		PT_OS_WINDOW_MANAGER,
		PT_PHYSICS_MANAGER,
		PT_SCENE_MANAGER,
		PT_SCRIPT_MANAGER,
		PT_XML_MANAGER,

		// Used internally
		PT_GROUP, 
		PT_IRRELEVANT,
		PT_ROOT
	};

	class Plugin
	{
	public:
		Plugin(AE::PluginType pluginType);
		virtual ~Plugin();

		AE::Plugin*		getParent() { return mParent; }
		AE::PluginType	getType() { return mPluginType; }
		virtual bool	install(AE::uint options) = 0;
		bool			isAttached() { return mIsAttached; }
		bool			isInstalled() { return mIsInstalled; }
		void			setParent(AE::Plugin *parent) { mParent = parent; }
		virtual bool	uninstall() = 0;

	protected:
		bool			mIsAttached;
		bool			mIsInstalled;
		AE::Plugin		*mParent;
		AE::PluginType	mPluginType;
	};
}

#endif