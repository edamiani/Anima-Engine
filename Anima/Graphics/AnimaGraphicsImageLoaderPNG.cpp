#include "../include/AnimaGraphicsImageLoaderPng.h"

#include "../include/AnimaGraphicsImageDesc.h"
#include "../include/AnimaGraphicsImagePng.h"

#include "png.h"

namespace AE
{
	namespace Graphics
	{
		ImageLoaderPng::ImageLoaderPng()
			: ImageLoader(AE::Graphics::IT_PNG)
		{
		}

		ImageLoaderPng::~ImageLoaderPng()
		{
		}

		AE::Graphics::Image* ImageLoaderPng::load(const std::string &fileName)
		{
			const AE::int16 PNG_BYTES_TO_CHECK = 4;
			png_byte buf[PNG_BYTES_TO_CHECK];
			FILE *fp;

			/* Open the prospective PNG file. */
#if defined(AE_PLATFORM_WIN32)
			if (fopen_s(&fp, fileName.c_str(), "rb") != NULL)
				return 0;
#else
			if ((fp = fopen(fileName.c_str(), "rb")) == NULL)
				return 0;
#endif

			/* Read in some of the signature bytes */
			if (fread(buf, 1, PNG_BYTES_TO_CHECK, fp) != PNG_BYTES_TO_CHECK)
				return 0;

			/* Compare the first PNG_BYTES_TO_CHECK bytes of the signature.
			Return nonzero (true) if they match */

			if(!png_sig_cmp(buf, (png_size_t)0, PNG_BYTES_TO_CHECK))
			{
				png_structp png_ptr;
				png_infop info_ptr;
				unsigned int sig_read = 0;

				/* Create and initialize the png_struct with the desired error handler
				* functions.  If you want to use the default stderr and longjump method,
				* you can supply NULL for the last three parameters.  We also supply the
				* the compiler header file version, so that we know if the application
				* was compiled with a compatible version of the library.  REQUIRED
				*/
				png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

				if (png_ptr == NULL)
				{
					fclose(fp);
					return 0;
				}

				/* Allocate/initialize the memory for image information.  REQUIRED. */
				info_ptr = png_create_info_struct(png_ptr);
				if (info_ptr == NULL)
				{
					fclose(fp);
					png_destroy_read_struct(&png_ptr, NULL, NULL);
					return 0;
				}

				/* Set error handling if you are using the setjmp/longjmp method (this is
				* the normal method of doing things with libpng).  REQUIRED unless you
				* set up your own error handlers in the png_create_read_struct() earlier.
				*/
				if(setjmp(png_jmpbuf(png_ptr)))
				{
					/* Free all of the memory associated with the png_ptr and info_ptr */
					png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
					fclose(fp);

					/* If we get here, we had a problem reading the file */
					return 0;
				}

				/* Set up the input control if you are using standard C streams */
				png_init_io(png_ptr, fp);

				/* If we have already read some of the signature */
				png_set_sig_bytes(png_ptr, PNG_BYTES_TO_CHECK);

				/* The call to png_read_info() gives us all of the information from the
				* PNG file before the first IDAT (image data chunk).  REQUIRED
				*/
				png_read_info(png_ptr, info_ptr);

				png_uint_32 width, height;
				int bitDepth, colorType, interlaceType;

				/* Image header info */
				png_get_IHDR(png_ptr, info_ptr, &width, &height, &bitDepth, &colorType, &interlaceType, NULL, NULL);

				/*int number_passes = 0;
				#ifdef PNG_READ_INTERLACING_SUPPORTED
					// Turn on interlace handling.  REQUIRED if you are not using
					// png_read_image().  To see how to handle interlacing passes,
					// see the png_read_row() method below:
					number_passes = png_set_interlace_handling(png_ptr);
				#else
					number_passes = 1;
				#endif // PNG_READ_INTERLACING_SUPPORTED */

				/* Allocate the memory to hold the image using the fields of info_ptr. */

				/* The easiest way to read the image: */
				//png_bytep row_pointers[height];
				png_bytep *row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * height);

				/* Clear the pointer array */
				AE::uint row;
				for (row = 0; row < height; row++)
					row_pointers[row] = NULL;

				for (row = 0; row < height; row++)
					row_pointers[row] = (png_bytep)png_malloc(png_ptr, png_get_rowbytes(png_ptr, info_ptr));

				/* Read the entire image in one go */
				png_read_image(png_ptr, row_pointers);

				AE::Graphics::ImageDesc imageDesc;
				imageDesc.imageType = AE::Graphics::IT_PNG;
				imageDesc.file = fileName;
				imageDesc.colorBufferDesc.dimensions.x = width;
				imageDesc.colorBufferDesc.dimensions.y = height;

				AE::uint rowSize = png_get_rowbytes(png_ptr, info_ptr);
				imageDesc.colorBufferDesc.data = malloc(height * rowSize);

				//pixelBufferDesc.data = malloc(height * rowSize);
				AE::byte *destination = static_cast<AE::byte *>(imageDesc.colorBufferDesc.data);
				for(AE::uint i = 0; i < height; i++)
				{
					memcpy((void *)destination, (void *)row_pointers[i], rowSize);
					destination += rowSize;
				}

				AE::uint8 numChannels = png_get_channels(png_ptr, info_ptr);

				if(numChannels == 3 && bitDepth == 8)
					imageDesc.colorBufferDesc.colorFormat = AE::Graphics::CF_R8G8B8;
				else if(numChannels == 4 && bitDepth == 8)
				{
					if(colorType == PNG_COLOR_TYPE_RGB_ALPHA)
						imageDesc.colorBufferDesc.colorFormat = AE::Graphics::CF_R8G8B8A8;
					else
						imageDesc.colorBufferDesc.colorFormat = AE::Graphics::CF_R8G8B8X8;
				}

				AE::Graphics::Image *image = new AE::Graphics::ImagePng(imageDesc);

				/* Clean up after the read, and free any memory allocated - REQUIRED */
				png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

				/* Close the file */
				fclose(fp);

				return image;
			}
			else
				return 0;
		}

		bool ImageLoaderPng::unload(AE::Graphics::Image *image)
		{
			delete image;

			return true;
		}
	}
}
