#include "../include/AnimaGraphicsCamera.h"
#include "../include/AnimaGraphicsManagerDX9.h"
#include "../include/AnimaGraphicsIndexBufferDX9.h"
#include "../include/AnimaGraphicsSurfaceDX9.h"
#include "../include/AnimaGraphicsVertexBufferDX9.h"
#include "../include/AnimaGraphicsViewport.h"
#include "../include/AnimaOSWindow.h"

//#include "../include/AnimaMath.h"

#include <cassert>

namespace AE
{
	namespace Graphics
	{
		ManagerDX9::ManagerDX9(AE::uint graphicsManagerOption) 
			: Manager(graphicsManagerOption), mD3d9(0), mD3dDevice(0)
		{
			AE::Graphics::Manager::mInstance = this;

			mD3d9 = ::Direct3DCreate9(D3D_SDK_VERSION);
			assert(mD3d9);

			mNumberOfVideoAdapters = mD3d9->GetAdapterCount();
			/*int monitorCount = 0;
			for (int i = 0; i < mNumberOfVideoAdapters; i++)
			{
				HMONITOR monitor = mD3d9->GetAdapterMonitor(i);
				if(monitor) monitorCount++;
			}*/
		}

		ManagerDX9::~ManagerDX9()
		{
			/*std::map<std::string, AE::Graphics::Sprite*>::iterator spritesIterator;
			for (spritesIterator = mSprites.begin(); spritesIterator != mSprites.end(); spritesIterator++)
				delete spritesIterator->second;
			mSprites.clear();

			std::map<std::string, AE::Graphics::Mesh*>::iterator meshesIterator;
			for (meshesIterator = mMeshes.begin(); meshesIterator != mMeshes.end(); meshesIterator++)
				delete meshesIterator->second;
			mMeshes.clear();*/

			std::map<std::string, AE::Graphics::IndexBuffer*>::iterator ibIterator;
			for (ibIterator = mIndexBuffers.begin(); ibIterator != mIndexBuffers.end(); ibIterator++)
				delete ibIterator->second;
			mIndexBuffers.clear();

			std::map<std::string, AE::Graphics::VertexBuffer*>::iterator vbIterator;
			for (vbIterator = mVertexBuffers.begin(); vbIterator != mVertexBuffers.end(); vbIterator++)
				delete vbIterator->second;
			mVertexBuffers.clear();

			if(mD3dDevice)
				mD3dDevice->Release();

			if(mD3d9)
				mD3d9->Release();

			AE::Graphics::Manager::mInstance = 0;
		}

		void ManagerDX9::blit(AE::Graphics::Surface *source, AE::Graphics::Surface *dest, const AE::Math::Vector2 &destPosition)
		{
			POINT point;
			IDirect3DSurface9 *surfSource = static_cast<AE::Graphics::SurfaceDX9 *>(source)->_getSurfaceDX9();
			IDirect3DSurface9 *surfDest = static_cast<AE::Graphics::SurfaceDX9 *>(dest)->_getSurfaceDX9();
			point.x = static_cast<LONG>(destPosition.x);
			point.y = static_cast<LONG>(destPosition.y);
			/*HRESULT result = mD3dDevice->UpdateSurface(static_cast<AE::Graphics::SurfaceDX9 *>(source)->_getSurfaceDX9(), NULL,
													   static_cast<AE::Graphics::SurfaceDX9 *>(dest)->_getSurfaceDX9(), &point);*/
			HRESULT result = mD3dDevice->UpdateSurface(surfSource, NULL, surfDest, &point);
			assert(result == D3D_OK);
		}

		/*AE::Graphics::Font* ManagerDX9::createFont(const std::string &fontFace, AE::Real size, AE::Graphics::FontType fontType)
		{
			//return (new AE::Graphics::FontOgre(fontFace, size, fontType));
			return 0;
		}*/

