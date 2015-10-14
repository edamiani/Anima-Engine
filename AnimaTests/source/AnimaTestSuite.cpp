#include "AnimaTestSuite.h"

#include "Anima/AnimaPlatform.h"

#include <stdlib.h>
#include <fstream>

#ifdef AE_PLATFORM_WIN32
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT)
#else
int main()
#endif
{
	ExampleTestSuite exampleTestSuite;
	std::ofstream ofile;
	ofile.open("test.log");
	Test::CompilerOutput output(Test::CompilerOutput::MSVC, ofile);
	return exampleTestSuite.run(output) ? EXIT_SUCCESS : EXIT_FAILURE;
}
