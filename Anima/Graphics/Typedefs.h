#ifndef __AE_GRAPHICS_TYPEDEFS__
#define __AE_GRAPHICS_TYPEDEFS__

#include <deque>

#include "Anima/Math/Vector3.h"

namespace AE
{
	namespace Graphics
	{
		typedef std::deque<int> Indices;
		typedef std::deque<AE::Math::Vector3> Points;
	}
}

#endif