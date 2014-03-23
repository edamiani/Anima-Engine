#ifndef __AE_MVC_TEST__
#define __AE_MVC_TEST__

#include "AnimaMVCFrontControllerFSMState.h"
#include "AnimaMVCModel.h"
#include "AnimaMVCView.h"
#include "AnimaGraphicsCamera2d.h"
#include "AnimaGraphicsFontFactoryFT.h"
#include "AnimaGraphicsFontFaceFT.h"
#include "AnimaGraphicsImageTGA.h"
#include "AnimaGraphicsMesh.h"
#include "AnimaGraphicsSurface.h"
#include "AnimaGraphicsViewport.h"
#include "AnimaSceneFactoryX3D.h"
#include "AnimaSceneGraphX3D.h"
#include "AnimaSceneDrawableNode.h"
#include "AnimaSceneTransformNode.h"

#include <ctime>
#include <list>
#include <utility>

#ifdef AE_PLATFORM_WIN32
	#define USING_OPENGL 0
#else
	#define USING_OPENGL 1
#endif

enum FrontControllerFSMState
{
	FSM_STATE_MAIN
};

class MyModel: public AE::MVC::Model
{
public:
	MyModel(AE::Graphics::Manager *graphicsManager) : mGraphicsManager(graphicsManager) 
	{
#if USING_OPENGL == 0
		mCamera = new AE::Graphics::Camera2d();
#else
		mCamera = new AE::Graphics::Camera2d(true);
#endif
		mCamera->setPosition(AE::Math::Vector3(0, 0, 0));
		mCamera->setWindowDimensions(AE::Math::Vector2(-5, -5), AE::Math::Vector2(5, 5));
		
		mSceneGraph = new AE::Scene::GraphX3D(mGraphicsManager);
		mSceneFactory = new AE::Scene::FactoryX3D(mGraphicsManager);

		AE::Graphics::VertexBufferDesc vbd;
		AE::Math::Vector3 vertexPosition;
		std::vector<AE::Math::Vector3> positions;

		/////////////////////// Creation of the first triangle //////////////////////////////

		AE::Graphics::RGBA color;

#if defined(AE_PLATFORM_WIN32) && USING_OPENGL == 0
		// DX9
		vertexPosition = AE::Math::Vector3(5, 0, -5.0); positions.push_back(vertexPosition);
		vertexPosition = AE::Math::Vector3(0, 0, -5.0); positions.push_back(vertexPosition);
		vertexPosition = AE::Math::Vector3(0, 5, -5.0); positions.push_back(vertexPosition);
		color = 0xcc00ff00;
#else	
		// OpenGL
		vertexPosition = AE::Math::Vector3(0, 5, -5.0); positions.push_back(vertexPosition);
		vertexPosition = AE::Math::Vector3(0, 0, -5.0); positions.push_back(vertexPosition);
		vertexPosition = AE::Math::Vector3(5, 0, -5.0); positions.push_back(vertexPosition);
		color = 0x000000ff;
#endif
		
		vbd.positions = &positions;

		
		std::vector<AE::Graphics::RGBA> diffuseColors;
		diffuseColors.push_back(color);
		diffuseColors.push_back(color);
		diffuseColors.push_back(color);
		vbd.diffuseColors = &diffuseColors;
		vbd.vertexElements |= AE::Graphics::VE_DIFFUSE;

		vbd.bufferChangeFrequency = AE::Graphics::BCF_STATIC;
		vbd.bufferUsage = AE::Graphics::BU_USER_READ;
		AE::Graphics::VertexBuffer *vb = mGraphicsManager->createVertexBuffer(vbd);
		
		std::vector<AE::ushort> indices;
		indices.push_back(0); indices.push_back(1); indices.push_back(2);
		AE::Graphics::IndexBuffer *ib = mGraphicsManager->createIndexBuffer(indices, AE::Graphics::BU_USER_READ, AE::Graphics::BCF_STATIC);

		AE::Graphics::Mesh *mesh = mGraphicsManager->createMesh(AE::Graphics::ROT_TRIANGLE_LIST, vb, ib);

		mTransformNode1 = new AE::Scene::TransformNode(mSceneGraph->getRootNode());
		mMeshNode1 = new AE::Scene::DrawableNode(mesh, mTransformNode1);

		/////////////////////// Creation of the second triangle //////////////////////////////

		positions.clear();

#if defined(AE_PLATFORM_WIN32) && USING_OPENGL == 0
		// DX9
		vertexPosition = AE::Math::Vector3(3.0, -1.0, -5.0); positions.push_back(vertexPosition);
		vertexPosition = AE::Math::Vector3(2.0, -1.0, -5.0); positions.push_back(vertexPosition);
		vertexPosition = AE::Math::Vector3(2.5, 1.0, -5.0); positions.push_back(vertexPosition);
#else	
		// OpenGL
		vertexPosition = AE::Math::Vector3(2.5, -1.5, -5.0); positions.push_back(vertexPosition);
		vertexPosition = AE::Math::Vector3(2.0, -2.5, -5.0); positions.push_back(vertexPosition);
		vertexPosition = AE::Math::Vector3(3.0, -2.5, -5.0); positions.push_back(vertexPosition);
#endif
		
		vbd.positions = &positions;

		color = 0x7700ff00;
		diffuseColors.clear();
		diffuseColors.push_back(color);
		diffuseColors.push_back(color);
		diffuseColors.push_back(color);
		vbd.diffuseColors = &diffuseColors;
		vbd.vertexElements |= AE::Graphics::VE_DIFFUSE;

		vbd.bufferChangeFrequency = AE::Graphics::BCF_STATIC;
		vbd.bufferUsage = AE::Graphics::BU_USER_READ;
		vb = mGraphicsManager->createVertexBuffer(vbd);
		
		indices.clear();
		indices.push_back(0); indices.push_back(1); indices.push_back(2);
		ib = mGraphicsManager->createIndexBuffer(indices, AE::Graphics::BU_USER_READ, AE::Graphics::BCF_STATIC);

		mesh = mGraphicsManager->createMesh(AE::Graphics::ROT_TRIANGLE_LIST, vb, ib);

		mMeshNode2 = new AE::Scene::DrawableNode(mesh, mSceneGraph->getRootNode());

		/////////////////////// Creation of the third triangle //////////////////////////////

		positions.clear();

#if defined(AE_PLATFORM_WIN32) && USING_OPENGL == 0
		// DX9
		vertexPosition = AE::Math::Vector3(5.0, -4.0, -5.0); positions.push_back(vertexPosition);
		vertexPosition = AE::Math::Vector3(4.0, -4.0, -5.0); positions.push_back(vertexPosition);
		vertexPosition = AE::Math::Vector3(4.5, -3.0, -5.0); positions.push_back(vertexPosition);
#else	
		// OpenGL
		vertexPosition = AE::Math::Vector3(4.5, -3.0, -5.0); positions.push_back(vertexPosition);
		vertexPosition = AE::Math::Vector3(4.0, -4.0, -5.0); positions.push_back(vertexPosition);
		vertexPosition = AE::Math::Vector3(5.0, -4.0, -5.0); positions.push_back(vertexPosition);
#endif
		
		vbd.positions = &positions;

		color = 0xffffffff;
		diffuseColors.clear();
		diffuseColors.push_back(color);
		diffuseColors.push_back(color);
		diffuseColors.push_back(color);
		vbd.diffuseColors = &diffuseColors;
		vbd.vertexElements |= AE::Graphics::VE_DIFFUSE;

		vbd.bufferChangeFrequency = AE::Graphics::BCF_STATIC;
		vbd.bufferUsage = AE::Graphics::BU_USER_READ;
		vb = mGraphicsManager->createVertexBuffer(vbd);
		
		indices.clear();
		indices.push_back(0); indices.push_back(1); indices.push_back(2);
		ib = mGraphicsManager->createIndexBuffer(indices, AE::Graphics::BU_USER_READ, AE::Graphics::BCF_STATIC);

		mesh = mGraphicsManager->createMesh(AE::Graphics::ROT_TRIANGLE_LIST, vb, ib);

		mTransformNode3 = new AE::Scene::TransformNode(mTransformNode1);
		mMeshNode3 = new AE::Scene::DrawableNode(mesh, mTransformNode3);

		mImageSmiley = new AE::Graphics::ImageTGA();
		mImageSmiley->load("smiley.tga");
		//image->save("smiley2.tga");
		//AE::Graphics::ImageTGA *image2 = new AE::Graphics::ImageTGA();
		//image2->load("smiley2.tga");
		//delete image;
	}

