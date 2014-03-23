#ifndef __AE_PARAMETER__
#define __AE_PARAMETER__

namespace AE
{
	class Parameter
	{
	public:
		Parameter(AE::uint type, AE::uint name) : mType(type), mName(name) {}
		~Parameter() {}

		AE::uint getName() { return mName; }
		AE::uint getType() { return mType; }

	protected:
		AE::uint mName;
		AE::uint mType;
	};
}

#endif