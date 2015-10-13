#ifndef __AE_GRAPHICS_MANAGER_DX9__
#define __AE_GRAPHICS_MANAGER_DX9__

#include "AnimaGraphicsManager.h"
#include "AnimaMathVector2.h"
#include "AnimaMathVector3.h"
#include "AnimaPlatform.h"

#include <d3d9.h>

namespace AE
{
	namespace Graphics
	{
		class Geometry;

		class ManagerDX9 : public Manager
		{
		public:
			ManagerDX9(AE::uint graphicsManagerOption = AE::Graphics::GMO_HARDWARE);
			~ManagerDX9();

			void					blit(AE::Graphics::Surface *source, AE::Graphics::Surface *dest, const AE::Math::Vector2 &destPosition);
			//AE::Graphics::Font*		createFont(const std::string &fontFace, AE::Real size, AE::Graphics::FontType fontType = AE::Graphics::FT_TRUETYPE);
			IndexBuffer*			createIndexBuffer(std::vector<AE::ushort> &indices, BufferUsage bufferUsage, BufferChangeFrequency bufferChangeFrequency);
			Mesh*					createMesh(RenderOperationType renderOperationType, VertexBuffer *vertexBuffer, IndexBuffer *indexBuffer = 0);
			//AE::Graphics::Sprite*	createSprite(AE::Graphics::SpriteDesc &spriteDesc);
			AE::Graphics::Surface*	createSurface(AE::uint16 width, AE::uint16 height, AE::Graphics::SurfaceFormat surfaceFormat);
			VertexBuffer*			createVertexBuffer(VertexBufferDesc &vertexBufferDesc);
			//void					destroySprite(const std::string &name);
			void					destroySurface(AE::Graphics::Surface* surface);
			void					enableLighting(bool enable) { mD3dDevice->SetRenderState(D3DRS_LIGHTING, enable); }
			AE::OS::Window*			getWindow() { return 0; }
			bool					initialize(AE::OS::Window *window);
			void					render(const AE::Math::Matrix4 &parentTransformation, AE::Graphics::Mesh *mesh);
			void					render(AE::Graphics::RenderOperationType renderOperationType, const AE::Math::Matrix4 &parentTransformation, AE::Graphics::VertexBuffer *vb, AE::Graphics::IndexBuffer *ib = 0);
			void					renderFrame();
			void					yield();

			IDirect3D9*				_getD3D9Object() { return mD3d9; }
			IDirect3DDevice9*		_getDevice() { return mD3dDevice; }

		private:
			IDirect3D9				*mD3d9;
			IDirect3DDevice9		*mD3dDevice;
		};
	}
}

#endif
