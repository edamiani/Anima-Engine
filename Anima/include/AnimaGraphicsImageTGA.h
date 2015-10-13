#ifndef __ANIMA_GRAPHICS_IMAGE_TGA__
#define __ANIMA_GRAPHICS_IMAGE_TGA__

#include "AnimaGraphicsImage.h"
#include "AnimaMathVector2.h"

namespace AE
{
	namespace Graphics
	{
		class ImageTGA : public AE::Graphics::Image
		{
		public:
			ImageTGA() { }
			~ImageTGA();

			void* getData() 
			{ 
				assert(mTgaSpec._b_imageAndColorMapData._08_imageData);
				return static_cast<void *>(mTgaSpec._b_imageAndColorMapData._08_imageData);
			}

			const AE::Math::Vector2 getDimensions()
			{
				return AE::Math::Vector2(mTgaSpec._a_header._05_imageSpecification._03_imageWidth,
										 mTgaSpec._a_header._05_imageSpecification._04_imageHeight);
			}

			void load(const std::string &fileName);
			void save(const std::string &fileName);

		protected:
			struct _tgaSpec
			{
				struct
				{
					AE::uint8 _01_idLength;					/* 0x00  Tamanho do campo de ID da imagem (definir como 0) */
					AE::uint8 _02_colorMapType;				/* 0x01  Tipo de mapa de cor */
					AE::uint8 _03_imageType;				/* 0x02  Tipo de imagem */

					struct
					{
						AE::uint16 _01_firstEntryIndex;		/* 0x03  Origem do mapa de cores */
						AE::uint16 _02_colorMapLength;		/* 0x05  Comprimento do mapa de cores */
						AE::uint8  _03_colorMapEntrySize;	/* 0x07  Profundidade das entradas do mapa de cores */
					} _04_colorMapSpecification;

					struct
					{
						AE::uint16 _01_xOrigin;				/* 0x08  Coordenada X da imagem (não utilizado) */
						AE::uint16 _02_yOrigin;				/* 0x0A  Coordenada Y da imagem (não utilizado) */
						AE::uint16 _03_imageWidth;			/* 0x0C  Largura da imagem */
						AE::uint16 _04_imageHeight;			/* 0x0E  Altura da imagem */
						AE::uint8  _05_pixelDepth;			/* 0x10  Profundidade de cor dos pixels */
						AE::uint8  _06_imageDescriptor;		/* 0x11  Byte de descrição da imagem */
					} _05_imageSpecification;
				} _a_header;

				struct
				{
					AE::int8	*_06_imageId;
					AE::uint8	*_07_colorMapData;
					AE::uint8	*_08_imageData;
				} _b_imageAndColorMapData;

				struct
				{
					AE::uint8	_28_extensionAreaOffset[4];
					AE::uint8	_29_developerDirectoryOffset[4];
					AE::int8	_30_signature[16];
					AE::int8	_31_reservedCharacter;
					AE::uint8	_32_binaryZeroStringTerminator;
				} _e_footer;

				_tgaSpec()
				{
					_b_imageAndColorMapData._06_imageId = 0;
					_b_imageAndColorMapData._07_colorMapData = 0;
					_b_imageAndColorMapData._08_imageData = 0;
				}

				~_tgaSpec()
				{
					if(_b_imageAndColorMapData._06_imageId)
						delete [] _b_imageAndColorMapData._06_imageId;

					if(_b_imageAndColorMapData._07_colorMapData)
						delete [] _b_imageAndColorMapData._07_colorMapData;

					if(_b_imageAndColorMapData._08_imageData)
						delete [] _b_imageAndColorMapData._08_imageData;
				}
			} mTgaSpec;
		};
	}
}

#endif