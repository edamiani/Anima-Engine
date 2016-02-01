#ifndef __AE_GRAPHICS_COLOR__
#define __AE_GRAPHICS_COLOR__

#include "Anima/Types.h"

namespace AE
{
	namespace Graphics
	{
		struct Color
		{
			Color() : R(0), G(0), B(0), A(255) { }
			Color(AE::uint8 red, AE::uint8 green, AE::uint8 blue, AE::uint8 alpha = 255)
				: R(red), G(green), B(blue), A(alpha) { }

			bool operator == (const AE::Graphics::Color &color)
			{
				return(R == color.R && G == color.G && B == color.B && A == color.A);
			}

			AE::uint32 get32Bit() 
			{
				return ((A << 24) + (R << 16) + (G << 8) + B);
			}

			AE::uint32 getARGB()
			{
				return ((A << 24) + (R << 16) + (G << 8) + B);
			}

			AE::uint32 getRGBA()
			{
				return ((R << 24) + (G << 16) + (B << 8) + A);
			}

			AE::uint8 R;
			AE::uint8 G;
			AE::uint8 B;
			AE::uint8 A;
		};
	}
}

#endif