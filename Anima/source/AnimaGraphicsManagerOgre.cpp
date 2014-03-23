#include "../include/AnimaGraphicsManagerOgre.h"

//#include "../include/AnimaGraphicsDeviceOgre.h"
//#include "../include/AnimaGraphicsFontOgre.h"
//#include "../include/AnimaGraphicsIndexBufferOgre.h"
//#include "../include/AnimaGraphicsSpriteOgre.h"
//#include "../include/AnimaGraphicsVertexBufferOgre.h"
#include "../include/AnimaTypes.h"
#include "../include/AnimaOSWindowOgre.h"

//#include "../include/AnimaMath.h"

#include "Ogre.h"
//#include <OgreFont.h>
//#include <OgreFontManager.h>

#ifdef OGRE_STATIC_LIB
	#include <RenderSystems/GL/include/OgreGLPlugin.h>
	#include <RenderSystems/Direct3D9/include/OgreD3D9Plugin.h>
#endif

namespace AE
{
	namespace Graphics
	{
		ManagerOgre::ManagerOgre(/*AE::Framework *framework,*/ AE::uint graphicsManagerOptions)
		{
			mOgreRoot = OGRE_NEW Ogre::Root("", "ogre.cfg", "ogre.log");

#		ifdef OGRE_STATIC_LIB
			if(graphicsManagerOptions & AE::Graphics::GMO_DX9)
				mOgreRenderSystemPlugin = OGRE_NEW Ogre::D3D9Plugin();
			else if(graphicsManagerOptions & AE::Graphics::GMO_OPENGL)
				mOgreRenderSystemPlugin = OGRE_NEW Ogre::GLPlugin();
			else
				mOgreRenderSystemPlugin = OGRE_NEW Ogre::GLPlugin();

			mOgreRoot->installPlugin(mOgreRenderSystemPlugin);
#		else
#		ifdef _DEBUG
			if(graphicsManagerOptions & AE::Graphics::GMO_OPENGL)
				mOgreRoot->loadPlugin("RenderSystem_GL_d");
			else if(graphicsManagerOptions & AE::Graphics::GMO_DX9)
				mOgreRoot->loadPlugin("RenderSystem_Direct3D9_d");
			else
				mOgreRoot->loadPlugin("RenderSystem_GL_d");
#		else
			if(graphicsManagerOptions & AE::Graphics::GMO_OPENGL)
				mOgreRoot->loadPlugin("RenderSystem_GL");
			else if(graphicsManagerOptions & AE::Graphics::GMO_DX9)
				mOgreRoot->loadPlugin("RenderSystem_Direct3D9");
			else
				mOgreRoot->loadPlugin("RenderSystem_GL");
#		endif
#		endif

			mOgreRoot->initialise(false);

			mNumberOfDevices = mOgreRoot->getDisplayMonitorCount();

			for(AE::uint i = 0; i < mNumberOfDevices; i++)
				mDevices.push_back(new AE::Graphics::DeviceOgre(i));

			/*if(mRoot->showConfigDialog())
				mRenderWindow = mRoot->initialise(true);
			else
				mFramework->stop();

			if(mFramework->isRunning())
			{
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Resources","FileSystem","AnimaGeneral");
				Ogre::ResourceGroupManager::getSingleton().createResourceGroup("AnimaEngine");
				mMeshCount = 0;
				_createCubeMesh();

				mAnimaWindow = new AE::OS::WindowOgre(mFramework, this, mRenderWindow);
				Ogre::WindowEventUtilities::addWindowEventListener(mRenderWindow, mAnimaWindow);

				mSceneManager = mRoot->createSceneManager(Ogre::ST_GENERIC, "LilaScene");

				mCamera = mSceneManager->createCamera("DefaultCam");

				mCamera->setPosition(Ogre::Vector3(0,0,20));
				mCamera->lookAt(Ogre::Vector3(0,0,0));
				mCamera->setNearClipDistance(5);

				Ogre::Viewport* vp = mRenderWindow->addViewport(mCamera, 1);
				vp->setBackgroundColour(Ogre::ColourValue(0,0,0.0,0));
				vp->setClearEveryFrame(true, Ogre::FBT_DEPTH);

				// Alter the camera aspect ratio to match the viewport
				mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

				Ogre::SceneManager *scene2 = mRoot->createSceneManager(Ogre::ST_GENERIC, "LilaScene2");
				Ogre::Camera *camera2 = scene2->createCamera("DefaultCam2");
				camera2->setPosition(Ogre::Vector3(0,0,20));
				camera2->lookAt(Ogre::Vector3(0,0,0));
				camera2->setNearClipDistance(5);
				vp = mRenderWindow->addViewport(camera2, 0);
				vp->setBackgroundColour(Ogre::ColourValue(0,0,96));
				camera2->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
				Ogre::String meshName("Scene2Cube");
				Ogre::Vector3 positionVec(0.0f, 0.0f, 0.0f);
				Ogre::Entity *entity = scene2->createEntity(meshName, "AnimaCubeMesh", "AnimaEngine");
				Ogre::SceneNode *node = scene2->getRootSceneNode()->createChildSceneNode(meshName, positionVec);
				node->attachObject(entity);
				node->scale(2.0f, 2.0f, 2.0f);

				Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

				Ogre::Animation::setDefaultInterpolationMode(Ogre::Animation::IM_SPLINE);
				Ogre::Animation::setDefaultRotationInterpolationMode(Ogre::Animation::RIM_SPHERICAL);
			}*/
		}

