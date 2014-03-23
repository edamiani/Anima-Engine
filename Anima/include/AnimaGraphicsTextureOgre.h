#ifndef __AE_GRAPHICS_TEXTURE_OGRE__
#define __AE_GRAPHICS_TEXTURE_OGRE__

#include "AnimaGraphicsTexture.h"

#include <Ogre.h>

namespace AE
{
	namespace Graphics
	{
		class TextureOgre
		{
		public:
			TextureOgre(const std::string &name, AE::uint width, AE::uint height) : 
			  mWidth(width), mHeight(height), mRowPitch(0)
			{
				mTexture = Ogre::TextureManager::getSingleton().createManual(
					name, // Name of texture
					"AnimaEngine", // Name of resource group in which the texture should be created
					Ogre::TEX_TYPE_2D, // Texture type
					width, // Width
					height, // Height
					1, // Depth (Must be 1 for two dimensional textures)
					0, // Number of mipmaps
					Ogre::PF_X8R8G8B8, // Pixel format
					Ogre::TU_DYNAMIC_WRITE_ONLY // usage
					);
			}

			~TextureOgre() { }

			AE::uint getHeight() { return mHeight; }
			AE::uint getRowPitch() { return mRowPitch; }
			AE::uint getWidth() { return mWidth; }
			
			void* lock() 
			{ 
				// Get the PixelBuffer for face 0, mipmap 0.
				mBuffer = mTexture->getBuffer(0,0);

				/// Lock the buffer so we can write to it
				mBuffer->lock(Ogre::HardwareBuffer::HBL_DISCARD);
				const Ogre::PixelBox &pb = mBuffer->getCurrentLock();
				mRowPitch = pb.rowPitch;
				return pb.data;
			}

			void unlock()
			{
				mBuffer->unlock();
			}

		private:
			Ogre::HardwarePixelBufferSharedPtr	mBuffer;
			Ogre::TexturePtr					mTexture;

			AE::uint mWidth, mHeight;
			AE::uint mRowPitch;
		};
	}
}

#endif