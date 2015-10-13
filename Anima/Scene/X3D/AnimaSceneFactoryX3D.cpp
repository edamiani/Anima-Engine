#include "../include/AnimaSceneFactoryX3D.h"

#include "../include/AnimaGraphicsIndexBuffer.h"
#include "../include/AnimaGraphicsManager.h"
#include "../include/AnimaGraphicsMesh.h"
#include "../include/AnimaGraphicsVertexBuffer.h"

namespace AE
{
	namespace Scene
	{
		AE::Graphics::Indices* FactoryX3D::bakeRendererIndices(AE::Scene::MeshType meshType, AE::Graphics::Indices *indices)
		{
			switch(meshType)
			{
			case AE::Scene::MT_POINT_SET:
			case AE::Scene::MT_TRIANGLE_FAN_SET:
			case AE::Scene::MT_TRIANGLE_SET:
			case AE::Scene::MT_TRIANGLE_STRIP_SET:
				// No changes needed
				break;
			case AE::Scene::MT_INDEXED_LINE_SET:
				indices = _bakeRendererIndicesFromIndexedLineSet(indices);
			case AE::Scene::MT_INDEXED_TRIANGLE_FAN_SET:
				indices = _bakeRendererIndicesFromIndexedTriangleFanSet(indices);
			case AE::Scene::MT_INDEXED_TRIANGLE_SET:
				indices = _bakeRendererIndicesFromIndexedTriangleSet(indices);
			case AE::Scene::MT_INDEXED_TRIANGLE_STRIP_SET:
				indices = _bakeRendererIndicesFromIndexedTriangleStripSet(indices);
			}

			return indices;
		}

		AE::Scene::ShapeNode* FactoryX3D::createShapeNode(AE::Graphics::Mesh *mesh, AE::Scene::GroupingNode *parentNode)
		{
			AE::Scene::ShapeNode *node = new AE::Scene::ShapeNode(mesh, parentNode);
			return node;
		}

		AE::Graphics::Indices* FactoryX3D::_bakeRendererIndicesFromIndexedLineSet(AE::Graphics::Indices *indices)
		{
			AE::Graphics::Indices::iterator i = indices->begin() + 1; // Starts at the second element
			
			while(i != indices->end())
			{
				if(*i == -1) // Transition from a polyline to another (or the vector's last element)
				{
					// Just delete this index
					i = indices->erase(i);

					// No need to increment the loop here, since erase() returns the next element
				}
				else
				{
					if((i + 1) != indices->end()) // Not the vector's last element
					{
						if(*(i + 1) != -1) // Next element is not a line break
							// Duplicate the index (since the polyline, represented by a line list,
							// must be built as a list of adjacent lines)
							indices->insert(i, *i);
					}

					i++; // Manually increment the loop
				}
			}

			return indices;
			
			//mFramework->getGraphicsManager()->createMesh(name, vb, ib, AE::Graphics::ROT_LINE_LIST);
		}

		AE::Graphics::Indices* FactoryX3D::_bakeRendererIndicesFromIndexedTriangleFanSet(AE::Graphics::Indices *indices)
		{
			AE::Graphics::Indices::iterator i = indices->begin() + 3; // Starts at the fourth element
			AE::Graphics::Indices::iterator firstElement = indices->begin();

			while(i != indices->end())
			{
				if(*i == -1) // Transition from a fan to another (or the vector's last element)
				{
					// Delete this element and jump to the fourth element after him
					i = indices->erase(i);
					if(i != indices->end())
					{
						firstElement = i;
						i += 3;
					}
				}
				else
				{
					indices->insert(i, *firstElement);
					indices->insert(i, *(i - 1));
					i++;
				}
			}

			return indices;
			
			//mFramework->getGraphicsManager()->createMesh(name, vb, ib, AE::Graphics::ROT_TRIANGLE_LIST);
		}

		AE::Graphics::Indices* FactoryX3D::_bakeRendererIndicesFromIndexedTriangleSet(AE::Graphics::Indices *indices)
		{
			AE::ushort remainder = indices->size() % 3;
			AE::Graphics::Indices::iterator i = indices->end() - remainder;
			
			for(int j = 0; j < remainder; j++)
				i = indices->erase(i);

			return indices;
			
			//mFramework->getGraphicsManager()->createMesh(name, vb, ib, AE::Graphics::ROT_TRIANGLE_LIST);
		}

		AE::Graphics::Indices* FactoryX3D::_bakeRendererIndicesFromIndexedTriangleStripSet(AE::Graphics::Indices *indices)
		{
			AE::Graphics::Indices::iterator i = indices->begin() + 3; // Starts at the fourth element

			bool inOrder = false; // Needed to invert the order of vertices stored for a triangle
			while(i != indices->end())
			{
				if(*i == -1) // Transition from a strip to another (or the vector's last element)
				{
					/* Delete this index and jump to the fourth element after it */
					i = indices->erase(i);
					if(i != indices->end())
						i += 3;
					inOrder = false;
				}
				else
				{
					if(inOrder)
					{
						indices->insert(i, *(i - 2));
						indices->insert(i, *(i - 1));
					}
					else
					{
						indices->insert(i, *(i - 1));
						indices->insert(i, *(i - 2));
					}
					inOrder = !inOrder;
					
					i++;
				}
			}

			return indices;
			
			//mFramework->getGraphicsManager()->createMesh(name, vb, ib, AE::Graphics::ROT_TRIANGLE_LIST);
		}
	}
}