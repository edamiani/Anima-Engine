#include "AnimaTestSuite.h"

#include "Anima/AnimaException.h"
#include "Anima/Graphics/Device/AnimaGraphicsDeviceContext.h"
#include "Anima/Graphics/Device/AnimaGraphicsDeviceDriver.h"
#include "Anima/Graphics/Device/AnimaGraphicsDeviceFrameBuffer.h"
#include "Anima/Graphics/Device/GL15/AnimaGraphicsDeviceManagerGL15.h"
#include "Anima/Graphics/Device/AnimaGraphicsDevicePixelBuffer.h"
#include "Anima/Math/AnimaMathPoint2.h"
#include "Anima/OS/AnimaOSWindowListener.h"

#ifdef AE_PLATFORM_WIN32
#	include "Anima/OS/Win/AnimaOSWindowManagerWin.h"
#elif defined AE_PLATFORM_LINUX
#	include "Anima/OS/AnimaOSWindowManagerLinux.h"
#endif

#include "Anima/AnimaPluginManager.h"

#include <cassert>
#include <climits>
#include <cmath>
#include <list>
#include <map>
#include <vector>

class MyWindowListener : public AE::OS::WindowListener
{
public:
	MyWindowListener() : mIsRunning(true) {}
	~MyWindowListener() {}

	bool isRunning() { return mIsRunning; }

	void onClose(AE::OS::Window *window)
	{
		mIsRunning = false;
	}

protected:
	bool mIsRunning;
};

void drawLine(AE::Graphics::Device::PixelBuffer *pixelBuffer, AE::Graphics::Color &color, const AE::Math::Point2<AE::int32> &begin, const AE::Math::Point2<AE::int32> &end)
{
	AE::int32 deltaX = end.x - begin.x;
	AE::int32 deltaY = end.y - begin.y;

	AE::int32 incrX;
	AE::int32 incrY;

	// Horizontal direction
	if(deltaX >= 0) // Running to the right?
	{
		incrX = 1;
	}
	else // Running to the left
	{
		incrX = -1;
		deltaX = -deltaX;
	}

	// Vertical direction
	if(deltaY >= 0)
	{
		// WARNING: Works with OpenGL, but must be inverted when using DirectX
		incrY = 1;
	}
	else
	{
		incrY = -1;
		deltaY = -deltaY;
	}

	AE::int32 error;
	AE::int32 x = begin.x;
	AE::int32 y = begin.y;

	AE::uint32 colorInt = color.getRGBA();

	pixelBuffer->plot(colorInt, AE::Math::Point2<AE::int32>(x, y));

	if(deltaX > deltaY) // Is the line wider than taller?
	{
		error = (2 * deltaY) - deltaX;

		for(int i = 0; i <= deltaX; i++)
		{
			pixelBuffer->plot(colorInt, AE::Math::Point2<AE::int32>(x, y));

			if(error >= 0)
			{
				error -= deltaX * 2;
				y += incrY;
			}

			error += deltaY * 2;
			x += incrX;
		}
	}
	else // The line is taller than wider
	{
		error = (2 * deltaX) - deltaX;

		for(int i = 0; i <= deltaY; i++)
		{
			pixelBuffer->plot(colorInt, AE::Math::Point2<AE::int32>(x, y));

			if(error >= 0)
			{
				error -= deltaY * 2;
				x += incrX;
			}

			error += deltaX * 2;
			y += incrY;
		}
	}
}

