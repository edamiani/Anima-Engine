#include "../include/AnimaGraphicsManagerGL.h"

#include "../include/AnimaGraphicsCamera.h"
#include "../include/AnimaGraphicsDeviceIndexBufferGL.h"
#include "../include/AnimaGraphicsDeviceVertexBufferGL.h"
#include "../include/AnimaGraphicsSurfaceGL.h"
#include "../include/AnimaGraphicsViewport.h"
#include "../include/AnimaMathMatrix4.h"
#include "../include/AnimaOSWindow.h"

//#include "../include/AnimaMath.h"

// GL_EXT_draw_range_eelments (1.2)
PFNGLDRAWRANGEELEMENTSPROC			glDrawRangeElements;

// GL_EXT_multi_draw_arrays (1.4)
PFNGLMULTIDRAWARRAYSPROC			glMultiDrawArrays;
PFNGLMULTIDRAWELEMENTSPROC			glMultiDrawElements;

// GL_ARB_multitexture (1.4)
PFNGLCLIENTACTIVETEXTUREPROC		glClientActiveTexture;

// GL_ARB_window_pos (1.4)
PFNGLWINDOWPOS2IPROC				glWindowPos2i;

// GL_ARB_vertex_buffer_object(1.5)
PFNGLBINDBUFFERPROC					glBindBuffer;
PFNGLBUFFERDATAPROC					glBufferData;
PFNGLBUFFERSUBDATAPROC				glBufferSubData;
PFNGLDELETEBUFFERSPROC				glDeleteBuffers;
PFNGLGENBUFFERSPROC					glGenBuffers;
PFNGLGETBUFFERPARAMETERIVPROC		glGetBufferParameteriv;
PFNGLGETBUFFERPOINTERVPROC			glGetBufferPointerv;
PFNGLGETBUFFERSUBDATAPROC			glGetBufferSubData;
PFNGLISBUFFERPROC					glIsBuffer;
PFNGLMAPBUFFERPROC					glMapBuffer;
PFNGLUNMAPBUFFERPROC				glUnmapBuffer;

namespace AE
{
	namespace Graphics
	{
		ManagerGL::ManagerGL(AE::uint graphicsManagerOption)
			: Manager(graphicsManagerOption)
		{
			AE::Graphics::Manager::mInstance = this;

			//glEnable(GL_BLEND); 
			//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		ManagerGL::~ManagerGL()
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

		#ifdef AE_PLATFORM_WIN32
			// Resets the screen mode
			ChangeDisplaySettings(0, 0);

			// Make the rendering context not current  
			::wglMakeCurrent(NULL, NULL);

			// Delete the rendering context  
			::wglDeleteContext(mRenderingContext);

			// Delete the window's device context
			::DeleteDC(mDeviceContext);
		#endif

			AE::Graphics::Manager::mInstance = 0;
		}		