	~MyModel() 
	{ 

		std::list<AE::Graphics::IndexBuffer *>::iterator iIB;
		for(iIB = mIBs.begin(); iIB != mIBs.end(); iIB++)
			delete (*iIB);

		std::list<AE::Graphics::VertexBuffer *>::iterator iVB;
		for(iVB = mVBs.begin(); iVB != mVBs.end(); iVB++)
			delete (*iVB);

		mMeshes.clear();
		mIBs.clear();
		mVBs.clear();
	}

	AE::Graphics::Camera* getCamera() { return mCamera; }
	std::list<AE::Graphics::Mesh *>& getMeshes() { return mMeshes; }
	AE::Scene::Graph* getSceneGraph() { return mSceneGraph; }
	AE::Graphics::ImageTGA *getSmiley() { return mImageSmiley; }

	void insert(AE::Graphics::Mesh *mesh)
	{
		mMeshes.push_back(mesh);
	}

	void moveNode()
	{
		static AE::Real position = 0.0f;
		static AE::Real delta = -0.005f;
		
		position += delta;
		if(position < -5.0f || position > 0.0f)
			delta = -delta;		

		static_cast<AE::Scene::TransformNode *>(mMeshNode1->getParentNode())->translate(AE::Math::Vector3(delta, 0.0f, 0.0f));		
		static_cast<AE::Scene::TransformNode *>(mMeshNode3->getParentNode())->translate(AE::Math::Vector3(delta * 0.8f, 0.0f, 0.0f));
	}

private:
	AE::Graphics::Manager *mGraphicsManager;
	std::list<AE::Graphics::IndexBuffer *> mIBs;
	std::list<AE::Graphics::Mesh *> mMeshes;
	std::list<AE::Graphics::VertexBuffer *> mVBs;
	AE::Graphics::Camera *mCamera;

