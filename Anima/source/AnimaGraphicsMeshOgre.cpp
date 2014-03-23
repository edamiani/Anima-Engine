#include "../include/AnimaGraphicsIndexBufferOgre.h"
#include "../include/AnimaGraphicsMeshOgre.h"
#include "../include/AnimaGraphicsVertexBufferOgre.h"
#include "OgreHardwareVertexBuffer.h"

namespace AE
{
	namespace Graphics
	{
		MeshOgre::MeshOgre(std::string &meshName, VertexBuffer *vertexBuffer, IndexBuffer *indexBuffer, RenderOperationType renderOperationType)
			: mIndexBuffer(indexBuffer), mVertexBuffer(vertexBuffer)
		{
			mOgreMesh = Ogre::MeshManager::getSingleton().createManual(meshName, "AnimaEngine");
			Ogre::SubMesh *subMesh = mOgreMesh->createSubMesh();
			
			if(indexBuffer)
				subMesh->indexData->indexCount = indexBuffer->getSize();

			switch(renderOperationType)
			{
				case AE::Graphics::ROT_LINE_LIST: subMesh->operationType = Ogre::RenderOperation::OT_LINE_LIST; break;
				case AE::Graphics::ROT_LINE_STRIP: subMesh->operationType = Ogre::RenderOperation::OT_LINE_STRIP; break;
				case AE::Graphics::ROT_POINT_LIST: subMesh->operationType = Ogre::RenderOperation::OT_POINT_LIST; break;
				case AE::Graphics::ROT_TRIANGLE_FAN: subMesh->operationType = Ogre::RenderOperation::OT_TRIANGLE_FAN; break;
				case AE::Graphics::ROT_TRIANGLE_LIST: subMesh->operationType = Ogre::RenderOperation::OT_TRIANGLE_LIST; break;
				case AE::Graphics::ROT_TRIANGLE_STRIP: subMesh->operationType = Ogre::RenderOperation::OT_TRIANGLE_STRIP; break;
				default: subMesh->operationType = Ogre::RenderOperation::OT_TRIANGLE_LIST; break;
			}

			mOgreMesh->sharedVertexData = OGRE_NEW Ogre::VertexData();
			mOgreMesh->sharedVertexData->vertexStart = 0;
			
			AE::uint vertexDeclaration = vertexBuffer->getVertexDeclaration();
			AE::uint offset = 0;
			Ogre::VertexDeclaration *decl = mOgreMesh->sharedVertexData->vertexDeclaration;
			
			if(vertexDeclaration & VE_POSITION) 
			{
				decl->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
				offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);
			}

			if(vertexDeclaration & VE_BLEND_WEIGHT1)
			{
				decl->addElement(0, offset, Ogre::VET_FLOAT1, Ogre::VES_BLEND_WEIGHTS);
				offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT1);
			}

