#ifndef __AE_PHYSICS2D_MATERIAL_DESC__
#define __AE_PHYSICS2D_MATERIAL_DESC__

namespace AE
{
	namespace Physics2d
	{
		struct MaterialDesc
		{
			AE::Real		dynamicFriction;
			std::string		name;
			AE::Real		restitution;
			AE::Real		staticFriction;
		};
	}
}

#endif