void drawCirclePoints(AE::Graphics::Device::PixelBuffer *pixelBuffer, AE::Graphics::Color &color, const AE::Math::Point2<AE::int32> &center, AE::Math::Point2<AE::int32> point)
{
	AE::Math::Point2<AE::int32> drawPoint = point + center;

	//pixelBuffer->plot32( color.get32Bit(), drawPoint );
	point.x *= -1;
	drawPoint = point + center;
	//pixelBuffer->plot32( color.get32Bit(), drawPoint );
	point.y *= -1;
	drawPoint = point + center;
	//pixelBuffer->plot32( color.get32Bit(), drawPoint );
	point.x *= -1;
	drawPoint = point + center;
	//pixelBuffer->plot32( color.get32Bit(), drawPoint );

	drawPoint = point;
	point.x = drawPoint.y;
	point.y = drawPoint.x;

	drawPoint = point + center;
	//pixelBuffer->plot32( color.get32Bit(), drawPoint );
	point.x *= -1;
	drawPoint = point + center;
	//pixelBuffer->plot32( color.get32Bit(), drawPoint );
	point.y *= -1;
	drawPoint = point + center;
	//pixelBuffer->plot32( color.get32Bit(), drawPoint );
	point.x *= -1;
	drawPoint = point + center;
	//pixelBuffer->plot32( color.get32Bit(), drawPoint );
}

void drawCircle(AE::Graphics::Device::PixelBuffer *pixelBuffer, AE::Graphics::Color &color, const AE::Math::Point2<AE::int32> &center, const AE::int32 &radius)
{
	AE::int32 deltaE, deltaSE, d;

	AE::Math::Point2<AE::int32> point(0, radius);

	d = 1 - radius;

	deltaE  = 3;
	deltaSE = -2*radius + 5;

#	define incrementE  ( 2*point.x + 3 );
#	define incrementSE ( 2*(point.x - point.y) + 5 );

	drawCirclePoints( pixelBuffer, color, center, point );

	while ( point.x < point.y )
	{
		if ( d < 0)
		{
			/* Go to E */
			d += incrementE;
			deltaSE += 2;
		}
		else
		{
			/* Go to SE */
			d += incrementSE;
			point.y--;
			deltaSE += 4;
		}

		point.x++;
		deltaE  += 2;

		drawCirclePoints( pixelBuffer, color, center, point );
	}
}

void drawPolygon(AE::Graphics::Device::PixelBuffer *pixelBuffer, AE::Graphics::Color &color, std::vector<AE::Math::Point2<AE::int32>> &points)
{
	for(AE::uint i = 0; i < points.size(); i++)
	{
		if((i + 1) == points.size())
			drawLine(pixelBuffer, color, AE::Math::Point2<AE::int32>(points[i].x, points[i].y), AE::Math::Point2<AE::int32>(points[0].x, points[0].y));
		else
			drawLine(pixelBuffer, color, AE::Math::Point2<AE::int32>(points[i].x, points[i].y), AE::Math::Point2<AE::int32>(points[i + 1].x, points[i + 1].y));
	}
}

struct EdgeTableEntry
{
	AE::int32 maxY;
	AE::int32 minY;
	AE::int32 xFromMinY;
	AE::int32 numerator; // delta X
	AE::int32 denominator; // delta Y
	AE::Real increment;

	EdgeTableEntry() : increment(0) { }
};

bool compareTableEntries(EdgeTableEntry entry1, EdgeTableEntry entry2)
{
	if(entry1.xFromMinY < entry2.xFromMinY)
		return true;
	else
		return false;
}

