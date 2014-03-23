#include "cpptest.h"

class ExampleTestSuite : public Test::Suite
{
public:
	ExampleTestSuite()
	{
		//TEST_ADD(ExampleTestSuite::windowTest);
		//TEST_ADD(ExampleTestSuite::windowAndContextTest);
		//TEST_ADD(ExampleTestSuite::plotTest);
		//TEST_ADD(ExampleTestSuite::simpleImageTest);
		//TEST_ADD(ExampleTestSuite::imageTest);
		//TEST_ADD(ExampleTestSuite::consoleTest);
		//TEST_ADD(ExampleTestSuite::drawingTest);
		TEST_ADD(ExampleTestSuite::sceneHierarchyTest);
		//TEST_ADD(ExampleTestSuite::MVCTest);
		//TEST_ADD(ExampleTestSuite::paintingTest);
		//TEST_ADD(ExampleTestSuite::gpuTest);
		//TEST_ADD(ExampleTestSuite::monitorAndVideoInfoTest);
		//TEST_ADD(ExampleTestSuite::guiTest);
	}

	~ExampleTestSuite(){}

private:
	void consoleTest();
	//void drawingTest();
	//void gpuTest();
	//void guiTest();
	void imageTest();
	//void monitorAndVideoInfoTest();
	void MVCTest();
	void paintingTest();
	void plotTest();
	void scalingTest();
	void sceneHierarchyTest();
	void simpleImageTest();
	void windowAndContextTest();
	void windowTest();
	void windowToViewportTest();
};
