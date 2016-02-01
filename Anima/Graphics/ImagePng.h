#ifndef __ANIMA_GRAPHICS_IMAGE_PNG__
#define __ANIMA_GRAPHICS_IMAGE_PNG__

#include "Anima/Graphics/Image.h"

namespace AE
{
	namespace Graphics
	{
		class ImagePng : public AE::Graphics::Image
		{
		public:
			ImagePng(AE::Graphics::ImageDesc const &imageDesc) 
				: AE::Graphics::Image(imageDesc) {}
			
			~ImagePng() 
			{
			}

			void						load() {}
			void						save(const std::string &fileName) {}
			void						unload() {}

			/***** Inherited from AE::Graphics::Image
			AE::Graphics::ImageType		getImageType();
			*****/

			/***** Inherited from AE::Graphics::ColorBuffer
			AE::Graphics::ColorFormat	getColorFormat();
			void*						getData();
			AE::Math::Point2&			getDimensions();
			AE::Math::Point2&			getRowOrder();
			*****/

		private:
			/***** Inherited from AE::Graphics::Image
			std::string					mFile;
			AE::Graphics::ImageType		mImageType;
			*****/

			/***** Inherited from AE::Graphics::ColorBuffer
			AE::Graphics::ColorFormat	mColorFormat;
			void						*mData;
			AE::Math::Point2			mDimensions;
			AE::Graphics::RowOrder		mRowOrder;
			*****/
		};
	}
}

#endif