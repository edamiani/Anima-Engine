#ifndef __AE_GRAPHICS_PRIMITIVE_FACTORY__
#define __AE_GRAPHICS_PRIMITIVE_FACTORY__

#include "../Math/AnimaMathVector3.h"

#include <cassert>

namespace AE
{
	namespace Graphics
	{
		class Manager;
		class Mesh;

		class PrimitiveFactory
		{
		public:
			~PrimitiveFactory() { mGraphicsManager = 0; }

			static AE::Graphics::PrimitiveFactory*	getInstance() { assert(mInstance); return mInstance; }
			static AE::Graphics::PrimitiveFactory*	initialize();
			static void						shutdown();

			AE::Graphics::Mesh*				createCube(AE::Math::Vector3 &position, AE::Math::Vector3 &size);
			AE::Graphics::Mesh*				createCone(AE::Math::Vector3 &position, AE::Math::Vector3 &size, AE::Real bottomRadius, AE::Real height, bool drawSide = true, bool drawBottom = true, bool doubleSided = false);
			AE::Graphics::Mesh*				createGrid(int m, int n, float gridSize);
			AE::Graphics::Mesh*				createSphere(AE::Math::Vector3 &position, AE::Math::Vector3 &size);
		
		protected:
			PrimitiveFactory();

			void							_createBottomlessInnerConeMesh();
			void							_createBottomlessOuterConeMesh();
			void							_createCubeMesh();
			void							_createOneSidedLowerDiscMesh();
			void							_createOneSidedUpperDiscMesh();
			void							_createOpenInnerCylinderMesh();
			void							_createOpenOuterCylinderMesh();
			void							_createSphereMesh();

			AE::Graphics::Manager *mGraphicsManager;
			static AE::Graphics::PrimitiveFactory *mInstance;
		};
	}
}

#endif