		ManagerOgre::~ManagerOgre()
		{
			/*std::map<std::string, AE::Graphics::Sprite*>::iterator spritesIterator;
			for (spritesIterator = mSprites.begin(); spritesIterator != mSprites.end(); spritesIterator++)
				delete spritesIterator->second;
			mSprites.clear();

			std::map<std::string, AE::Graphics::Mesh*>::iterator meshesIterator;
			for (meshesIterator = mMeshes.begin(); meshesIterator != mMeshes.end(); meshesIterator++)
				delete meshesIterator->second;
			mMeshes.clear();

			std::map<std::string, AE::Graphics::IndexBuffer*>::iterator ibIterator;
			for (ibIterator = mIndexBuffers.begin(); ibIterator != mIndexBuffers.end(); ibIterator++)
				delete ibIterator->second;
			mIndexBuffers.clear();

			std::map<std::string, AE::Graphics::VertexBuffer*>::iterator vbIterator;
			for (vbIterator = mVertexBuffers.begin(); vbIterator != mVertexBuffers.end(); vbIterator++)
				delete vbIterator->second;
			mVertexBuffers.clear();*/

			mOgreRoot->shutdown();

#ifdef OGRE_STATIC_LIB
			mOgreRenderSystemPlugin->shutdown();
#endif

			//Ogre::MeshManager::getSingleton().destroyAllResourcePools();
			//Ogre::OverlayManager::getSingleton().destroyAll();
			//Ogre::FontManager::getSingleton().destroyAllResourcePools();

			//mCubeMesh.setNull();

			//Ogre::WindowEventUtilities::removeWindowEventListener(mRenderWindow, dynamic_cast<AE::OS::WindowOgre*>(mAnimaWindow));

			/*if(mAnimaWindow) 
				delete mAnimaWindow;*/

			if(mOgreRoot)
				OGRE_DELETE mOgreRoot;

#ifdef OGRE_STATIC_LIB
			if(mOgreRenderSystemPlugin)
				OGRE_DELETE mOgreRenderSystemPlugin;
#endif
		}