		IndexBuffer* ManagerDX9::createIndexBuffer(std::vector<AE::ushort> &indices, BufferUsage bufferUsage, BufferChangeFrequency bufferChangeFrequency)
		{
			IndexBuffer *indexBuffer = new IndexBufferDX9(indices, bufferUsage, bufferChangeFrequency, mD3dDevice);
			//mIndexBuffers[name] = indexBuffer;
			return indexBuffer;
			return 0;
		}

		Mesh* ManagerDX9::createMesh(RenderOperationType renderOperationType, VertexBuffer *vertexBuffer, IndexBuffer *indexBuffer)
		{
			Mesh *mesh = new Mesh(renderOperationType, vertexBuffer, indexBuffer);
			//mMeshes[name] = mesh;
			return mesh;
		}

		/*AE::Graphics::Sprite* ManagerDX9::createSprite(AE::Graphics::SpriteDesc &spriteDesc)
		{
			AE::Graphics::Sprite *sprite;

			if(spriteDesc.prefabType == AE::Graphics::PF_NONE)
			{
				assert(spriteDesc.name != "" && spriteDesc.mesh != "");
				Ogre::Entity *ogreEntity = mSceneManager->createEntity(spriteDesc.name, spriteDesc.mesh);
				
				ogreEntity->setVisible(spriteDesc.isVisible);

				//mSceneManager->getSceneNode(spriteDesc.node->getName())->attachObject(ogreEntity);
				Ogre::SceneNode *ogreSceneNode = mSceneManager->createSceneNode(spriteDesc.name);
				ogreSceneNode->attachObject(ogreEntity);

				ogreSceneNode->setScale(spriteDesc.scale.x, spriteDesc.scale.y, spriteDesc.scale.z);

				if(spriteDesc.shadowCaster)
					ogreEntity->setCastShadows(true);
				else
					ogreEntity->setCastShadows(false);

				sprite = new AE::Graphics::SpriteOgre(ogreEntity, spriteDesc.position, spriteDesc.orientation);
			}
			else
			{
				if(spriteDesc.prefabType == AE::Graphics::PF_CUBE)
				{
					Ogre::String meshName(Ogre::String(spriteDesc.name) + Ogre::String("Mesh"));

					Ogre::Vector3 positionVec(spriteDesc.position.x, spriteDesc.position.y, spriteDesc.position.z);
					Ogre::Entity *ogreEntity = mSceneManager->createEntity(meshName, "AnimaCubeMesh", "AnimaEngine");
					Ogre::SceneNode *node = mSceneManager->getRootSceneNode()->createChildSceneNode(meshName, positionVec);
					node->attachObject(ogreEntity);
					node->scale(spriteDesc.scale.x, spriteDesc.scale.y, spriteDesc.scale.z);

					sprite = new AE::Graphics::SpriteOgre(ogreEntity, spriteDesc.position, spriteDesc.orientation);
				}
			}

			sprite->setName(spriteDesc.name);
			mSprites[spriteDesc.name] = sprite;
			return sprite;
		}*/

		AE::Graphics::Surface* ManagerDX9::createSurface(AE::uint16 width, AE::uint16 height, AE::Graphics::SurfaceFormat surfaceFormat)
		{
			//AE::Graphics::Surface *surface = new AE::Graphics::SurfaceDX9(this, width, height, surfaceFormat);
			//return surface;
			return 0;
		}

		VertexBuffer* ManagerDX9::createVertexBuffer(VertexBufferDesc &vertexBufferDesc)
		{
			VertexBuffer *vertexBuffer = new VertexBufferDX9(vertexBufferDesc, mD3dDevice);
			//mVertexBuffers[name] = vertexBuffer;
			return vertexBuffer;
			return 0;
		}

		/*void ManagerDX9::destroySprite(const std::string &name)
		{
			Ogre::Entity *entity = static_cast<AE::Graphics::SpriteOgre *>(mSprites[name])->_getOgreEntity();
			mSceneManager->destroySceneNode(entity->getParentSceneNode());
			mSceneManager->destroyEntity(entity);
			mSprites.erase(name);
		}*/

