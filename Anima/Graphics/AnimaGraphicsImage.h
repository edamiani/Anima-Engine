#ifndef __ANIMA_GRAPHICS_IMAGE__
#define __ANIMA_GRAPHICS_IMAGE__

#include "AnimaGraphicsColorBuffer.h"
#include "AnimaGraphicsEnums.h"
#include "AnimaGraphicsImageDesc.h"
#include "../Math/AnimaMathPoint2.h"
#include "../AnimaTypes.h"

#include <string>

namespace AE
{
	namespace Graphics
	{
		class Image : public AE::Graphics::ColorBuffer
		{
		public:
			Image(AE::Graphics::ImageDesc const &imageDesc) :
				AE::Graphics::ColorBuffer(imageDesc.colorBufferDesc),
				mFile(imageDesc.file),
				mImageType(imageDesc.imageType) {}
			
			virtual ~Image() 
			{
			}

			AE::Graphics::ImageDesc		getDesc()
			{
				AE::Graphics::ImageDesc imageDesc;

				imageDesc.colorBufferDesc.colorFormat = mColorFormat;
				imageDesc.colorBufferDesc.data = mData;
				imageDesc.colorBufferDesc.dimensions = mDimensions;
				imageDesc.file = mFile;
				imageDesc.imageType = mImageType;

				return imageDesc;
			}

			AE::Graphics::ImageType		getImageType() { return mImageType; }
			virtual void				load() = 0;
			virtual void				save(const std::string &fileName) = 0;
			virtual void				unload() = 0;

			/***** Inherited from AE::Graphics::ColorBuffer
			AE::Graphics::ColorFormat	getColorFormat();
			void*						getData();
			AE::Math::Point2&			getDimensions();
			*****/

		protected:
			std::string					mFile;
			AE::Graphics::ImageType		mImageType;

			/***** Inherited from AE::Graphics::ColorBuffer
			AE::Graphics::ColorFormat	mColorFormat;
			void						*mData;
			AE::Math::Point2			mDimensions;
			*****/
		};
	}
}

#endif