			if(vertexDeclaration & VE_BLEND_WEIGHT2)
			{
				decl->addElement(0, offset, Ogre::VET_FLOAT1, Ogre::VES_BLEND_WEIGHTS);
				offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT1);
			}

			if(vertexDeclaration & VE_BLEND_WEIGHT3)
			{
				decl->addElement(0, offset, Ogre::VET_FLOAT1, Ogre::VES_BLEND_WEIGHTS);
				offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT1);
			}

			if(vertexDeclaration & VE_BLEND_WEIGHT4)
			{
				decl->addElement(0, offset, Ogre::VET_FLOAT1, Ogre::VES_BLEND_WEIGHTS);
				offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT1);
			}

			if(vertexDeclaration & VE_NORMAL)
			{
				decl->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_NORMAL);
				offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);
			}

			if(vertexDeclaration & VE_DIFFUSE)
			{
				decl->addElement(0, offset, Ogre::VET_COLOUR, Ogre::VES_DIFFUSE);
				offset += Ogre::VertexElement::getTypeSize(Ogre::VET_COLOUR);
			}

			if(vertexDeclaration & VE_SPECULAR)
			{
				decl->addElement(0, offset, Ogre::VET_COLOUR, Ogre::VES_SPECULAR);
				offset += Ogre::VertexElement::getTypeSize(Ogre::VET_COLOUR);
			}

			if(vertexDeclaration & VE_TEX_COORD1)
			{
				decl->addElement(0, offset, Ogre::VET_FLOAT2, Ogre::VES_TEXTURE_COORDINATES);
				offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT2);
			}
			
			if(vertexDeclaration & VE_TEX_COORD2)
			{
				decl->addElement(0, offset, Ogre::VET_FLOAT2, Ogre::VES_TEXTURE_COORDINATES);
				offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT2);
			}
			
			if(vertexDeclaration & VE_TEX_COORD3)
			{
				decl->addElement(0, offset, Ogre::VET_FLOAT2, Ogre::VES_TEXTURE_COORDINATES);
				offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT2);
			}
			
			if(vertexDeclaration & VE_TEX_COORD4)
				decl->addElement(0, offset, Ogre::VET_FLOAT2, Ogre::VES_TEXTURE_COORDINATES);
			
			mOgreMesh->sharedVertexData->vertexCount = vertexBuffer->getSize();
			Ogre::HardwareVertexBufferSharedPtr buffer = dynamic_cast<VertexBufferOgre *>(vertexBuffer)->_getOgreVertexBuffer();
			mOgreMesh->sharedVertexData->vertexBufferBinding->setBinding(0, buffer);
			//bind->setBinding(0, dynamic_cast<VertexBufferOgre *>(vertexBuffer)->_getOgreVertexBuffer());

			if(indexBuffer)
				subMesh->indexData->indexBuffer = dynamic_cast<IndexBufferOgre *>(indexBuffer)->_getOgreIndexBuffer();

			mOgreMesh->_setBounds(dynamic_cast<VertexBufferOgre *>(vertexBuffer)->_getOgreAABB());
			mOgreMesh->_setBoundingSphereRadius(dynamic_cast<VertexBufferOgre *>(vertexBuffer)->_getOgreRadius());

			mOgreMesh->load();

			/*mOgreMesh = Ogre::MeshManager::getSingleton().createManual(meshName, "AnimaEngine");
			Ogre::SubMesh *subMesh = mOgreMesh->createSubMesh();
			subMesh->indexData->indexCount = indices.size();

			switch(renderOperationType)
			{
				case AE::Graphics::ROT_LINE_LIST: subMesh->operationType = Ogre::RenderOperation::OT_LINE_LIST; break;
				case AE::Graphics::ROT_LINE_STRIP: subMesh->operationType = Ogre::RenderOperation::OT_LINE_STRIP; break;
				case AE::Graphics::ROT_POINT_LIST: subMesh->operationType = Ogre::RenderOperation::OT_POINT_LIST; break;
				case AE::Graphics::ROT_TRIANGLE_FAN: subMesh->operationType = Ogre::RenderOperation::OT_TRIANGLE_FAN; break;
				case AE::Graphics::ROT_TRIANGLE_LIST: subMesh->operationType = Ogre::RenderOperation::OT_TRIANGLE_LIST; break;
				case AE::Graphics::ROT_TRIANGLE_STRIP: subMesh->operationType = Ogre::RenderOperation::OT_TRIANGLE_STRIP; break;
				default: subMesh->operationType = Ogre::RenderOperation::OT_TRIANGLE_LIST; break;
			}
			
			mOgreMesh->sharedVertexData = OGRE_NEW Ogre::VertexData();
			mOgreMesh->sharedVertexData->vertexStart = 0;
			
			Ogre::VertexBufferBinding *bind = mOgreMesh->sharedVertexData->vertexBufferBinding;
			Ogre::VertexDeclaration *decl = mOgreMesh->sharedVertexData->vertexDeclaration;
			
			mOgreMesh->sharedVertexData->vertexCount = vertices.size();
			
			size_t offset = 0;
			decl->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
			offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);

			Ogre::HardwareBuffer::Usage ogreBufferUsage;
			switch(bufferUsage)
			{
				case BU_DYNAMIC: ogreBufferUsage = Ogre::HardwareBuffer::HBU_DYNAMIC; break;
				case BU_DYNAMIC_WRITE_ONLY: ogreBufferUsage = Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY; break;
				case BU_DYNAMIC_WRITE_ONLY_DISCARDABLE: ogreBufferUsage = Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE; break;
				case BU_STATIC: ogreBufferUsage = Ogre::HardwareBuffer::HBU_STATIC; break;
				case BU_STATIC_WRITE_ONLY: ogreBufferUsage = Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY; break;
				case BU_WRITE_ONLY: ogreBufferUsage = Ogre::HardwareBuffer::HBU_WRITE_ONLY; break;
				default: ogreBufferUsage = Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY; break;
			}

			// Allocate memory
			Ogre::HardwareVertexBufferSharedPtr vbuf = 
				Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
					offset, 
					mOgreMesh->sharedVertexData->vertexCount, 
					ogreBufferUsage, 
					useShadowBuffer);
			bind->setBinding(0, vbuf);

			Ogre::AxisAlignedBox meshAABB;
			AE::Real meshRadius = 0;
			Ogre::Vector3 tempVertex;

			float* pFloat = static_cast<float*>(vbuf->lock(Ogre::HardwareBuffer::HBL_DISCARD));
			{
				for(AE::uint i = 0; i < vertices.size(); i++)
				{
					*pFloat++ = vertices[i].x;
					*pFloat++ = vertices[i].y;
					*pFloat++ = vertices[i].z;

					tempVertex.x = vertices[i].x;
					tempVertex.y = vertices[i].y;
					tempVertex.z = vertices[i].z;

					meshAABB.merge(tempVertex);
					meshRadius = std::max(meshRadius, tempVertex.length());
				}
			}
			vbuf->unlock();

			subMesh->indexData->indexBuffer = Ogre::HardwareBufferManager::getSingleton().
				createIndexBuffer(Ogre::HardwareIndexBuffer::IT_16BIT, 
								  subMesh->indexData->indexCount, 
								  ogreBufferUsage, 
								  useShadowBuffer);
			Ogre::HardwareIndexBufferSharedPtr ibuf = subMesh->indexData->indexBuffer;

			unsigned short* pIndexes = static_cast<unsigned short*>(ibuf->lock(Ogre::HardwareBuffer::HBL_DISCARD));
			{
				for(AE::uint i = 0; i < indices.size(); i++)
					*pIndexes++ = indices[i];
			}
			ibuf->unlock();

			mOgreMesh->_setBounds(meshAABB);
			mOgreMesh->_setBoundingSphereRadius(meshRadius);

			mOgreMesh->load();*/
		}
	}
}