		/*void ManagerOgre::createCube(AE::Math::Vector3 &position, AE::Math::Vector3 &size)
		{
			Ogre::Real scaleX = 1 / size.x;
			Ogre::Real scaleY = 1 / size.y;
			Ogre::Real scaleZ = 1 / size.z;

			Ogre::String meshName(Ogre::String("Mesh") + Ogre::String(Ogre::StringConverter::toString(mMeshCount)));
			mMeshCount++;

			Ogre::Vector3 positionVec(position.x, position.y, position.z);
			Ogre::Entity *entity = mSceneManager->createEntity(meshName, "AnimaCubeMesh", "AnimaEngine");
			Ogre::SceneNode *node = mSceneManager->getRootSceneNode()->createChildSceneNode(meshName, positionVec);
			node->attachObject(entity);
			node->scale(size.x, size.y, size.z);
		}*/

		/*AE::Graphics::Font* ManagerOgre::createFont(const std::string &fontFace, AE::Real size, AE::Graphics::FontType fontType)
		{
			//return (new AE::Graphics::FontOgre(fontFace, size, fontType));
			return 0;
		}*/

		/*void ManagerOgre::createGrid(int m, int n, float gridSize)
		{
			Ogre::ManualObject* myManualObject =  mSceneManager->createManualObject("manual1"); 
			Ogre::SceneNode* myManualObjectNode = mSceneManager->getRootSceneNode()->createChildSceneNode("manual1_node"); 
			 
			Ogre::MaterialPtr myManualObjectMaterial = Ogre::MaterialManager::getSingleton().create("manual1Material", "AnimaEngine"); 
			myManualObjectMaterial->setReceiveShadows(false); 
			myManualObjectMaterial->getTechnique(0)->setLightingEnabled(true); 
			myManualObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(1,1,1,0); 
			myManualObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(1,1,1); 
			myManualObjectMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(0,0,0); 
			 
			myManualObject->begin("manual1Material", Ogre::RenderOperation::OT_LINE_LIST);
			float totalSize = m * gridSize;
			float halfSize = totalSize / 2.0f;
			float initialX, initialZ;
			float finalX, finalZ;
			
			initialX = initialZ = (-halfSize) + (gridSize / 2.0f);
			finalX = finalZ = halfSize - (gridSize / 2.0f);

			float nX = initialX;
			float nZ = initialZ;
			for(int i = 0; i < n; i++)
			{
				myManualObject->position(initialX, 0, nZ); 
				myManualObject->position(finalX, 0, nZ);
				nZ += gridSize;
			}
			for(int i = 0; i < m; i++)
			{
				myManualObject->position(nX, 0, initialZ); 
				myManualObject->position(nX, 0, finalZ);
				nX += gridSize;
			}
			myManualObject->end(); 
			
			myManualObjectNode->attachObject(myManualObject);
		}*/

		/*IndexBuffer* ManagerOgre::createIndexBuffer(std::string &name, std::vector<AE::ushort> &indices, BufferUsage bufferUsage, bool useShadowBuffer)
		{
			IndexBuffer *indexBuffer = new IndexBufferOgre(indices, bufferUsage, useShadowBuffer);
			mIndexBuffers[name] = indexBuffer;
			return indexBuffer;
		}*/

		/*Mesh* ManagerOgre::createMesh(std::string &name, VertexBuffer *vertexBuffer, IndexBuffer *indexBuffer, RenderOperationType renderOperationType)
		{
			Mesh *mesh = new MeshOgre(name, vertexBuffer, indexBuffer, renderOperationType);
			mMeshes[name] = mesh;
			return mesh;
		}*/

		/*AE::Graphics::Sprite* ManagerOgre::createSprite(AE::Graphics::SpriteDesc &spriteDesc)
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

				//if(spriteDesc.initialAnimation != "")
					//sprite->enableAnimation(spriteDesc.initialAnimation);
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

		/*VertexBuffer* ManagerOgre::createVertexBuffer(std::string &name, VertexBufferDesc &vertexBufferDesc)
		{
			VertexBuffer *vertexBuffer = new VertexBufferOgre(vertexBufferDesc);
			mVertexBuffers[name] = vertexBuffer;
			return vertexBuffer;
		}*/

