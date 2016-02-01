#include "../include/AnimaGraphicsColor.h"
#include "../include/AnimaGraphicsRasterFactory.h"
#include "../include/AnimaGraphicsSurface.h"
#include "../include/AnimaMath.h"

#include <cmath>

AE::Graphics::RasterFactory* AE::Graphics::RasterFactory::mInstance = 0;

namespace AE
{
	namespace Graphics
	{
		RasterFactory::RasterFactory()
		{

		}

		AE::Graphics::RasterFactory* RasterFactory::initialize()
		{
			if(!mInstance)
				mInstance = new AE::Graphics::RasterFactory();

			return mInstance;
		}

		void RasterFactory::shutdown()
		{
			if(mInstance)
				delete mInstance;
		}

		void RasterFactory::drawLine(AE::Graphics::Surface *drawingSurface, const AE::Math::Point2<AE::int32> &start, const AE::Math::Point2<AE::int32> &end, const AE::Graphics::Color &color, AE::Graphics::LockType lockType)
		{
			drawingSurface->lock(lockType);

			AE::Real deltaX = end.x - start.x;
			AE::Real deltaY = end.y - start.y;

			if(AE::Math::Abs(deltaX) >= AE::Math::Abs(deltaY))
			{
				AE::Real slope = deltaY / deltaX;

				if(deltaX > 0)
				{
					AE::Real y = start.y;
					for(AE::int16 i = start.x; i <= end.x; i++)
					{
						drawingSurface->plot(color, AE::Math::Point2<AE::int32>(i, _round(y)));
						y += slope;
					}
				}
				else
				{
					AE::Real y = end.y;
					for(AE::int16 i = end.x; i <= start.x; i++)
					{
						drawingSurface->plot(color, AE::Math::Point2<AE::int32>(i, _round(y)));
						y += slope;
					}
				}
			}
			else
			{
				AE::Real slope = deltaX / deltaY;

				if(deltaY > 0)
				{
					AE::Real x = start.x;
					for(AE::int16 i = start.y; i <= end.y; i++)
					{
						drawingSurface->plot(color, AE::Math::Point2<AE::int32>(_round(x), i));
						x += slope;
					}
				}
				else
				{
					AE::Real x = end.x;
					for(AE::int16 i = end.y; i <= start.y; i++)
					{
						drawingSurface->plot(color, AE::Math::Point2<AE::int32>(_round(x), i));
						x += slope;
					}
				}
			}

			drawingSurface->unlock();
		}

		AE::int32 RasterFactory::_round(AE::Real number)
		{
			if(number - floor(number) <= 0.5)
				return floor(number);
			else
				return ceil(number);
		}
	}
}
