#ifndef __AE_EXCEPTION__
#define __AE_EXCEPTION__

#include "Anima/Types.h"

#include <string>

namespace AE
{
	enum ExceptionType
	{
		ET_ALREADY_EXISTS,
		ET_INVALID_MEMORY_ADDRESS,
		ET_FILE_NOT_FOUND,
		ET_NOT_FOUND,
		ET_NOT_RELATED,
		ET_NOT_SUPPORTED,
		ET_OUT_OF_RANGE
	};

	class Exception
	{
	public:
		Exception(AE::ExceptionType type, const std::string &message) : mType(type), mMessage(message) {}
		~Exception() {}

		std::string& getMessage() { return mMessage; }
		AE::ExceptionType getType() { return mType; }

	protected:
		std::string mMessage;
		AE::ExceptionType mType;
	};
}

#endif