		/*void ManagerOgre::destroySprite(const std::string &name)
		{
			Ogre::Entity *entity = static_cast<AE::Graphics::SpriteOgre *>(mSprites[name])->_getOgreEntity();
			mSceneManager->destroySceneNode(entity->getParentSceneNode());
			mSceneManager->destroyEntity(entity);
			mSprites.erase(name);
		}*/

		/*void ManagerOgre::renderFrame()
		{
			Ogre::WindowEventUtilities::messagePump();
			try
			{
				mRoot->renderOneFrame();
			}
			catch(Ogre::Exception &e)
			{
				assert("" == e.getFullDescription().c_str());
			}
		}*/

		/*void ManagerOgre::yield()
		{
			//mRenderWindow->yield();
		}*/

		/*void ManagerOgre::_createBottomlessInnerConeMesh()
		{
			AE::Real bottomRadius = 1;
			AE::Real height = 2;
			AE::uint nSegments = 20;
			//AE::Real radiusStep = bottomRadius / nSegments;
			AE::Real deltaAngle = ((2 * AE::Math::PI) / nSegments);

			std::vector<AE::Math::Vector3> vertices;
			std::vector<AE::ushort> indices;

			vertices.push_back(AE::Math::Vector3(0.f, 1.f, 0.f));
			//AE::Real currentRadius = radiusStep;

			// Generate the bottom ring
			AE::ushort vertexIndex = 1;
			for(AE::uint i = 0 ; i < nSegments; i++, vertexIndex++)
			{
				AE::Real angle = i * deltaAngle;
				vertices.push_back(AE::Math::Vector3(cosf(angle), -1.f, sinf(angle)));

				if(i < nSegments - 1)
				{ indices.push_back(0); indices.push_back(vertexIndex); indices.push_back(vertexIndex + 1); }
				else
				{ indices.push_back(0); indices.push_back(vertexIndex); indices.push_back(1); }
			}

			AE::Graphics::VertexBufferDesc vertexBufferDesc;
			vertexBufferDesc.positions = &vertices;
			AE::Graphics::VertexBufferOgre vb = static_cast<VertexBufferOgre *>(createVertexBuffer(std::string("AnimaBottomlessInnerConeVB"), vertexBufferDesc));
			AE::Graphics::IndexBufferOgre ib = static_cast<IndexBufferOgre *>(createIndexBuffer(std::string("AnimaBottomlessInnerConeIB"), indices, AE::Graphics::BU_STATIC_WRITE_ONLY, false));
			mBottomlessInnerConeMesh = static_cast<MeshOgre *>(createMesh(std::string("AnimaBottomlessInnerConeMesh"), vb, ib, AE::Graphics::ROT_TRIANGLE_LIST));
		}*/

		/*void ManagerOgre::_createBottomlessOuterConeMesh()
		{
			AE::Real bottomRadius = 1;
			AE::Real height = 2;
			AE::uint nSegments = 20;
			//AE::Real radiusStep = bottomRadius / nSegments;
			AE::Real deltaAngle = ((2 * AE::Math::PI / nSegments);

			std::vector<AE::Math::Vector3> vertices;
			std::vector<AE::ushort> indices;

			vertices.push_back(AE::Math::Vector3(0.f, 1.f, 0.f));
			//AE::Real currentRadius = radiusStep;

			// Generate the bottom ring
			AE::ushort vertexIndex = 1;
			for(AE::uint i = 0 ; i < nSegments; i++, vertexIndex++)
			{
				AE::Real angle = i * deltaAngle;
				vertices.push_back(AE::Math::Vector3(cosf(angle), -1.f, sinf(angle)));

				if(i < nSegments - 1)
				{
					indices.push_back(0); indices.push_back(vertexIndex + 1); indices.push_back(vertexIndex);
				}
				else
				{
					indices.push_back(0); indices.push_back(1); indices.push_back(vertexIndex);
				}
			}

			AE::Graphics::VertexBufferDesc vertexBufferDesc;
			vertexBufferDesc.positions = vertices;
			AE::Graphics::VertexBufferOgre vb = static_cast<VertexBufferOgre *>(createVertexBuffer("AnimaBottomlessOuterConeVB", vertexBufferDesc));
			AE::Graphics::IndexBufferOgre ib = static_cast<IndexBufferOgre *>(createIndexBuffer("AnimaBottomlessOuterConeIB", indices, AE::Graphics::BU_STATIC_WRITE_ONLY, false));
			mBottomlessOuterConeMesh = static_cast<MeshOgre *>(createMesh("AnimaBottomlessOuterConeMesh", vb, ib, AE::Graphics::ROT_TRIANGLE_LIST));
		}*/

