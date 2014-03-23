#ifndef __AE_GRAPHICS_MANAGER__
#define __AE_GRAPHICS_MANAGER__

#include "AnimaPluginGroup.h"

#include "AnimaPlatform.h"
#include "AnimaTypes.h"

#include "AnimaGraphicsDeviceContext.h"
#include "AnimaGraphicsDeviceDriver.h"
#include "AnimaGraphicsDeviceManager.h"
#include "AnimaGraphicsEnums.h"
#include "AnimaGraphicsImageManagerAE.h"
#include "AnimaGraphicsIndexBuffer.h"
#include "AnimaGraphicsManager.h"
#include "AnimaGraphicsMesh.h"
#include "AnimaGraphicsSurface.h"
#include "AnimaGraphicsVertexBuffer.h"
#include "AnimaMathVector3.h"
#include "AnimaMathMatrix4.h"

#include <map>
#include <vector>

namespace AE
{
	namespace Graphics
	{
		class ImageManager;

		namespace Device
		{
			class Manager;
		}

		namespace Font
		{
			class Manager;
		}

		class Manager : public AE::PluginGroup
		{
		public:
			Manager();
			virtual ~Manager();

			static AE::Graphics::Manager*	getInstance() { assert(mInstance); return mInstance; }

			//virtual void					blit(AE::Graphics::Surface *source, AE::Graphics::Surface *dest, const AE::Math::Vector2 &destPosition) = 0;
			//AE::Graphics::Font*				createFont(const std::string &fontFace, AE::Real size, AE::Graphics::FontType fontType = AE::Graphics::FT_TRUETYPE);
			//virtual IndexBuffer*			createIndexBuffer(std::vector<AE::ushort> &indices, BufferUsage bufferUsage, BufferChangeFrequency bufferChangeFrequency) = 0;
			//virtual Mesh*					createMesh(RenderOperationType renderOperationType, VertexBuffer *vertexBuffer, IndexBuffer *indexBuffer = 0) = 0;
			//virtual AE::Graphics::Sprite*	createSprite(AE::Graphics::SpriteDesc &spriteDesc) = 0;
			//virtual AE::Graphics::Surface*	createSurface(AE::uint16 width, AE::uint16 height, AE::Graphics::SurfaceFormat surfaceFormat) = 0;
			//virtual VertexBuffer*			createVertexBuffer(VertexBufferDesc &vertexBufferDesc) = 0;
			//virtual void					destroySprite(const std::string &name) = 0;
			//virtual void					destroySurface(AE::Graphics::Surface* surface) = 0;
			//virtual void					enableLighting(bool enable) = 0;
			AE::Graphics::Device::Manager*	getDeviceManager() { return mDeviceManager; }
			AE::Graphics::Font::Manager*	getFontManager() { return mFontManager; }
			AE::Graphics::ImageManager*		getImageManager() { return mImageManager; }
			//AE::Graphics::Surface*			getSurface() { return mSurface; }
			//AE::Graphics::Viewport*			getViewport() { return mViewport; }
			//virtual AE::OS::Window*			getWindow() = 0;
			//AE::Graphics::Sprite*			getSprite(const std::string &name);
			bool							install(AE::uint options);
			//virtual void					render(const AE::Math::Matrix4 &parentTransformation, AE::Graphics::Mesh *mesh) = 0;
			//virtual void					render(AE::Graphics::RenderOperationType renderOperationType, const AE::Math::Matrix4 &parentTransformation, AE::Graphics::VertexBuffer *vb, AE::Graphics::IndexBuffer *ib = 0) = 0;
			//virtual void					renderFrame() = 0;
			void							setViewport(AE::Graphics::Viewport *viewport) { mViewport = viewport; }
			bool							uninstall();
			//virtual void					yield() = 0;

		protected:

			static AE::Graphics::Manager	*mInstance;

			AE::Graphics::Device::Manager	*mDeviceManager;
			AE::Graphics::Font::Manager		*mFontManager;
			AE::Graphics::ImageManager		*mImageManager;

			//std::vector<AE::Graphics::Device *> mGraphicsDevices;
			//AE::uint8 mNumberOfGraphicsDevices;

			//std::map<std::string, AE::Graphics::IndexBuffer*>		mIndexBuffers;
			//std::map<std::string, AE::Graphics::Mesh*>				mMeshes;
			//std::map<std::string, AE::Graphics::Sprite*>			mSprites;
			//std::map<std::string, AE::Graphics::VertexBuffer*>		mVertexBuffers;

			//AE::Graphics::Surface *mSurface;
			//std::map<AE::uint8, AE::Graphics::Surface*>		mSurfaces;
			AE::Graphics::Viewport *mViewport;
		};
	}
}

#endif