void drawFilledPolygon(AE::Graphics::Device::PixelBuffer *pixelBuffer, AE::Graphics::Color &color, std::vector<AE::Math::Point2<AE::int32>> &points)
{
	/*std::multimap<AE::int32, std::list<EdgeTableEntry> > edgeTable;

	EdgeTableEntry tableEntry;
	AE::int32 polygonMinY = INT_MAX;
	AE::int32 polygonMaxY = INT_MIN;

	// Table entry insertion
	AE::uint pointsSize = points.size();
	for(AE::uint i = 0; i < pointsSize; i++)
	{
		// Take this point and the next to form an edge;
		// store the highest Y coordinate, the X coordinate
		// from the lowest Y and the slope of the edge.
		if(i != pointsSize - 1)
		{
			if(points[i].y > points[i + 1].y)
			{
				tableEntry.maxY = points[i].y;
				tableEntry.xFromMinY = points[i + 1].x;
				tableEntry.minY = points[i + 1].y;
			}
			else
			{
				tableEntry.maxY = points[i + 1].y;
				tableEntry.xFromMinY = points[i].x;
				tableEntry.minY = points[i].y;
			}

			tableEntry.numerator = (points[i].x - points[i + 1].x);
			tableEntry.denominator = (points[i].y - points[i + 1].y);
		}
		else
		{
			if(points[i].y > points[0].y)
			{
				tableEntry.maxY = points[i].y;
				tableEntry.xFromMinY = points[0].x;
				tableEntry.minY = points[0].y;
			}
			else
			{
				tableEntry.maxY = points[0].y;
				tableEntry.xFromMinY = points[i].x;
				tableEntry.minY = points[i].y;
			}

			tableEntry.numerator = (points[i].x - points[0].x);
			tableEntry.denominator = (points[i].y - points[0].y);
		}

		// Unordered insertion of table entry into the edge table
		//edgeTable[tableEntry.minY].push_back(tableEntry);
		edgeTable.insert(std::pair<AE::int32, EdgeTableEntry>(tableEntry.minY, tableEntry));

		if(tableEntry.minY < polygonMinY)
			polygonMinY = tableEntry.minY;

		if(tableEntry.maxY > polygonMinY)
			polygonMaxY = tableEntry.maxY;
	}

	// Edge sort
	std::multimap<AE::int32, std::list<EdgeTableEntry> >::iterator it = edgeTable.begin();
	for(it; it != edgeTable.end(); it++)
	{
		(*it).second.sort(compareTableEntries);
	}

	std::list<EdgeTableEntry> activeEdgeTable;

	// Edge table traversal using AET
	for(AE::int32 y = polygonMinY; y < polygonMaxY; y++)
	{
		// Is there an edge in this row?
		if(edgeTable.find(y) != edgeTable.end())
		{
			// Move from ET bucket i to the AET those edges whose yMin = i (entering edges)
			std::list<EdgeTableEntry>::iterator it = edgeTable[y].begin();
			for(it; it != edgeTable[y].end(); it++)
			{
				//if((*it).minY == y)
					activeEdgeTable.push_back(*it);
			}

			// Remove from the AET those entries for which yMax = i (edges not involved in the
			// next scan line),...
			it = activeEdgeTable.begin();
			for(it; it != activeEdgeTable.end(); it++)
			{
				if((*it).maxY == y)
					activeEdgeTable.erase(it);
			}

			// ... then sort the AET on x.
			activeEdgeTable.sort(compareTableEntries);

			// Fill in desired pixel values on scan line y by using pairs of x coordinates from the AET
			it = activeEdgeTable.begin();
			EdgeTableEntry previousEntry = *it;
			it++;
			for(it; it != activeEdgeTable.end(); it++)
			{
				for(int curX = previousEntry.xFromMinY; curX < (*it).xFromMinY; curX++)
					surface->plot32(color.get32Bit(), AE::Math::Point2(curX, y));
			}

			// Increment slopes
			it = activeEdgeTable.begin();
			for(it; it != activeEdgeTable.end(); it++)
			{
				(*it).increment += (*it).numerator;
				if(abs((*it).increment) > abs((*it).denominator))
				{
					if((*it).numerator >= 0)
						(*it).xFromMinY++;
					else
						(*it).xFromMinY--;

					(*it).increment -= (*it).denominator;
				}
			}
		}
	}*/


	// Find the highest Y coordinate
	AE::int32 topY = points[0].y;
	for(AE::uint i = 1; i < points.size(); i++)
	{
		if(points[i].y > topY)
			topY = points[i].y;
	}

	// Find the lowest Y coordinate
	AE::int32 bottomY = points[0].y;
	for(AE::uint i = 1; i < points.size(); i++)
	{
		if(points[i].y < bottomY)
			bottomY = points[i].y;
	}

	// Find the leftmost X coordinate
	AE::int32 leftX = points[0].x;
	for(AE::uint i = 1; i < points.size(); i++)
	{
		if(points[i].x < leftX)
			leftX = points[i].x;
	}

	// Find the rightmost X coordinate
	AE::int32 rightX = points[0].x;
	for(AE::uint i = 1; i < points.size(); i++)
	{
		if(points[i].x > rightX)
			rightX = points[i].x;
	}

	//  Loop through the rows of the image.
	for (AE::int32 currentY = topY; currentY > bottomY; currentY--)
	{
		//  Build a list of nodes.
		AE::uint polyCorners = points.size();
		AE::int32 nodeX[50];
		AE::uint i;
		AE::uint j = polyCorners - 1;
		AE::uint nodes = 0;
		for (i = 0; i < polyCorners; i++)
		{
			if (points[i].y <= currentY && points[j].y >= currentY ||
				points[j].y <= currentY && points[i].y >= currentY)
			{
				float proportionalDeltaY = static_cast<float>(currentY - points[i].y);
				float deltaY = static_cast<float>(points[j].y - points[i].y);
				//float division = proportionalDeltaY / deltaY;
				float division;
				if(deltaY == 0)
				{
					//division = 0;
					j = i;
					continue;
				}
				else
					division = proportionalDeltaY / deltaY;
				float deltaX = static_cast<float>(points[j].x - points[i].x);
				nodeX[nodes++] = (int) (points[i].x + division * deltaX);
			}
			j = i;
		}

		//  Sort the nodes, via a simple “Bubble” sort.
		AE::int32 swap;
		i = 0;
		while(i < nodes - 1)
		{
			if(nodeX[i] > nodeX[i + 1])
			{
				swap = nodeX[i];
				nodeX[i] = nodeX[i + 1];
				nodeX[i + 1] = swap;
				if (i) i--;
			}
			else
			{
				i++;
			}
		}

		//  Fill the pixels between node pairs.
		for(i = 0; i < nodes; i += 2)
		{
			//if(nodeX[i] >= rightX)
				//break;

			//if(nodeX[i+1] > leftX)
			//{
			//	if (nodeX[i] < leftX)
			//		nodeX[i] = leftX;

			//	if (nodeX[i+1] > rightX)
			//		nodeX[i+1] = rightX;
			AE::int32 firstNode = i;
			AE::int32 secondNode;
			if(i == nodes - 1)
				secondNode = 0;
			else
				secondNode = i + 1;
			for (j = nodeX[firstNode]; j <= nodeX[secondNode]; j++)
				;//pixelBuffer->plot32(color.get32Bit(), AE::Math::Point2(j, currentY));
			//}
		}
	}
}