		/*void ManagerOgre::_createCubeMesh()
		{
			std::vector<AE::Math::Vector3> positions;
			positions.push_back(AE::Math::Vector3(-0.5f, -0.5f, 0.5f));
			positions.push_back(AE::Math::Vector3(-0.5f, -0.5f, -0.5f));
			positions.push_back(AE::Math::Vector3(0.5f, -0.5f, -0.5f));
			positions.push_back(AE::Math::Vector3(0.5f, -0.5f, 0.5f));
			positions.push_back(AE::Math::Vector3(-0.5f, 0.5f, 0.5f));
			positions.push_back(AE::Math::Vector3(-0.5f, 0.5f, -0.5f));
			positions.push_back(AE::Math::Vector3(0.5f, 0.5f, -0.5f));
			positions.push_back(AE::Math::Vector3(0.5f, 0.5f, 0.5f));
			
			AE::Graphics::VertexBufferDesc vertexBufferDesc;
			vertexBufferDesc.useShadowBuffer = true;
			vertexBufferDesc.positions = &positions;
			VertexBufferOgre *vertexBuffer = static_cast<VertexBufferOgre *>(createVertexBuffer(std::string("AnimaCubeVB"), vertexBufferDesc));

			std::vector<AE::ushort> indices;
			indices.push_back(0); indices.push_back(1); indices.push_back(2);
			indices.push_back(2); indices.push_back(3); indices.push_back(0);
			indices.push_back(0); indices.push_back(4); indices.push_back(5);
			indices.push_back(5); indices.push_back(1); indices.push_back(0);
			indices.push_back(2); indices.push_back(1); indices.push_back(5);
			indices.push_back(5); indices.push_back(6); indices.push_back(2);
			indices.push_back(3); indices.push_back(2); indices.push_back(6);
			indices.push_back(6); indices.push_back(7); indices.push_back(3);
			indices.push_back(7); indices.push_back(4); indices.push_back(0);
			indices.push_back(7); indices.push_back(0); indices.push_back(3);
			indices.push_back(4); indices.push_back(7); indices.push_back(6);
			indices.push_back(6); indices.push_back(5); indices.push_back(4);
			
			IndexBufferOgre *indexBuffer = static_cast<IndexBufferOgre *>(createIndexBuffer(std::string("AnimaCubeIB"), indices, BU_STATIC_WRITE_ONLY, false));

			mCubeMesh = static_cast<MeshOgre *>(createMesh(std::string("AnimaCubeMesh"), vertexBuffer, indexBuffer, ROT_TRIANGLE_LIST));
		}*/

