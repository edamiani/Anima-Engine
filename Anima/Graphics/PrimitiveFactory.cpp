#include "../include/AnimaGraphicsPrimitiveFactory.h"
#include "../include/AnimaGraphicsManager.h"

AE::Graphics::PrimitiveFactory* AE::Graphics::PrimitiveFactory::mInstance = 0;

namespace AE
{
	namespace Graphics
	{
		PrimitiveFactory::PrimitiveFactory()
		{
			mGraphicsManager = AE::Graphics::Manager::getInstance();
		}

		AE::Graphics::PrimitiveFactory* PrimitiveFactory::initialize()
		{
			return 0;
		}

		void PrimitiveFactory::shutdown()
		{
		}

		AE::Graphics::Mesh* PrimitiveFactory::createCube(AE::Math::Vector3 &position, AE::Math::Vector3 &size)
		{
			/*Ogre::Real scaleX = 1 / size.x;
			Ogre::Real scaleY = 1 / size.y;
			Ogre::Real scaleZ = 1 / size.z;

			Ogre::String meshName(Ogre::String("Mesh") + Ogre::String(Ogre::StringConverter::toString(mMeshCount)));
			mMeshCount++;

			Ogre::Vector3 positionVec(position.x, position.y, position.z);
			Ogre::Entity *entity = mSceneManager->createEntity(meshName, "AnimaCubeMesh", "AnimaEngine");
			Ogre::SceneNode *node = mSceneManager->getRootSceneNode()->createChildSceneNode(meshName, positionVec);
			node->attachObject(entity);
			node->scale(size.x, size.y, size.z);*/

			return 0;
		}

		AE::Graphics::Mesh* PrimitiveFactory::createCone(AE::Math::Vector3 &position, AE::Math::Vector3 &size, AE::Real bottomRadius, AE::Real height, bool drawSide, bool drawBottom, bool doubleSided)
		{
			return 0;
		}

		AE::Graphics::Mesh* PrimitiveFactory::createGrid(int m, int n, float gridSize)
		{
			/*Ogre::ManualObject* myManualObject =  mSceneManager->createManualObject("manual1"); 
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
			
			myManualObjectNode->attachObject(myManualObject);*/

			return 0;
		}

		AE::Graphics::Mesh* createSphere(AE::Math::Vector3 &position, AE::Math::Vector3 &size)
		{
			return 0;
		}

		void PrimitiveFactory::_createBottomlessInnerConeMesh()
		{
			/*AE::Real bottomRadius = 1;
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
					indices.push_back(0); indices.push_back(vertexIndex); indices.push_back(vertexIndex + 1);
				else
					indices.push_back(0); indices.push_back(vertexIndex); indices.push_back(1);
			}

			AE::Graphics::VertexBufferDesc vertexBufferDesc;
			vertexBufferDesc.positions = vertices;
			AE::Graphics::VertexBufferOgre vb = static_cast<VertexBufferOgre *>(createVertexBuffer("AnimaBottomlessInnerConeVB", vertexBufferDesc));
			AE::Graphics::IndexBufferOgre ib = static_cast<IndexBufferOgre *>(createIndexBuffer("AnimaBottomlessInnerConeIB", indices, AE::Graphics::BU_STATIC_WRITE_ONLY, false));
			mBottomlessInnerConeMesh = static_cast<MeshOgre *>(createMesh("AnimaBottomlessInnerConeMesh", vb, ib, AE::Graphics::ROT_TRIANGLE_LIST));*/
		}

		void PrimitiveFactory::_createBottomlessOuterConeMesh()
		{
			/*AE::Real bottomRadius = 1;
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
			mBottomlessOuterConeMesh = static_cast<MeshOgre *>(createMesh("AnimaBottomlessOuterConeMesh", vb, ib, AE::Graphics::ROT_TRIANGLE_LIST));*/
		}

		void PrimitiveFactory::_createCubeMesh()
		{
			/*std::vector<AE::Math::Vector3> positions;
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

			mCubeMesh = static_cast<MeshOgre *>(createMesh(std::string("AnimaCubeMesh"), vertexBuffer, indexBuffer, ROT_TRIANGLE_LIST));*/
		}

		void PrimitiveFactory::_createOneSidedLowerDiscMesh()
		{
			/*AE::Real radius = 1;
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
			mOneSidedLowerDiscMesh = static_cast<MeshOgre *>(createMesh("AnimaOneSidedLowerDiscMesh", vb, ib, AE::Graphics::ROT_TRIANGLE_LIST));*/
		}

		void PrimitiveFactory::_createOneSidedUpperDiscMesh()
		{
			/*AE::Real radius = 1;
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
			mOneSidedUpperDiscMesh = static_cast<MeshOgre *>(createMesh("AnimaOneSidedUpperDiscMesh", vb, ib, AE::Graphics::ROT_TRIANGLE_LIST));*/
		}

		void PrimitiveFactory::_createOpenInnerCylinderMesh()
		{
			/*AE::Real radius = 1.f;
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
			mOpenInnerCylinderMesh = static_cast<MeshOgre *>(createMesh("AnimaOpenInnerCylinderMesh", vb, ib, AE::Graphics::ROT_TRIANGLE_LIST));*/
		}

		void PrimitiveFactory::_createOpenOuterCylinderMesh()
		{
			/*AE::Real radius = 1.f;
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
			mOpenOuterCylinderMesh = static_cast<MeshOgre *>(createMesh("AnimaOpenOuterCylinderMesh", vb, ib, AE::Graphics::ROT_TRIANGLE_LIST));*/
		}

		void PrimitiveFactory::_createSphereMesh()
		{
			/*AE::Real radius = 1.f;
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
			mSphereMesh = static_cast<MeshOgre *>(createMesh("AnimaSphereMesh", vb, ib, AE::Graphics::ROT_TRIANGLE_LIST));*/
		}
	}
}