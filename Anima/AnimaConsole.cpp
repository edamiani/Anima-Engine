#include "../include/AnimaConsole.h"

#include "../include/AnimaGraphicsColor.h"
#include "../include/AnimaGraphicsDeviceManager.h"
#include "../include/AnimaGraphicsDevicePixelBuffer.h"
#include "../include/AnimaGraphicsDevicePixelBufferDesc.h"
#include "../include/AnimaGraphicsDevicePixelBufferFactory.h"
#include "../include/AnimaMathPoint2.h"
#include "../include/AnimaOSWindow.h"

namespace AE
{
	Console::Console(const AE::ConsoleDesc &consoleDesc)
		: mBackgroundColor(consoleDesc.backgroundColor),
		  mConsoleStyle(consoleDesc.consoleStyle),
		  mDimensionsInCharacters(consoleDesc.dimensionsInCharacters),
		  mDimensionsInPixels(consoleDesc.dimensionsInPixels),
		  mForegroundColor(consoleDesc.foregroundColor)
	{
		mCharacterMatrix = malloc(mDimensionsInCharacters.x * mDimensionsInCharacters.y);

		AE::Graphics::Device::PixelBufferDesc pixelBufferDesc;
		pixelBufferDesc.colorBufferDesc.dimensions = mDimensionsInPixels;
		pixelBufferDesc.colorBufferDesc.colorFormat = consoleDesc.colorFormat;

		mPixelBuffer = AE::Graphics::Device::Manager::getInstance()->getPixelBufferFactory()->createPixelBuffer(pixelBufferDesc);
		//mPixelBuffer->clear(mBackgroundColor);
	}

	Console::~Console() {}
}