		/*void ManagerOgre::_createOneSidedLowerDiscMesh()
		{
			AE::Real radius = 1;
			AE::uint nSegments = 20;
			AE::Real deltaAngle = ((2 * AE::Math::PI / nSegments);

			std::vector<AE::Math::Vector3> vertices;
			std::vector<AE::ushort> indices;

			vertices.push_back(AE::Math::Vector3(0.f, 0.f, 0.f));
			//AE::Real currentRadius = radiusStep;

			// Generate the ring
			AE::ushort vertexIndex = 1;
			for(AE::uint i = 0 ; i < nSegments; i++, vertexIndex++)
			{
				AE::Real angle = i * deltaAngle;
				vertices.push_back(AE::Math::Vector3(cosf(angle), -1.f, sinf(angle)));

				if(i < nSegments - 1)
					indices.push_back(0); indices.push_back(vertexIndex + 1); indices.push_back(vertexIndex);
				else
					indices.push_back(0); indices.push_back(1); indices.push_back(vertexIndex);
			}

			AE::Graphics::VertexBufferDesc vertexBufferDesc;
			vertexBufferDesc.positions = vertices;
			AE::Graphics::VertexBufferOgre vb = static_cast<VertexBufferOgre *>(createVertexBuffer("AnimaOneSidedLowerDiscVB", vertexBufferDesc));
			AE::Graphics::IndexBufferOgre ib = static_cast<IndexBufferOgre *>(createIndexBuffer("AnimaOneSidedLowerDiscIB", indices, AE::Graphics::BU_STATIC_WRITE_ONLY, false));
			mOneSidedLowerDiscMesh = static_cast<MeshOgre *>(createMesh("AnimaOneSidedLowerDiscMesh", vb, ib, AE::Graphics::ROT_TRIANGLE_LIST));
		}*/

		/*void ManagerOgre::_createOneSidedUpperDiscMesh()
		{
			AE::Real radius = 1;
			AE::uint nSegments = 20;
			AE::Real deltaAngle = ((2 * AE::Math::PI / nSegments);

			std::vector<AE::Math::Vector3> vertices;
			std::vector<AE::ushort> indices;

			vertices.push_back(AE::Math::Vector3(0.f, 0.f, 0.f));
			//AE::Real currentRadius = radiusStep;

			// Generate the ring
			AE::ushort vertexIndex = 1;
			for(AE::uint i = 0 ; i < nSegments; i++, vertexIndex++)
			{
				AE::Real angle = i * deltaAngle;
				vertices.push_back(AE::Math::Vector3(cosf(angle), -1.f, sinf(angle)));

				if(i < nSegments - 1)
					indices.push_back(0); indices.push_back(vertexIndex); indices.push_back(vertexIndex + 1);
				else
					indices.push_back(0); indices.push_back(vertexIndex); indices.push_back(1);
			}

			AE::Graphics::VertexBufferDesc vertexBufferDesc;
			vertexBufferDesc.positions = vertices;
			AE::Graphics::VertexBufferOgre vb = static_cast<VertexBufferOgre *>(createVertexBuffer("AnimaOneSidedUpperDiscVB", vertexBufferDesc));
			AE::Graphics::IndexBufferOgre ib = static_cast<IndexBufferOgre *>(createIndexBuffer("AnimaOneSidedUpperDiscIB", indices, AE::Graphics::BU_STATIC_WRITE_ONLY, false));
			mOneSidedUpperDiscMesh = static_cast<MeshOgre *>(createMesh("AnimaOneSidedUpperDiscMesh", vb, ib, AE::Graphics::ROT_TRIANGLE_LIST));
		}*/

