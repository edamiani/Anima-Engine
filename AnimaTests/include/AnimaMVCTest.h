#ifndef __AE_MVC_TEST__
#define __AE_MVC_TEST__

#include "AnimaGraphicsCamera2d.h"
#include "AnimaGraphicsManager.h"
#include "AnimaGraphicsMesh.h"
#include "AnimaGraphicsViewport.h"
#include "AnimaMVCFrontControllerFSMState.h"
#include "AnimaMVCModel.h"
#include "AnimaMVCView.h"
#include "AnimaPlatform.h"

#include <list>
#include <utility>

#define USING_OPENGL 0

typedef std::pair<AE::Graphics::VertexBuffer *, AE::Graphics::IndexBuffer *> Object;

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
		mObjects.clear();
		mIBs.clear();
		mVBs.clear();
	}

	AE::Graphics::Camera* getCamera() { return mCamera; }
	std::list<AE::Graphics::Mesh *>& getMeshes() { return mMeshes; }
	std::list<Object>& getObjects() { return mObjects; }

	void insert(AE::Graphics::Mesh *mesh)
	{
		mMeshes.push_back(mesh);
	}

	void insert(AE::Graphics::VertexBuffer *vb, AE::Graphics::IndexBuffer *ib)
	{
		Object obj;
		obj.first = vb;
		obj.second = ib;

		mVBs.push_back(vb);
		mIBs.push_back(ib);
		mObjects.push_back(obj);
	}

private:
	AE::Graphics::Manager *mGraphicsManager;
	std::list<AE::Graphics::IndexBuffer *> mIBs;
	std::list<AE::Graphics::Mesh *> mMeshes;
	std::list<AE::Graphics::VertexBuffer *> mVBs;
	std::list<Object> mObjects;
	AE::Graphics::Camera *mCamera;
};




class MyView : public AE::MVC::View
{
public:
	MyView(AE::Graphics::Manager *graphicsManager, AE::MVC::Model *model) 
		: View(graphicsManager), mModel(model)
	{
		mViewport = new AE::Graphics::Viewport(static_cast<MyModel *>(mModel)->getCamera());
		mGraphicsManager->setViewport(mViewport);
	}

	~MyView() {  }

	void render()
	{
		if(mGraphicsManager->beginRendering(AE::Graphics::Color(128, 0, 0, 255)))
		{
			/*std::list<Object> objects = static_cast<MyModel *>(mModel)->getObjects();
			std::list<Object>::iterator i;

			for(i = objects.begin(); i != objects.end(); i++)
				mGraphicsManager->render(AE::Graphics::ROT_TRIANGLE_LIST, (*i).first, (*i).second);*/
			std::list<AE::Graphics::Mesh *> meshes = static_cast<MyModel *>(mModel)->getMeshes();
			std::list<AE::Graphics::Mesh *>::iterator i;

			AE::Math::Matrix4 identity;
			identity.setIdentity();

			for(i = meshes.begin(); i != meshes.end(); i++)
				mGraphicsManager->render(identity, *i);

			mGraphicsManager->endRendering();
		}
	}

private:
	AE::MVC::Model *mModel;
	AE::Graphics::Viewport *mViewport;
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