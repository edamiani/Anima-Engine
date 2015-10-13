#ifndef __AE_GRAPHICS_MANAGER_GL__
#define __AE_GRAPHICS_MANAGER_GL__

#include "AnimaGraphicsDeviceManagerGL.h"
#include "AnimaMathVector3.h"

namespace AE
{
	namespace Graphics
	{
		class Geometry;

		class ManagerGL : public Manager
		{
		public:
			ManagerGL(AE::uint graphicsManagerOption = AE::Graphics::GMO_HARDWARE);
			~ManagerGL();

			void					blit(AE::Graphics::Surface *source, AE::Graphics::Surface *dest, const AE::Math::Vector2 &destPosition) {}
			//AE::Graphics::Font*		createFont(const std::string &fontFace, AE::Real size, AE::Graphics::FontType fontType = AE::Graphics::FT_TRUETYPE);
			IndexBuffer*			createIndexBuffer(std::vector<AE::ushort> &indices, BufferUsage bufferUsage, BufferChangeFrequency bufferChangeFrequency);
			Mesh*					createMesh(RenderOperationType renderOperationType, VertexBuffer *vertexBuffer, IndexBuffer *indexBuffer = 0);
			//AE::Graphics::Sprite*	createSprite(AE::Graphics::SpriteDesc &spriteDesc);
			AE::Graphics::Surface*	createSurface(AE::uint16 width, AE::uint16 height, AE::Graphics::SurfaceFormat surfaceFormat);
			VertexBuffer*			createVertexBuffer(VertexBufferDesc &vertexBufferDesc);
			//void					destroySprite(const std::string &name);
			void					destroySurface(AE::Graphics::Surface* surface);
			void					enableLighting(bool enable) {  }
			AE::OS::Window*			getWindow() { return 0; }
			bool					initialize(AE::OS::Window *window);
			void					render(const AE::Math::Matrix4 &parentTransformation, AE::Graphics::Mesh *mesh);
			void					render(AE::Graphics::RenderOperationType renderOperationType, const AE::Math::Matrix4 &parentTransformation, AE::Graphics::VertexBuffer *vb, AE::Graphics::IndexBuffer *ib = 0);
			void					renderFrame();
			void					yield();

			void					_initializeExtensions();
#ifdef WIN32
			void					_setDeviceContext(HDC hdc) { mDeviceContext = hdc; }
#endif

		private:
			bool					_checkOpenGLExtension(char* extensionName);

#ifdef WIN32
			HDC						mDeviceContext;
			HGLRC					mRenderingContext;
#elif defined(MAC_OS_X_VERSION_10_0)
			AGLContext				mAGLContext;
#endif
		};
	}
}

#endif