		void ManagerDX9::destroySurface(AE::Graphics::Surface* surface) 
		{ 
			delete static_cast<AE::Graphics::SurfaceDX9 *>(surface); 
		}

		void ManagerDX9::render(const AE::Math::Matrix4 &parentTransformation, AE::Graphics::Mesh *mesh)
		{
			render(mesh->getRenderOperationType(), parentTransformation, mesh->getVertexBuffer(), mesh->getIndexBuffer()); 
		}

		void ManagerDX9::render(AE::Graphics::RenderOperationType renderOperationType, const AE::Math::Matrix4 &parentTransformation, AE::Graphics::VertexBuffer *vb, AE::Graphics::IndexBuffer *ib)
		{
			AE::Math::Matrix4 viewMatrix = mViewport->getCamera()->getViewMatrix();
			AE::Math::Matrix4 projectionMatrix = mViewport->getProjectionMatrix();

			D3DXMATRIX matWorld;
			//D3DXMatrixIdentity( &matWorld );
			matWorld.m[0][0] = parentTransformation[0][0]; matWorld.m[0][1] = parentTransformation[0][1]; matWorld.m[0][2] = parentTransformation[0][2]; matWorld.m[0][3] = parentTransformation[0][3];
			matWorld.m[1][0] = parentTransformation[1][0]; matWorld.m[1][1] = parentTransformation[1][1]; matWorld.m[1][2] = parentTransformation[1][2]; matWorld.m[1][3] = parentTransformation[1][3];
			matWorld.m[2][0] = parentTransformation[2][0]; matWorld.m[2][1] = parentTransformation[2][1]; matWorld.m[2][2] = parentTransformation[2][2]; matWorld.m[2][3] = parentTransformation[2][3];
			matWorld.m[3][0] = parentTransformation[3][0]; matWorld.m[3][1] = parentTransformation[3][1]; matWorld.m[3][2] = parentTransformation[3][2]; matWorld.m[3][3] = parentTransformation[3][3];
			mD3dDevice->SetTransform( D3DTS_WORLD, &matWorld );

			/*D3DXVECTOR3 vEyePt   ( 0.0f, 0.0f, 0.0f );
			D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 5.0f );
			D3DXVECTOR3 vUpVec   ( 0.0f, 1.0f, 0.0f );
			D3DXMATRIXA16 matView;
			D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );*/

			D3DXMATRIXA16 matView;
			//D3DXMatrixIdentity( &matView );
			//viewMatrix = parentTransformation * viewMatrix;
			matView.m[0][0] = viewMatrix[0][0]; matView.m[0][1] = viewMatrix[0][1]; matView.m[0][2] = viewMatrix[0][2]; matView.m[0][3] = viewMatrix[0][3];
			matView.m[1][0] = viewMatrix[1][0]; matView.m[1][1] = viewMatrix[1][1]; matView.m[1][2] = viewMatrix[1][2]; matView.m[1][3] = viewMatrix[1][3];
			matView.m[2][0] = viewMatrix[2][0]; matView.m[2][1] = viewMatrix[2][1]; matView.m[2][2] = viewMatrix[2][2]; matView.m[2][3] = viewMatrix[2][3];
			matView.m[3][0] = viewMatrix[3][0]; matView.m[3][1] = viewMatrix[3][1]; matView.m[3][2] = viewMatrix[3][2]; matView.m[3][3] = viewMatrix[3][3];
			mD3dDevice->SetTransform( D3DTS_VIEW, &matView );

			D3DXMATRIX matProj;
			//D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 0.0f, 10.0f );
			//projectionMatrix = projectionMatrix.transpose();
			matProj.m[0][0] = projectionMatrix[0][0]; matProj.m[0][1] = projectionMatrix[0][1]; matProj.m[0][2] = projectionMatrix[0][2]; matProj.m[0][3] = projectionMatrix[0][3];
			matProj.m[1][0] = projectionMatrix[1][0]; matProj.m[1][1] = projectionMatrix[1][1]; matProj.m[1][2] = projectionMatrix[1][2]; matProj.m[1][3] = projectionMatrix[1][3];
			matProj.m[2][0] = projectionMatrix[2][0]; matProj.m[2][1] = projectionMatrix[2][1]; matProj.m[2][2] = projectionMatrix[2][2]; matProj.m[2][3] = projectionMatrix[2][3];
			matProj.m[3][0] = projectionMatrix[3][0]; matProj.m[3][1] = projectionMatrix[3][1]; matProj.m[3][2] = projectionMatrix[3][2]; matProj.m[3][3] = projectionMatrix[3][3];
			mD3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );



