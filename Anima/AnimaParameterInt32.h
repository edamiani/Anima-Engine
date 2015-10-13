#ifndef __AE_PARAMETER_INT32__
#define __AE_PARAMETER_INT32__

#include "AnimaParameter.h"

namespace AE
{
	enum ParameterType
	{
		PT_INT32
	};

	class ParameterInt32 : public AE::Parameter
	{
	public:
		ParameterInt32(AE::uint name, AE::int32 value)
			: Parameter(AE::PT_INT32, name), mValue(value) {}

		~ParameterInt32() {}

		int getValue() { return mValue; }

	protected:
		int mValue;
	};
}

#endif