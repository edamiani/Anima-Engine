#ifndef __AE_OS_EVENT__
#define __AE_OS_EVENT__

#include "Anima/Input/AnimaInputKeyInfo.h"
#include "Anima/Math/Point2.h"
#include "Anima/Types.h"

#include <string>

namespace AE
{
	namespace OS
	{
		class Window;

		enum EventType
		{
			ET_JOYSTICK,
			ET_KEYBOARD,
			ET_MOUSE,
			ET_TIMER,
			ET_WINDOW
		};

		enum EventSubType
		{
			EST_JOYSTICK_AXIS,
			EST_JOYSTICK_BUTTON_DOWN,
			EST_JOYSTICK_BUTTON_UP,
			EST_JOYSTICK_CONFIGURATION,
			EST_KEY_DOWN,
			EST_KEY_TRANSLATION,
			EST_KEY_UP,
			EST_MOUSE_AXES,
			EST_MOUSE_BUTTON_DOWN,
			EST_MOUSE_BUTTON_UP,
			EST_MOUSE_ENTER_WINDOW,
			EST_MOUSE_LEAVE_WINDOW,
			EST_MOUSE_WARPED,
			EST_TIMER,
			EST_WINDOW_CLOSE,
			EST_WINDOW_DEVICE_FOUND,
			EST_WINDOW_DEVICE_LOST,
			EST_WINDOW_GAIN_FOCUS,
			EST_WINDOW_LOST_FOCUS,
			EST_WINDOW_ORIENTATION_CHANGED,
			EST_WINDOW_RESTORE,
			EST_WINDOW_RESIZE
		};

		struct Event
		{
			AE::OS::Window			*sourceWindow;
			AE::OS::EventSubType	subType;
			AE::OS::EventType		type;

			Event(AE::OS::EventType _type, AE::OS::EventSubType _subType, AE::OS::Window *_sourceWindow)
				: type(_type), subType(_subType), sourceWindow(_sourceWindow) {}
		};

		struct EventJoystick : public AE::OS::Event
		{
			AE::uint axisId;
			AE::uint id;
			AE::uint stickId;
			AE::Real position;

			EventJoystick(AE::OS::EventSubType _subType, AE::OS::Window *_sourceWindow)
				: Event(AE::OS::ET_JOYSTICK, _subType, _sourceWindow) {}
		};

		struct EventKeyboard : public AE::OS::Event
		{
			AE::Input::KeyInfo keyInfo;

			EventKeyboard(AE::OS::EventSubType _subType, AE::OS::Window *_sourceWindow, const AE::Input::KeyInfo &keyInfo)
				: Event(AE::OS::ET_KEYBOARD, _subType, _sourceWindow), keyInfo(keyInfo) {}
		};

		struct EventKeyTranslation : public AE::OS::Event
		{
			wchar_t character;

			EventKeyTranslation(AE::OS::Window *_sourceWindow, wchar_t _character)
				: Event(AE::OS::ET_KEYBOARD, AE::OS::EST_KEY_TRANSLATION, _sourceWindow), character(_character) {}
		};

		struct EventMouse : public AE::OS::Event
		{
			AE::uint16					buttonPressed;
			AE::Math::Point2<AE::int32>	offset;
			AE::Math::Point2<AE::int32>	position;

			EventMouse(AE::OS::EventSubType _subType, AE::OS::Window *_sourceWindow, AE::uint16 _buttonPressed, const AE::Math::Point2<AE::int32> &_offset)
				: Event(AE::OS::ET_MOUSE, _subType, _sourceWindow), buttonPressed(_buttonPressed), offset(_offset) {}
		};

		struct EventTimer : public AE::OS::Event
		{
			EventTimer(AE::OS::EventSubType _subType, AE::OS::Window *_sourceWindow)
				: Event(AE::OS::ET_TIMER, _subType, _sourceWindow) {}
		};

		struct EventWindow : public AE::OS::Event
		{
			EventWindow(AE::OS::EventSubType _subType, AE::OS::Window *_sourceWindow, AE::Math::Point2<AE::int32> *_topLeft = 0, AE::Math::Point2<AE::uint> *_dimensions = 0)
				: Event(AE::OS::ET_WINDOW, _subType, _sourceWindow)
			{
				if(_dimensions)
				{
					dimensions.x = _dimensions->x;
					dimensions.y = _dimensions->y;
					topLeft.x = _topLeft->x;
					topLeft.y = _topLeft->y;
				}
			}

			AE::Math::Point2<AE::uint> dimensions;
			AE::Math::Point2<AE::int32> topLeft;
		};
	}
}

#endif