	AE::Graphics::ImageTGA *mImageSmiley;

	AE::Scene::DrawableNode *mMeshNode1;
	AE::Scene::DrawableNode *mMeshNode2;
	AE::Scene::DrawableNode *mMeshNode3;

	AE::Scene::TransformNode *mTransformNode1;
	AE::Scene::TransformNode *mTransformNode3;

	AE::Scene::FactoryX3D *mSceneFactory;
	AE::Scene::GraphX3D *mSceneGraph;
};




class MyView : public AE::MVC::View
{
public:
	MyView(AE::Graphics::Manager *graphicsManager, AE::MVC::Model *model) 
		: View(graphicsManager), mModel(static_cast<MyModel *>(model))
	{
		mViewport = new AE::Graphics::Viewport(mModel->getCamera());
		mGraphicsManager->setViewport(mViewport);

		mFontFactory = new AE::Graphics::FontFactoryFT();
		mFontFactory->init();
		mFontFace = mFontFactory->createFontFace("arial.ttf", 12, 12, 72, 72);
	}

	~MyView() {  }

	void render()
	{
		if(mGraphicsManager->beginRendering(AE::Graphics::Color(0, 0, 128, 255)))
		{
			//mGraphicsManager->getSurface()->lock(AE::Graphics::LT_DISCARD);
				//AE::uint32 color = 255 + (255 << 8) + (255 << 16);
				//for(int i = 0; i < 120000; i++)
					//mGraphicsManager->getSurface()->plot32(color, AE::Math::Vector2(rand() % 800, rand() % 600));
					//mGraphicsManager->getSurface()->plot(AE::Graphics::Color(255, 255, 255, 0), AE::Math::Vector2(rand() % 800, rand() % 600));

				/*for(int i = 0; i < 400; i++)
					mGraphicsManager->getSurface()->plot(AE::Graphics::Color(255, 255, 255, 0), AE::Math::Vector2(i + 200, i));*/
			//mGraphicsManager->getSurface()->unlock();

			AE::uint32 square[16384];
			
			
			mGraphicsManager->getSurface()->lock(AE::Graphics::LT_DISCARD);
				for(int i = 0; i < 550; i++)
					mGraphicsManager->getSurface()->plot(AE::Graphics::Color(255, 255, 255, 0), AE::Math::Vector2(400, i));
				
				//for(int i = 0; i < 50; i++)
					//mGraphicsManager->getSurface()->blit2(square, AE::Math::Vector2(128, 128), AE::Math::Vector2(rand() % 672, rand() % 472));
				//mGraphicsManager->getSurface()->blit2(square, AE::Math::Vector2(128, 128), AE::Math::Vector2(0, 0));

				ZeroMemory(square, 65536);	
				for (int i = 0; i < 16384; i++)
					square[i] |= 0x88ffff00;

				//mGraphicsManager->getSurface()->blit(square, AE::Math::Vector2(128, 128), AE::Math::Vector2(50, 50));

				ZeroMemory(square, 65536);
				for (int i = 0; i < 16384; i++)
					square[i] |= 0x88ff0000;
				//mGraphicsManager->getSurface()->blit(square, AE::Math::Vector2(128, 128), AE::Math::Vector2(100, 100));
				mGraphicsManager->getSurface()->blit(mModel->getSmiley()->getData(), mModel->getSmiley()->getDimensions(), AE::Math::Vector2(0, 0));
				mGraphicsManager->getSurface()->blit(mFontFace->getSurface(), mFontFace->getSurface()->getDimensions(), AE::Math::Vector2(350, 350));
				/*mGraphicsManager->getSurface()->blit2(mModel->getSmiley()->getData(), mModel->getSmiley()->getDimensions(), AE::Math::Vector2(100, 200));
				mGraphicsManager->getSurface()->blit2(mModel->getSmiley()->getData(), mModel->getSmiley()->getDimensions(), AE::Math::Vector2(150, 100));
				mGraphicsManager->getSurface()->blit2(mModel->getSmiley()->getData(), mModel->getSmiley()->getDimensions(), AE::Math::Vector2(150, 200));
				mGraphicsManager->getSurface()->blit2(mModel->getSmiley()->getData(), mModel->getSmiley()->getDimensions(), AE::Math::Vector2(200, 100));
				mGraphicsManager->getSurface()->blit2(mModel->getSmiley()->getData(), mModel->getSmiley()->getDimensions(), AE::Math::Vector2(200, 200));
				mGraphicsManager->getSurface()->blit2(mModel->getSmiley()->getData(), mModel->getSmiley()->getDimensions(), AE::Math::Vector2(250, 100));
				mGraphicsManager->getSurface()->blit2(mModel->getSmiley()->getData(), mModel->getSmiley()->getDimensions(), AE::Math::Vector2(250, 200));*/

				mGraphicsManager->getSurface()->unlock();

			//mModel->moveNode();
			//mModel->getSceneGraph()->traverse(mModel->getSceneGraph()->getRootNode());

			mGraphicsManager->endRendering();
		}	
	}

private:
	MyModel *mModel;
	AE::Graphics::Viewport *mViewport;
	AE::Graphics::FontFactory *mFontFactory;
	AE::Graphics::FontFace *mFontFace;
};




class MyFrontControllerFSMState : public AE::MVC::FrontControllerFSMState
{
public:
	MyFrontControllerFSMState(int type, AE::MVC::Model *model, AE::MVC::View *view) :
		FrontControllerFSMState(type, model, view) {  }
	~MyFrontControllerFSMState() {}

	void onUpdate(float dt)
	{
		mView->render();
	}
};

#endif