		bool ManagerGL::initialize(AE::OS::Window *window)
		{
		/*#ifdef AE_PLATFORM_WIN32
			HDC deviceContext = ::GetDC((HWND)window->getWindowHandle());

			AE::int8 redBits = 0, redShift = 0, greenBits = 0, greenShift = 0, blueBits = 0, blueShift = 0, alphaBits = 0, alphaShift = 0;
			switch(window->getSurfaceFormat())
			{
				case SF_A8R8G8B8:
					redBits = 8; redShift = 0;
					greenBits = 8; greenShift = 8;
					blueBits = 8; blueShift = 16;
					alphaBits = 8; alphaShift = 24;
					break;
				case SF_X8R8G8B8:
					redBits = 8; redShift = 0;
					greenBits = 8; greenShift = 8;
					blueBits = 8; blueShift = 16;
					alphaBits = 0; alphaShift = 0;
					break;
				case SF_A1R5G5B5:
					redBits = 5; redShift = 0;
					greenBits = 5; greenShift = 5;
					blueBits = 5; blueShift = 10;
					alphaBits = 1; alphaShift = 15;
					break;
				case SF_X1R5G5B5:
					redBits = 5; redShift = 0;
					greenBits = 5; greenShift = 5;
					blueBits = 5; blueShift = 10;
					alphaBits = 0; alphaShift = 0;
					break;
				case SF_R5G6B5:
					redBits = 5; redShift = 0;
					greenBits = 6; greenShift = 5;
					blueBits = 5; blueShift = 11;
					alphaBits = 0; alphaShift = 0;
					break;
			}

			PIXELFORMATDESCRIPTOR pfd = { 
				sizeof(PIXELFORMATDESCRIPTOR),   // size of this pfd  
				1,                     // version number  
				PFD_DRAW_TO_BITMAP |   // supports window  
				PFD_SUPPORT_OPENGL |   // supports OpenGL  
				PFD_DOUBLEBUFFER,      // double buffered  
				PFD_TYPE_RGBA,         // RGBA type  
				24,                    // 24-bit color depth  
				redBits, redShift,	   // Red bits, red shift
				greenBits, greenShift, // Green bits, green shift 
				blueBits, blueShift,   // Blue bits, blue shift
				alphaBits, alphaShift, // Alpha bits, alpha shift
				0,                     // no accumulation buffer  
				0, 0, 0, 0,            // accum bits ignored  
				32,                    // 32-bit z-buffer  
				0,                     // no stencil buffer  
				0,                     // no auxiliary buffer  
				PFD_MAIN_PLANE,        // main layer  
				0,                     // reserved  
				0, 0, 0                // layer masks ignored  
			};

			int iPixelFormat;

			// get the best available match of pixel format for the device context   
			iPixelFormat = ::ChoosePixelFormat(mDeviceContext, &pfd); 
			 
			// make it the pixel format of the device context  
			if(::SetPixelFormat(mDeviceContext, iPixelFormat, &pfd) == FALSE)
				return false;

			// Create a rendering context  
			mRenderingContext = ::wglCreateContext(mDeviceContext);
			
			if(mRenderingContext == NULL)
				return false;

			// Make it the calling thread's current rendering context
			::wglMakeCurrent(mDeviceContext, mRenderingContext);

			mSurface = new AE::Graphics::SurfaceGL(this, window->getWindowMetrics().width, window->getWindowMetrics().height, window->getSurfaceFormat());
			static_cast<AE::Graphics::SurfaceGL *>(mSurface)->_setOffScreen(false);

			if(window->isFullScreen())
			{
				DEVMODE dm;
				dm.dmSize = sizeof(DEVMODE);
				dm.dmPelsWidth = window->getWindowMetrics().width;
				dm.dmPelsHeight = window->getWindowMetrics().height;
				dm.dmBitsPerPel = window->getWindowMetrics().getColorDepth();
				dm.dmDisplayFrequency = 60;
				dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;
				ChangeDisplaySettings(&dm, CDS_FULLSCREEN);
			}

		#elif defined(AE_PLATFORM_OSX)

			static GLint glAttributes[] = 
			{
				AGL_DOUBLEBUFFER,	GL_TRUE,
				AGL_RGBA,			GL_TRUE,
				AGL_DEPTH_SIZE,		16,
				AGL_NONE 
			};
			
			AGLPixelFormat openGLFormat = aglChoosePixelFormat(NULL, 0, glAttributes);
			if(openGLFormat == NULL)
				return false;
			
			mAGLContext = aglCreateContext(openGLFormat, NULL);
			if(mAGLContext == NULL)
				return false;
			
			aglDestroyPixelFormat(openGLFormat);
			
			WindowRef winRef = window->getWindowHandle();
			
			//aglSetWindowRef(mAGLContext, winRef);
			aglSetDrawable(mAGLContext, GetWindowPort(winRef));
			aglSetCurrentContext(mAGLContext);			
				
		#endif*/

		if(_checkOpenGLExtension("GL_EXT_draw_range_elements"))
			{
				glDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC) wglGetProcAddress("glDrawRangeElementsEXT");
			}

			if(_checkOpenGLExtension("GL_EXT_multi_draw_arrays"))
			{
				glMultiDrawArrays = (PFNGLMULTIDRAWARRAYSPROC) wglGetProcAddress("glMultiDrawArraysEXT");
				glMultiDrawElements = (PFNGLMULTIDRAWELEMENTSPROC) wglGetProcAddress("glMultiDrawElementsEXT");
			}

