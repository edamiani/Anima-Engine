#ifndef __AE_INPUT_KEY_INFO__
#define __AE_INPUT_KEY_INFO__

#include "AnimaInputEnums.h"

namespace AE
{
	namespace Input
	{
		struct KeyInfo
		{
			KeyInfo(AE::Input::KeyValue kv) : keyValue(kv) {}
			virtual ~KeyInfo() {}

			AE::Input::KeyValue keyValue;
		};
	}
}

#endif