		/*void ManagerOgre::_createOpenInnerCylinderMesh()
		{
			AE::Real radius = 1.f;
			AE::Real height = 2.f;
			AE::uint nSegments = 20;
			AE::Real deltaAngle = ((2 * AE::Math::PI / nSegments);

			std::vector<AE::Math::Vector3> vertices;
			std::vector<AE::ushort> indices;

			// Generate the upper ring and indices
			AE::ushort vertexIndex = 0;
			for(int segment = 0; segment < nSegments; segment++, vertexIndex++) 
			{
				AE::Real x = sinf(segment * deltaAngle);
				AE::Real z = cosf(segment * deltaAngle);
				vertices.push_back(AE::Math::Vector3(x, 1.f, z));

				if(segment < (nSegments - 1))
				{
					//First triangle
					indices.push_back(vertexIndex + nSegments + 1);
					indices.push_back(vertexIndex + nSegments);
					indices.push_back(vertexIndex);
					// Second triangle
					indices.push_back(vertexIndex + nSegments + 1);
					indices.push_back(vertexIndex);
					indices.push_back(vertexIndex + 1);
				}
				else
				{
					//First triangle
					indices.push_back(vertexIndex + 1);
					indices.push_back(vertexIndex + nSegments);
					indices.push_back(vertexIndex);
					// Second triangle
					indices.push_back(vertexIndex + 1);
					indices.push_back(vertexIndex);
					indices.push_back(vertexIndex + 1 - nSegments);
				}

				// Generate the lower ring
				for(int segment = 0; segment < nSegments; segment++, vertexCount++) 
				{
					AE::Real x = sinf(segment * deltaAngle);
					AE::Real z = cosf(segment * deltaAngle);
					vertices.push_back(AE::Math::Vector3(x, -1.f, z));
				}
			}

			AE::Graphics::VertexBufferDesc vertexBufferDesc;
			vertexBufferDesc.positions = vertices;
			AE::Graphics::VertexBufferOgre vb = static_cast<VertexBufferOgre *>(createVertexBuffer("AnimaOpenInnerCylinderVB", vertexBufferDesc));
			AE::Graphics::IndexBufferOgre ib = static_cast<IndexBufferOgre *>(createIndexBuffer("AnimaOpenInnerCylinderIB", indices, AE::Graphics::BU_STATIC_WRITE_ONLY, false));
			mOpenInnerCylinderMesh = static_cast<MeshOgre *>(createMesh("AnimaOpenInnerCylinderMesh", vb, ib, AE::Graphics::ROT_TRIANGLE_LIST));
		}*/

		/*void ManagerOgre::_createOpenOuterCylinderMesh()
		{
			AE::Real radius = 1.f;
			AE::Real height = 2.f;
			AE::uint nSegments = 20;
			AE::Real deltaAngle = ((2 * AE::Math::PI / nSegments);

			std::vector<AE::Math::Vector3> vertices;
			std::vector<AE::ushort> indices;

			// Generate the upper ring and indices
			AE::ushort vertexIndex = 0;
			for(int segment = 0; segment < nSegments; segment++, vertexIndex++) 
			{
				AE::Real x = sinf(segment * deltaAngle);
				AE::Real z = cosf(segment * deltaAngle);
				vertices.push_back(AE::Math::Vector3(x, 1.f, z));

				if(segment < (nSegments - 1))
				{
					//First triangle
					indices.push_back(vertexIndex + nSegments + 1);
					indices.push_back(vertexIndex);
					indices.push_back(vertexIndex + nSegments);
					// Second triangle
					indices.push_back(vertexIndex + nSegments + 1);
					indices.push_back(vertexIndex + 1);
					indices.push_back(vertexIndex);
				}
				else
				{
					//First triangle
					indices.push_back(vertexIndex + 1);
					indices.push_back(vertexIndex);
					indices.push_back(vertexIndex + nSegments);
					// Second triangle
					indices.push_back(vertexIndex + 1);
					indices.push_back(vertexIndex + 1 - nSegments);
					indices.push_back(vertexIndex);
				}

				// Generate the lower ring
				for(int segment = 0; segment < nSegments; segment++, vertexCount++) 
				{
					AE::Real x = sinf(segment * deltaAngle);
					AE::Real z = cosf(segment * deltaAngle);
					vertices.push_back(AE::Math::Vector3(x, -1.f, z));
				}
			}

			AE::Graphics::VertexBufferDesc vertexBufferDesc;
			vertexBufferDesc.positions = vertices;
			AE::Graphics::VertexBufferOgre vb = static_cast<VertexBufferOgre *>(createVertexBuffer("AnimaOpenOuterCylinderVB", vertexBufferDesc));
			AE::Graphics::IndexBufferOgre ib = static_cast<IndexBufferOgre *>(createIndexBuffer("AnimaOpenOuterCylinderIB", indices, AE::Graphics::BU_STATIC_WRITE_ONLY, false));
			mOpenOuterCylinderMesh = static_cast<MeshOgre *>(createMesh("AnimaOpenOuterCylinderMesh", vb, ib, AE::Graphics::ROT_TRIANGLE_LIST));
		}*/
		