			if(_checkOpenGLExtension("GL_ARB_multitexture"))
			{
				glClientActiveTexture = (PFNGLCLIENTACTIVETEXTUREPROC) wglGetProcAddress("glClientActiveTextureARB");
			}

			if(_checkOpenGLExtension("GL_ARB_window_pos"))
			{
				glWindowPos2i = (PFNGLWINDOWPOS2IPROC) wglGetProcAddress("glWindowPos2iARB");
			}

			if(_checkOpenGLExtension("GL_ARB_vertex_buffer_object"))
			{
				glBindBuffer = (PFNGLBINDBUFFERPROC) wglGetProcAddress("glBindBufferARB");
				glDeleteBuffers = (PFNGLDELETEBUFFERSPROC) wglGetProcAddress("glDeleteBuffersARB");
				glGenBuffers = (PFNGLGENBUFFERSPROC) wglGetProcAddress("glGenBuffersARB");
				glIsBuffer = (PFNGLISBUFFERPROC) wglGetProcAddress("glIsBufferARB");
				glBufferData = (PFNGLBUFFERDATAPROC) wglGetProcAddress("glBufferDataARB");
				glBufferSubData = (PFNGLBUFFERSUBDATAPROC) wglGetProcAddress("glBufferSubDataARB");
				glGetBufferSubData = (PFNGLGETBUFFERSUBDATAPROC) wglGetProcAddress("glGetBufferSubDataARB");
				glMapBuffer = (PFNGLMAPBUFFERPROC) wglGetProcAddress("glMapBufferARB");
				glUnmapBuffer = (PFNGLUNMAPBUFFERPROC) wglGetProcAddress("glUnmapBufferARB");
				glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC) wglGetProcAddress("glGetBufferParameterivARB");
				glGetBufferPointerv = (PFNGLGETBUFFERPOINTERVPROC) wglGetProcAddress("glGetBufferPointervARB");
			}
			