			IDirect3DVertexBuffer9 *vbD3d = static_cast<AE::Graphics::VertexBufferDX9 *>(vb)->_getVertexBuffer();
			
			IDirect3DIndexBuffer9 *ibD3d = 0;
			if(ib)
				ibD3d = static_cast<AE::Graphics::IndexBufferDX9 *>(ib)->_getIndexBuffer();

			D3DPRIMITIVETYPE primitiveType;
			AE::uint primitiveCount;
			switch(renderOperationType)
			{
			case AE::Graphics::ROT_POINT_LIST: 
				primitiveType = D3DPT_POINTLIST;
				primitiveCount = vb->getSize();
				break;
			case AE::Graphics::ROT_LINE_LIST: 
				primitiveType = D3DPT_LINELIST;
				if(ib)
					primitiveCount = ib->getSize() / 2;
				else
					primitiveCount = vb->getSize() / 2;
				break;
			case AE::Graphics::ROT_LINE_STRIP: 
				primitiveType = D3DPT_LINESTRIP;
				if(ib)
					primitiveCount = ib->getSize() - 1;
				else
					primitiveCount = vb->getSize() - 1;
				break;
			case AE::Graphics::ROT_TRIANGLE_LIST: 
				primitiveType = D3DPT_TRIANGLELIST;
				if(ib)
					primitiveCount = ib->getSize() / 3;
				else
					primitiveCount = vb->getSize() / 3;
				break;
			case AE::Graphics::ROT_TRIANGLE_STRIP:
				primitiveType = D3DPT_TRIANGLEFAN;
				if(ib)
					primitiveCount = ib->getSize() - 2;
				else
					primitiveCount = vb->getSize() - 2;
				break;
			case AE::Graphics::ROT_TRIANGLE_FAN:
				primitiveType = D3DPT_TRIANGLESTRIP;
				if(ib)
					primitiveCount = ib->getSize() - 2;
				else
					primitiveCount = vb->getSize() - 2;
				break;
			}

			if(FAILED(mD3dDevice->SetStreamSource(0, vbD3d, 0, vb->getStrideInBytes())))
				assert("error!");
			if(FAILED(mD3dDevice->SetVertexDeclaration(static_cast<AE::Graphics::VertexBufferDX9 *>(vb)->_getVertexDeclaration())))
				assert("error!");

			if(ib)
			{
				if(mD3dDevice->SetIndices(ibD3d) != D3D_OK)
					int x = 1;
				if(mD3dDevice->DrawIndexedPrimitive(primitiveType, 0, 0, vb->getSize(), 0, primitiveCount) != D3D_OK)
					assert("error!");
			}
			else
				mD3dDevice->DrawPrimitive(primitiveType, 0, primitiveCount);
		}

		void ManagerDX9::renderFrame()
		{
			/*// Clear the back buffer to a blue color
			mD3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

			// Begin the scene
			mD3dDevice->BeginScene();

			// Rendering of scene objects happens here

			// End the scene
			mD3dDevice->EndScene();

			mD3dDevice->Present(NULL, NULL, NULL, NULL);*/
		}

		void ManagerDX9::yield()
		{
			//mRenderWindow->yield();
		}
	}
}