		/*void ManagerOgre::_createSphereMesh()
		{
			AE::Real radius = 1.f;
			AE::uint nRings = 16;
			AE::uint nSegments = 16;

			std::vector<AE::Math::Vector3> vertices;
			std::vector<AE::ushort> indices;

			vertices.push_back(AE::Math::Vector3(0.f, 1.f, 0.f));

			AE::Real deltaRingAngle = (AE::Math::PI / nRings);
			AE::Real deltaSegAngle = (2 * AE::Math::PI / nSegments);
			AE::ushort vertexIndex = 1;

			AE::Real x, y, z, r0;

			// Generate the first ring
			r0 = sinf(deltaRingAngle);
			y = cosf(deltaRingAngle);
			for(int segment = 0; segment < nSegments; segment++, vertexIndex++)
			{
				x = r0 * sinf(segment * deltaSegAngle);
				z = r0 * cosf(segment * deltaSegAngle);
				vertices.push_back(AE::Math::Vector3(x, y, z));

				if(segment < nSegments - 1)
					indices.push_back(0); indices.push_back(vertexIndex); indices.push_back(vertexIndex + 1);
				else
					indices.push_back(0); indices.push_back(vertexIndex); indices.push_back(1);
			}

			// Generate the sphere's middle rings
			for(int ring = 2; ring < nRings; ring++, vertexIndex++;) 
			{
				r0 = sinf(ring * deltaRingAngle);
				y = cosf(ring * deltaRingAngle);

				// Generate the group of segments for the current ring
				for(int segment = 0; segment <= nSegments; segment++) 
				{
					x = r0 * sinf(segment * deltaSegAngle);
					z = r0 * cosf(segment * deltaSegAngle);
					vertices.push_back(AE::Math::Vector3(x, y, z));

					if(segment < (nSegments - 1))
					{
						//First triangle
						indices.push_back(vertexIndex + nSegments + 1);
						indices.push_back(vertexIndex);
						indices.push_back(vertexIndex + nSegments);
						// Second triangle
						indices.push_back(vertexIndex + nSegments + 1);
						indices.push_back(vertexIndex + 1);
						indices.push_back(vertexIndex);
					}
					else
					{
						//First triangle
						indices.push_back(vertexIndex + 1);
						indices.push_back(vertexIndex);
						indices.push_back(vertexIndex + nSegments);
						// Second triangle
						indices.push_back(vertexIndex + 1);
						indices.push_back(vertexIndex + 1 - nSegments);
						indices.push_back(vertexIndex);
					}
				} // end of segment
			} // end of ring
			
			// Generate the last ring
			vertices.push_back(AE::Math::Vector3(0.f, -1.f, 0.f));
			vertexIndex++;
			AE::ushort firstIndex = vertexIndex - nSegments;
			for(int lastRing = firstIndex; lastRing <= nSegments; lastRing++)
			{
				if(lastRing < nSegments)
					indices.push_back(lastRing); indices.push_back(lastRing + 1); indices.push_back(lastRing);
				else
					indices.push_back(lastRing); indices.push_back(vertexIndex); indices.push_back(firstIndex);
			}

			AE::Graphics::VertexBufferDesc vertexBufferDesc;
			vertexBufferDesc.positions = vertices;
			AE::Graphics::VertexBufferOgre vb = static_cast<VertexBufferOgre *>(createVertexBuffer("AnimaSphereVB", vertexBufferDesc));
			AE::Graphics::IndexBufferOgre ib = static_cast<IndexBufferOgre *>(createIndexBuffer("AnimaSphereIB", indices, AE::Graphics::BU_STATIC_WRITE_ONLY, false));
			mSphereMesh = static_cast<MeshOgre *>(createMesh("AnimaSphereMesh", vb, ib, AE::Graphics::ROT_TRIANGLE_LIST));
		}*/
	}
}