			return true;
		}

		/*bool ManagerGL::beginRendering(const AE::Graphics::Color &clearColor)
		{
			//glClearColor(0.0F, 0.0F, 1.0F, 1.0F);
			glClearColor(clearColor.R / 255.0, clearColor.G / 255.0, clearColor.B / 255.0, 1.0f);
			glClearDepth(1.0f);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glShadeModel(GL_SMOOTH);

			return true;
		}*/

		/*AE::Graphics::Font* ManagerGL::createFont(const std::string &fontFace, AE::Real size, AE::Graphics::FontType fontType)
		{
			//return (new AE::Graphics::FontOgre(fontFace, size, fontType));
			return 0;
		}*/

		IndexBuffer* ManagerGL::createIndexBuffer(std::vector<AE::ushort> &indices, BufferUsage bufferUsage, BufferChangeFrequency bufferChangeFrequency)
		{
			IndexBuffer *indexBuffer = new IndexBufferGL(indices, bufferUsage, bufferChangeFrequency);
			//mIndexBuffers[name] = indexBuffer;
			return indexBuffer;
			return 0;
		}

		Mesh* ManagerGL::createMesh(RenderOperationType renderOperationType, VertexBuffer *vertexBuffer, IndexBuffer *indexBuffer)
		{
			Mesh *mesh = new Mesh(renderOperationType, vertexBuffer, indexBuffer);
			//mMeshes[name] = mesh;
			return mesh;
		}

		/*AE::Graphics::Sprite* ManagerGL::createSprite(AE::Graphics::SpriteDesc &spriteDesc)
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

		AE::Graphics::Surface* ManagerGL::createSurface(AE::uint16 width, AE::uint16 height, AE::Graphics::SurfaceFormat surfaceFormat)
		{
			/*AE::Graphics::Surface *surface = new AE::Graphics::SurfaceGL(this, width, height, surfaceFormat);
			return surface;*/
			return 0;
		}

		VertexBuffer* ManagerGL::createVertexBuffer(VertexBufferDesc &vertexBufferDesc)
		{
			VertexBuffer *vertexBuffer = new VertexBufferGL(vertexBufferDesc);
			//mVertexBuffers[name] = vertexBuffer;
			return vertexBuffer;
			return 0;
		}

		/*void ManagerGL::destroySprite(const std::string &name)
		{
			Ogre::Entity *entity = static_cast<AE::Graphics::SpriteOgre *>(mSprites[name])->_getOgreEntity();
			mSceneManager->destroySceneNode(entity->getParentSceneNode());
			mSceneManager->destroyEntity(entity);
			mSprites.erase(name);
		}*/

		void ManagerGL::destroySurface(AE::Graphics::Surface* surface) 
		{ 
			delete static_cast<AE::Graphics::SurfaceGL *>(surface); 
		}

		/*void ManagerGL::endRendering()
		{
		#ifdef AE_PLATFORM_WIN32
			::SwapBuffers(mDeviceContext);
		#endif
		}*/

		void ManagerGL::render(const AE::Math::Matrix4 &parentTransformation, AE::Graphics::Mesh *mesh)
		{
			render(mesh->getRenderOperationType(), parentTransformation, mesh->getVertexBuffer(), mesh->getIndexBuffer());
		}

		void ManagerGL::render(AE::Graphics::RenderOperationType renderOperationType, const AE::Math::Matrix4 &parentTransformation, AE::Graphics::VertexBuffer *vb, AE::Graphics::IndexBuffer *ib)
		{
			assert(mViewport != 0);

			AE::Math::Matrix4 viewMatrix = mViewport->getCamera()->getViewMatrix();
			AE::Math::Matrix4 projectionMatrix = mViewport->getProjectionMatrix();

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			viewMatrix = parentTransformation * viewMatrix;
			//viewMatrix = viewMatrix.transpose();
		#if AE_DOUBLE_PRECISION
			glMultMatrixd(viewMatrix._m);
		#else
			glMultMatrixf(viewMatrix._m);
		#endif
			GLdouble viewMatrixGL[16];
			glGetDoublev(GL_MODELVIEW_MATRIX, viewMatrixGL);

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			projectionMatrix = projectionMatrix.transpose();
		#if AE_DOUBLE_PRECISION
			glMultMatrixd(projectionMatrix._m);
		#else
			glMultMatrixf(projectionMatrix._m);
		#endif



			GLuint vbGL = static_cast<AE::Graphics::VertexBufferGL *>(vb)->_getVertexBuffer();
			
			GLuint ibGL = 0;
			if(ib)
				ibGL = static_cast<AE::Graphics::IndexBufferGL *>(ib)->_getIndexBuffer();

			GLenum primitiveType;
			AE::uint primitiveCount;
			switch(renderOperationType)
			{
			case AE::Graphics::ROT_POINT_LIST: 
				primitiveType = GL_POINTS;
				primitiveCount = vb->getSize();
				break;
			case AE::Graphics::ROT_LINE_LIST: 
				primitiveType = GL_LINES;
				if(ib)
					primitiveCount = ib->getSize() / 2;
				else
					primitiveCount = vb->getSize() / 2;
				break;
			case AE::Graphics::ROT_LINE_STRIP: 
				primitiveType = GL_LINE_STRIP;
				if(ib)
					primitiveCount = ib->getSize() - 1;
				else
					primitiveCount = vb->getSize() - 1;
				break;
			case AE::Graphics::ROT_TRIANGLE_LIST: 
				primitiveType = GL_TRIANGLES;
				if(ib)
					primitiveCount = ib->getSize() / 3;
				else
					primitiveCount = vb->getSize() / 3;
				break;
			case AE::Graphics::ROT_TRIANGLE_STRIP:
				primitiveType = GL_TRIANGLE_STRIP;
				if(ib)
					primitiveCount = ib->getSize() - 2;
				else
					primitiveCount = vb->getSize() - 2;
				break;
			case AE::Graphics::ROT_TRIANGLE_FAN:
				primitiveType = GL_TRIANGLE_FAN;
				if(ib)
					primitiveCount = ib->getSize() - 2;
				else
					primitiveCount = vb->getSize() - 2;
				break;
			}

			glBindBuffer(GL_ARRAY_BUFFER, vbGL);
			size_t error = glGetError();
			static_cast<AE::Graphics::VertexBufferGL *>(vb)->_activateBufferStates();
			error = glGetError();

			if(ib)
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibGL);
				glDrawElements(primitiveType, ib->getSize(), GL_UNSIGNED_BYTE, AE_GL_BUFFER_OFFSET(0));
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			}
			else
			{
				size_t nVertices = vb->getSize();
				glDrawArrays(primitiveType, 0, vb->getSize());
				error = glGetError();
			}

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			error = glGetError();

			static_cast<AE::Graphics::VertexBufferGL *>(vb)->_deactivateBufferStates();
			error = glGetError();
		}

		void ManagerGL::renderFrame()
		{
			glClearColor(0.0F, 0.0F, 1.0F, 1.0F);
			glClearDepth( 1.0F );

			// Draw here

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#ifdef AE_PLATFORM_WIN32
			::SwapBuffers(mDeviceContext);
#endif
		}

		void ManagerGL::yield()
		{
			//mRenderWindow->yield();
		}

		bool ManagerGL::_checkOpenGLExtension(char* extensionName)
		{
			// get the list of supported extensions
			char* extensionList = (char*) glGetString(GL_EXTENSIONS);
			size_t error = glGetError();

			if (!extensionName || !extensionList)
				return false;

			while (*extensionList)
			{
				// find the length of the first extension substring
				unsigned int firstExtensionLength = strcspn(extensionList, " ");

				if (strlen(extensionName) == firstExtensionLength &&
					strncmp(extensionName, extensionList, firstExtensionLength) == 0)
				{
					return true;
				}

				// move to the next substring
				extensionList += firstExtensionLength + 1;
			}

			return false;
		}

		void ManagerGL::_initializeExtensions()
		{

		if(_checkOpenGLExtension("GL_EXT_draw_range_elements"))
			{
				glDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC) wglGetProcAddress("glDrawRangeElementsEXT");
			}

			if(_checkOpenGLExtension("GL_EXT_multi_draw_arrays"))
			{
				glMultiDrawArrays = (PFNGLMULTIDRAWARRAYSPROC) wglGetProcAddress("glMultiDrawArraysEXT");
				glMultiDrawElements = (PFNGLMULTIDRAWELEMENTSPROC) wglGetProcAddress("glMultiDrawElementsEXT");
			}

			if(_checkOpenGLExtension("GL_ARB_multitexture"))
			{
				glClientActiveTexture = (PFNGLCLIENTACTIVETEXTUREPROC) wglGetProcAddress("glClientActiveTextureARB");
			}

			if(_checkOpenGLExtension("GL_ARB_window_pos"))
			{
				glWindowPos2i = (PFNGLWINDOWPOS2IPROC) wglGetProcAddress("glWindowPos2iARB");
			}

			if(_checkOpenGLExtension("GL_ARB_vertex_buffer_object"))
			{
				glBindBuffer = (PFNGLBINDBUFFERPROC) wglGetProcAddress("glBindBufferARB");
				glDeleteBuffers = (PFNGLDELETEBUFFERSPROC) wglGetProcAddress("glDeleteBuffersARB");
				glGenBuffers = (PFNGLGENBUFFERSPROC) wglGetProcAddress("glGenBuffersARB");
				glIsBuffer = (PFNGLISBUFFERPROC) wglGetProcAddress("glIsBufferARB");
				glBufferData = (PFNGLBUFFERDATAPROC) wglGetProcAddress("glBufferDataARB");
				glBufferSubData = (PFNGLBUFFERSUBDATAPROC) wglGetProcAddress("glBufferSubDataARB");
				glGetBufferSubData = (PFNGLGETBUFFERSUBDATAPROC) wglGetProcAddress("glGetBufferSubDataARB");
				glMapBuffer = (PFNGLMAPBUFFERPROC) wglGetProcAddress("glMapBufferARB");
				glUnmapBuffer = (PFNGLUNMAPBUFFERPROC) wglGetProcAddress("glUnmapBufferARB");
				glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC) wglGetProcAddress("glGetBufferParameterivARB");
				glGetBufferPointerv = (PFNGLGETBUFFERPOINTERVPROC) wglGetProcAddress("glGetBufferPointervARB");
			}
		}
	}
}