void ExampleTestSuite::plotTest()
{
	AE::PluginManager *pluginManager = AE::PluginManager::initialize();

#ifdef AE_PLATFORM_WIN32
	AE::OS::WindowManager *windowManager = static_cast<AE::OS::WindowManager *>(pluginManager->registerPlugin("windowManager", new AE::OS::WindowManagerWin()));
#else
	AE::OS::WindowManager *windowManager = static_cast<AE::OS::WindowManager *>(pluginManager->registerPlugin("windowManager", new AE::OS::WindowManagerLinux()));
#endif
	pluginManager->getRoot()->attach(windowManager);

	assert(windowManager);
	windowManager->install(AE::NO_OPTIONS);

	AE::OS::WindowDesc windowDesc;
	windowDesc.dimensions = AE::Math::Point2<AE::uint>(640, 480);
	windowDesc.position = AE::Math::Point2<AE::int32>(100, 100);
	AE::OS::Window *window = windowManager->createWindow("Plot Test", windowDesc);

	MyWindowListener myWindowListener;
	AE::OS::EventQueue *eventQueue = windowManager->getEventQueue();
	eventQueue->registerWindowListener(&myWindowListener);

	AE::Graphics::Device::Manager *deviceManager;
	AE::Graphics::Device::Driver *deviceDriver;

#ifdef AE_PLATFORM_WIN32
	deviceManager = static_cast<AE::Graphics::Device::Manager *>(pluginManager->registerPlugin("deviceManagerGL15", new AE::Graphics::Device::ManagerGL15()));
	deviceManager->install(0);
	deviceDriver = deviceManager->acquireDeviceDriver(0, AE::Graphics::Device::DT_GL_15);
#else
	deviceManager = static_cast<AE::Graphics::Device::Manager *>(pluginManager->registerPlugin("deviceManagerGL15", new AE::Graphics::Device::ManagerGL15()));
	deviceManager->install(0);
	deviceDriver = deviceManager->acquireDeviceDriver(0, AE::Graphics::Device::DT_OPENGL1_5);
#endif

	AE::Graphics::Device::ContextDesc contextDesc;
	contextDesc.dimensions = window->getDimensions();
	contextDesc.fullScreen = false;
	contextDesc.parentWindow = window;
	contextDesc.setColorFormat(AE::Graphics::CF_R8G8B8A8);

	AE::Graphics::Device::Context *deviceContext = deviceDriver->createDeviceContext(contextDesc);

	window->show();

	AE::Graphics::Color red(255, 0, 0);
	AE::Graphics::Color green(0, 255, 0);
	AE::Graphics::Color blue(0, 0, 255);
	AE::Graphics::Color black(0, 0, 0);
	AE::Graphics::Color white(255, 255, 255);

#define VERTICES 0 
#define INDICES 1 
#define NUM_BUFFERS 2

#define BUFFER_OFFSET(i) ((void*)(i))

	GLuint buffers[NUM_BUFFERS];
	/*GLfloat vertices[][3] =
	{
	{ -1.0, -1.0, -1.0 },
	{ 1.0, -1.0, -1.0 },
	{ 1.0, 1.0, -1.0 },
	{ -1.0, 1.0, -1.0 },
	{ -1.0, -1.0, 1.0 },
	{ 1.0, -1.0, 1.0 },
	{ 1.0, 1.0, 1.0},
	{ -1.0, 1.0, 1.0 },
	};*/
	GLfloat vertices[][3] =
	{
		{ 100.0, 100.0, 0.0 },
		{ 100.0, 200.0, 0.0 },
		{ 0.0, 200.0, 0.0 },
		{ 0.0, 100.0, 0.0}
	};

	/*GLubyte indices[][4] =
	{
	{ 0, 1, 2, 3 },
	{ 4, 7, 6, 5 },
	{ 0, 4, 5, 1 },
	{ 3, 2, 6, 7 },
	{ 0, 3, 7, 4 },
	{ 1, 5, 6, 2 }
	};*/

	GLubyte indices[] =
	{
		0, 1, 2, 2, 3, 0
	};

	GLfloat colors[] = { 1, 1, 1,   1, 1, 0,   1, 0, 0, };

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);

	glGenBuffers(NUM_BUFFERS, buffers);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[VERTICES]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[INDICES]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	while(myWindowListener.isRunning())
	{
		deviceContext->beginRendering(black);

		AE::Graphics::Device::FrameBuffer *frameBuffer = deviceContext->getFrameBuffer();
		frameBuffer->lock(AE::Graphics::LT_DISCARD);
		//frameBuffer->clear(red);

		frameBuffer->plot(green.getRGBA(), AE::Math::Point2<AE::int32>(100, 100));
		drawLine(frameBuffer, white, AE::Math::Point2<AE::int32>(50, 50), AE::Math::Point2<AE::int32>(100, 50));
		drawLine(frameBuffer, red, AE::Math::Point2<AE::int32>(101, 51), AE::Math::Point2<AE::int32>(150, 100));
		drawLine(frameBuffer, blue, AE::Math::Point2<AE::int32>(151, 101), AE::Math::Point2<AE::int32>(250, 50));
		
		//glBegin(GL_POLYGON);            // These vertices form a closed polygon
		//glColor3f(1.0f, 1.0f, 0.0f); // Yellow
		//glVertex2f(300.f, 100.f);
		//glVertex2f(300.f, 300.f);
		//glVertex2f(100, 100);
		//glEnd();

		glBindBuffer(GL_ARRAY_BUFFER, buffers[VERTICES]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[INDICES]);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));

		//glDrawElements(GL_QUADS, 1, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_BYTE, 0);

		glDisableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		//std::vector<AE::Math::Point2<AE::int32>> points;
		//points.push_back(AE::Math::Point2<AE::int32>(400, 200));
		//points.push_back(AE::Math::Point2<AE::int32>(403, 200));
		//points.push_back(AE::Math::Point2<AE::int32>(406, 203));
		//points.push_back(AE::Math::Point2<AE::int32>(403, 206));
		//points.push_back(AE::Math::Point2<AE::int32>(400, 206));
		//points.push_back(AE::Math::Point2<AE::int32>(397, 203));
		//drawPolygon(frameBuffer, white, points);

		//std::vector<AE::Math::Point2<AE::int32>> points2;
		///*points2.push_back(AE::Math::Point2(2, 3));
		//points2.push_back(AE::Math::Point2(7, 1));
		//points2.push_back(AE::Math::Point2(13, 5));
		//points2.push_back(AE::Math::Point2(13, 11));
		//points2.push_back(AE::Math::Point2(7, 7));
		//points2.push_back(AE::Math::Point2(2, 9));*/
		///*points2.push_back(AE::Math::Point2(50, 50));
		//points2.push_back(AE::Math::Point2(30, 30));
		//points2.push_back(AE::Math::Point2(70, 30));*/
		//points2.push_back(AE::Math::Point2<AE::int32>(200, 200));
		//points2.push_back(AE::Math::Point2<AE::int32>(300, 200));
		//points2.push_back(AE::Math::Point2<AE::int32>(350, 275));
		//points2.push_back(AE::Math::Point2<AE::int32>(300, 350));
		//points2.push_back(AE::Math::Point2<AE::int32>(200, 350));
		//points2.push_back(AE::Math::Point2<AE::int32>(150, 275));
		//drawFilledPolygon(frameBuffer, white, points2);

		//drawCircle(frameBuffer, blue, AE::Math::Point2<AE::int32>(320, 240), AE::int32(5) );
		//drawCircle(frameBuffer, red, AE::Math::Point2<AE::int32>(320, 240), AE::int32(10));
		//drawCircle(frameBuffer, red, AE::Math::Point2<AE::int32>(320, 240), AE::int32(15));
		//drawCircle(frameBuffer, red, AE::Math::Point2<AE::int32>(320, 240), AE::int32(20));
		//drawCircle(frameBuffer, red, AE::Math::Point2<AE::int32>(320, 240), AE::int32(25));
		//drawCircle(frameBuffer, red, AE::Math::Point2<AE::int32>(320, 240), AE::int32(30));
		//drawCircle(frameBuffer, red, AE::Math::Point2<AE::int32>(320, 240), AE::int32(35));
		//drawCircle(frameBuffer, red, AE::Math::Point2<AE::int32>(320, 240), AE::int32(40));
		//drawCircle(frameBuffer, red, AE::Math::Point2<AE::int32>(320, 240), AE::int32(45));
		//drawCircle(frameBuffer, blue, AE::Math::Point2<AE::int32>(320, 240), AE::int32(50));

		frameBuffer->unlock();

		deviceContext->endRendering();

		eventQueue->getNextEvent(0);
	}

	pluginManager->shutdown();
}
