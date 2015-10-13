#ifndef __AE_PHYSICS2D_MATERIAL__
#define __AE_PHYSICS2D_MATERIAL__

#include "AnimaPhysics2dMaterialDesc.h"

namespace AE
{
	namespace Physics2d
	{
		class Material
		{
		public:
									Material(const MaterialDesc &material) {  }
			virtual					~Material() {  }

			virtual AE::Real		getDynamicFriction() = 0 ;
			virtual AE::uint16		getIndex() = 0 ;
			virtual std::string		getName() = 0 ;
			virtual AE::Real		getRestitution() = 0 ;
			virtual AE::Real		getStaticFriction() = 0 ;
			virtual void			setDynamicFriction(AE::Real dynamicFriction) = 0;
			virtual void			setIndex(AE::uint16 index) = 0;
			virtual void			setName(const std::string &name) = 0;
			virtual void			setRestitution(AE::Real restitution) = 0;
			virtual void			setStaticFriction(AE::Real staticFriction) = 0;
		};
	}
}

#endif