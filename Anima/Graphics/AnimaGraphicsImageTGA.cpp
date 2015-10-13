#include "../include/AnimaGraphicsImageTGA.h"
#include "../include/AnimaGraphicsEnums.h"
#include "../include/AnimaGraphicsManager.h"
#include "../include/AnimaMathPoint2.h"

#include <cassert>
#include <fstream>

namespace AE
{
	namespace Graphics
	{
		ImageTGA::~ImageTGA() 
		{ 
			if(mSurface)
			{
				AE::Graphics::Manager::getInstance()->destroySurface(mSurface); 
				mSurface = 0;
			}
		}

		void ImageTGA::load(const std::string &fileName)
		{
			std::ifstream file(fileName.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
			assert(file.is_open());
			long size;
			size = file.tellg();
			char *memBlock = new char[static_cast<AE::uint>(size)];
			char *memBlockBOF = memBlock;
			file.seekg(0, std::ios::beg);
			file.read(memBlock, size);
			file.close();

			memcpy(&mTgaSpec._a_header._01_idLength, memBlock, 1); memBlock ++;
			memcpy(&mTgaSpec._a_header._02_colorMapType, memBlock, 1); memBlock ++;
			memcpy(&mTgaSpec._a_header._03_imageType, memBlock, 1); memBlock ++;

			memcpy(&mTgaSpec._a_header._04_colorMapSpecification._01_firstEntryIndex, memBlock, 2); memBlock += 2;
			memcpy(&mTgaSpec._a_header._04_colorMapSpecification._02_colorMapLength, memBlock, 2); memBlock += 2;
			memcpy(&mTgaSpec._a_header._04_colorMapSpecification._03_colorMapEntrySize, memBlock, 1); memBlock ++;

			memcpy(&mTgaSpec._a_header._05_imageSpecification._01_xOrigin, memBlock, 2); memBlock += 2;
			memcpy(&mTgaSpec._a_header._05_imageSpecification._02_yOrigin, memBlock, 2); memBlock += 2;
			memcpy(&mTgaSpec._a_header._05_imageSpecification._03_imageWidth, memBlock, 2); memBlock += 2;
			memcpy(&mTgaSpec._a_header._05_imageSpecification._04_imageHeight, memBlock, 2); memBlock += 2;
			memcpy(&mTgaSpec._a_header._05_imageSpecification._05_pixelDepth, memBlock, 1); memBlock ++;
			memcpy(&mTgaSpec._a_header._05_imageSpecification._06_imageDescriptor, memBlock, 1); memBlock ++;

			if(mTgaSpec._a_header._01_idLength != 0)
			{
				mTgaSpec._b_imageAndColorMapData._06_imageId = new AE::int8[mTgaSpec._a_header._01_idLength];
				memcpy(mTgaSpec._b_imageAndColorMapData._06_imageId, memBlock, mTgaSpec._a_header._01_idLength);
				memBlock += mTgaSpec._a_header._01_idLength;
			}

			if(mTgaSpec._a_header._02_colorMapType == 1)
			{
				mTgaSpec._b_imageAndColorMapData._07_colorMapData = new AE::uint8[mTgaSpec._a_header._04_colorMapSpecification._02_colorMapLength];
				memcpy(mTgaSpec._b_imageAndColorMapData._07_colorMapData, memBlock, mTgaSpec._a_header._04_colorMapSpecification._02_colorMapLength);
				memBlock += mTgaSpec._a_header._02_colorMapType;
			}

			AE::uint32 imageSize = mTgaSpec._a_header._05_imageSpecification._03_imageWidth *
								   mTgaSpec._a_header._05_imageSpecification._04_imageHeight *
								   (mTgaSpec._a_header._05_imageSpecification._05_pixelDepth / 8);
			mTgaSpec._b_imageAndColorMapData._08_imageData = new AE::uint8[imageSize];
			memcpy(mTgaSpec._b_imageAndColorMapData._08_imageData, memBlock, imageSize);
			memBlock += imageSize;

			memcpy(mTgaSpec._e_footer._28_extensionAreaOffset, memBlock, 4); memBlock += 4;
			memcpy(mTgaSpec._e_footer._29_developerDirectoryOffset, memBlock, 4); memBlock += 4;
			memcpy(mTgaSpec._e_footer._30_signature, memBlock, 16); memBlock += 16;
			memcpy(&mTgaSpec._e_footer._31_reservedCharacter, memBlock, 1); memBlock++;
			memcpy(&mTgaSpec._e_footer._32_binaryZeroStringTerminator, memBlock, 1); memBlock++;

			delete [] memBlockBOF;

			AE::Graphics::SurfaceFormat surfaceFormat;
			if(mTgaSpec._a_header._05_imageSpecification._05_pixelDepth == 32)
				surfaceFormat = AE::Graphics::SF_A8R8G8B8;
			else if(mTgaSpec._a_header._05_imageSpecification._05_pixelDepth == 24)
				surfaceFormat = AE::Graphics::SF_X8R8G8B8;
			else if(mTgaSpec._a_header._05_imageSpecification._05_pixelDepth == 16)
				surfaceFormat = AE::Graphics::SF_A1R5G5B5;
			else if(mTgaSpec._a_header._05_imageSpecification._05_pixelDepth == 15)
				surfaceFormat = AE::Graphics::SF_X1R5G5B5;
			else
				assert(0 && "TGA: unknown pixel depth");

			mSurface = AE::Graphics::Manager::getInstance()->createSurface(mTgaSpec._a_header._05_imageSpecification._03_imageWidth,
																mTgaSpec._a_header._05_imageSpecification._04_imageHeight,
																surfaceFormat);
			mSurface->lock(AE::Graphics::LT_DISCARD);
				mSurface->blit(static_cast<void *>(mTgaSpec._b_imageAndColorMapData._08_imageData),
													AE::Math::Point2(mTgaSpec._a_header._05_imageSpecification._03_imageWidth, mTgaSpec._a_header._05_imageSpecification._04_imageHeight), 
													AE::Math::Point2(0, 0));
			mSurface->unlock();
		}

		void ImageTGA::save(const std::string &fileName)
		{
			AE::uint32 fullSize = 18; // Starts with header size
			fullSize += mTgaSpec._a_header._01_idLength;
			fullSize += mTgaSpec._a_header._04_colorMapSpecification._02_colorMapLength;
			AE::uint32 imageSize = mTgaSpec._a_header._05_imageSpecification._03_imageWidth *
								   mTgaSpec._a_header._05_imageSpecification._04_imageHeight *
								   (mTgaSpec._a_header._05_imageSpecification._05_pixelDepth / 8);
			fullSize += imageSize;
			fullSize += 26; // Footer size
			char *memBlock = new char[fullSize];
			char *memBlockBOF = memBlock;

			memcpy(memBlock, &mTgaSpec._a_header._01_idLength, 1); memBlock ++;
			memcpy(memBlock, &mTgaSpec._a_header._02_colorMapType, 1); memBlock ++;
			memcpy(memBlock, &mTgaSpec._a_header._03_imageType, 1); memBlock ++;

			memcpy(memBlock, &mTgaSpec._a_header._04_colorMapSpecification._01_firstEntryIndex, 2); memBlock += 2;
			memcpy(memBlock, &mTgaSpec._a_header._04_colorMapSpecification._02_colorMapLength, 2); memBlock += 2;
			memcpy(memBlock, &mTgaSpec._a_header._04_colorMapSpecification._03_colorMapEntrySize, 1); memBlock ++;

			memcpy(memBlock, &mTgaSpec._a_header._05_imageSpecification._01_xOrigin, 2); memBlock += 2;
			memcpy(memBlock, &mTgaSpec._a_header._05_imageSpecification._02_yOrigin, 2); memBlock += 2;
			memcpy(memBlock, &mTgaSpec._a_header._05_imageSpecification._03_imageWidth, 2); memBlock += 2;
			memcpy(memBlock, &mTgaSpec._a_header._05_imageSpecification._04_imageHeight, 2); memBlock += 2;
			memcpy(memBlock, &mTgaSpec._a_header._05_imageSpecification._05_pixelDepth, 1); memBlock ++;
			memcpy(memBlock, &mTgaSpec._a_header._05_imageSpecification._06_imageDescriptor, 1); memBlock ++;

			if(mTgaSpec._a_header._01_idLength != 0)
			{
				memcpy(memBlock, mTgaSpec._b_imageAndColorMapData._06_imageId, mTgaSpec._a_header._01_idLength);
				memBlock += mTgaSpec._a_header._01_idLength;
			}

			if(mTgaSpec._a_header._02_colorMapType != 0)
			{
				memcpy(memBlock, mTgaSpec._b_imageAndColorMapData._07_colorMapData, mTgaSpec._a_header._04_colorMapSpecification._02_colorMapLength);
				memBlock += mTgaSpec._a_header._04_colorMapSpecification._02_colorMapLength;
			}

			memcpy(memBlock, mTgaSpec._b_imageAndColorMapData._08_imageData, imageSize);
			memBlock += imageSize;

			memcpy(memBlock, mTgaSpec._e_footer._28_extensionAreaOffset, 4); memBlock += 4;
			memcpy(memBlock, mTgaSpec._e_footer._29_developerDirectoryOffset, 4); memBlock += 4;
			memcpy(memBlock, mTgaSpec._e_footer._30_signature, 16); memBlock += 16;
			memcpy(memBlock, &mTgaSpec._e_footer._31_reservedCharacter, 1); memBlock++;
			memcpy(memBlock, &mTgaSpec._e_footer._32_binaryZeroStringTerminator, 1); memBlock++;

			std::ofstream file(fileName.c_str(), std::ios::out | std::ios::binary);
			assert(file.is_open());
			file.write(memBlockBOF, fullSize);
			file.close();

			delete [] memBlockBOF;
		}
	}
}