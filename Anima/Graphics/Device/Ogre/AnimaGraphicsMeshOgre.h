#ifndef __ANIMA_GRAPHICS_MESH_OGRE__
#define __ANIMA_GRAPHICS_MESH_OGRE__

#include "AnimaGraphicsMesh.h"

#include "Ogre.h"
#include "OgreHardwareVertexBuffer.h"
#include "OgreMesh.h"
#include "OgreSubMesh.h"

namespace AE
{
	namespace Graphics
	{
		class MeshOgre : public Mesh
		{
		public:
			//MeshOgre(std::string &meshName, Points &vertices, Indices &indices, BufferUsage bufferUsage, RenderOperationType renderOperationType, bool useShadowBuffer = false);
			MeshOgre(std::string &meshName, VertexBuffer *vertexBuffer, IndexBuffer *indexBuffer, RenderOperationType renderOperationType);
			~MeshOgre() { mOgreMesh.setNull(); }

			Ogre::MeshPtr _getOgreMesh() { return mOgreMesh; }

		private:
			Ogre::MeshPtr mOgreMesh;
		};
	}
}


#endif