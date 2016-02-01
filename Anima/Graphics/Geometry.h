#ifndef __ANIMA_GRAPHICS_GEOMETRY__
#define __ANIMA_GRAPHICS_GEOMETRY__

#include "Anima/Graphics/Enums.h"

namespace AE
{
	namespace Graphics
	{
		class Mesh;

		class Geometry
		{
		public:
			Geometry(AE::Graphics::GeometryType type) 
				: mType(type), mMesh(0) { }
			virtual ~Geometry() { }

			AE::Graphics::GeometryType getType() { return mType; }

		protected:
			AE::Graphics::GeometryType mType;
			AE::Graphics::Mesh *mMesh;
		};
	}
}


#endif