#ifndef __AE_GRAPHICS_MANAGER_OGRE__
#define __AE_GRAPHICS_MANAGER_OGRE__

#include "AnimaGraphicsManager.h"

//#include "AnimaGraphicsMeshOgre.h"
//#include "AnimaMath.h"
//#include "AnimaOSWindowOgre.h"

namespace Ogre
{
	class Root;
	class Plugin;
}

namespace AE
{
	namespace Graphics
	{
		class ManagerOgre : public Manager
		{
		public:
			ManagerOgre(AE::uint graphicsManagerOptions = AE::Graphics::GMO_OPENGL);
			~ManagerOgre();

			//void					createCube(AE::Math::Vector3 &position, AE::Math::Vector3 &size);
			//void					createCone(AE::Math::Vector3 &position, AE::Math::Vector3 &size, AE::Real bottomRadius, AE::Real height, bool drawSide = true, bool drawBottom = true, bool doubleSided = false) {}
			//AE::Graphics::Font*		createFont(const std::string &fontFace, AE::Real size, AE::Graphics::FontType fontType = AE::Graphics::FT_TRUETYPE);
			//void					createGrid(int m, int n, float gridSize);
			//IndexBuffer*			createIndexBuffer(std::string &name, std::vector<AE::ushort> &indices, BufferUsage bufferUsage, bool useShadowBuffer);
			//Mesh*					createMesh(std::string &name, VertexBuffer *vertexBuffer, IndexBuffer *indexBuffer, RenderOperationType renderOperationType);
			//void					createSphere(AE::Math::Vector3 &position, AE::Math::Vector3 &size);
			//AE::Graphics::Sprite*	createSprite(AE::Graphics::SpriteDesc &spriteDesc);
			//VertexBuffer*			createVertexBuffer(std::string &name, VertexBufferDesc &vertexBufferDesc);
			//void					destroySprite(const std::string &name);
			//AE::OS::Window*			getWindow() { return reinterpret_cast<AE::OS::Window *>(mAnimaWindow); }
			//void					renderFrame();
			//void					yield();

		private:
			//std::vector<AE::Graphics::Device *> mDevices;
			//AE::uint				mNumberOfDevices;
			Ogre::Root				*mOgreRoot;

			/*void					_createBottomlessInnerConeMesh();
			void					_createBottomlessOuterConeMesh();
			void					_createCubeMesh();
			void					_createOneSidedLowerDiscMesh();
			void					_createOneSidedUpperDiscMesh();
			void					_createOpenInnerCylinderMesh();
			void					_createOpenOuterCylinderMesh();
			void					_createSphereMesh();*/

			//AE::OS::WindowOgre		*mAnimaWindow;
			//Ogre::Camera			*mCamera;
			//AE::Graphics::MeshOgre	*mBottomlessInnerConeMesh;
			//AE::Graphics::MeshOgre	*mBottomlessOuterConeMesh;
			//AE::Graphics::MeshOgre	*mCubeMesh;
			//AE::Graphics::MeshOgre	*mOneSidedLowerDiscMesh;
			//AE::Graphics::MeshOgre	*mOneSidedUpperDiscMesh;
			//AE::Graphics::MeshOgre	*mOpenInnerCylinderMesh;
			//AE::Graphics::MeshOgre	*mOpenOuterCylinderMesh;
			//AE::Graphics::MeshOgre	*mSphereMesh;
			//int						mMeshCount;
			//Ogre::RenderWindow		*mRenderWindow;
			//Ogre::SceneManager		*mSceneManager;

#ifdef OGRE_STATIC_LIB
			Ogre::Plugin			*mOgreRenderSystemPlugin;
#endif
		};
	}
}

#endif
