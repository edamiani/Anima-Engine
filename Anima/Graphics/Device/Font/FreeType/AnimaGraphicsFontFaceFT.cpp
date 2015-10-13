#include "../include/AnimaGraphicsFontFaceFT.h"

#include "../include/AnimaGraphicsAxesConvention2d.h"
#include "../include/AnimaGraphicsColor.h"
#include "../include/AnimaGraphicsDeviceManager.h"
#include "../include/AnimaGraphicsDevicePixelBuffer.h"
#include "../include/AnimaGraphicsDevicePixelBufferFactory.h"
#include "../include/AnimaInputKeyInfo.h"
#include "../include/AnimaTypes.h"

namespace AE
{
	namespace Graphics
	{
		namespace Font
		{
			FaceFT::FaceFT(FT_Face face, const AE::Graphics::Font::FaceDesc &faceDesc) 
				: Face(faceDesc.fontOptions), mFaceFT(face), mDimensions(faceDesc.glyphDimensions), mOriginLine(0)
			{
				// The diacritic is a good glyph to test for the maximum height, since its measures
				// reflect its true height and bearing
				FT_Error error = FT_Load_Char(mFaceFT, '^', FT_LOAD_RENDER);
				mOriginLine += mFaceFT->glyph->bitmap_top + (mFaceFT->glyph->metrics.horiBearingY >> 6);

				int x = getAscender();
				x = getDescender();
			}

			FaceFT::~FaceFT() 
			{
			}

			void FaceFT::print(AE::Graphics::Device::PixelBuffer *destination, const std::wstring &text, const AE::Math::Point2<AE::int32> &position, const AE::Graphics::Color &color) 
			{
				AE::Math::Point2<AE::int32> pen = position;
				AE::int32 textSize = text.size();
				const wchar_t *cString = text.c_str();
				FT_Error error;

				AE::Graphics::ColorBufferDesc colorBufferDesc;
				colorBufferDesc.colorFormat = destination->getColorFormat();

				AE::uint numberOfBytes;
				AE::uint numberOfChannels;

				switch(colorBufferDesc.colorFormat)
				{
				case CF_A8R8G8B8:
					numberOfBytes = 4;
					numberOfChannels = 4;
					break;
				case CF_X8R8G8B8:
					numberOfBytes = 4;
					numberOfChannels = 3;
					break;
				case CF_R8G8B8A8:
					numberOfBytes = 4;
					numberOfChannels = 4;
					break;
				case CF_R8G8B8X8:
					numberOfBytes = 4;
					numberOfChannels = 3;
					break;
				case CF_R8G8B8:
					numberOfBytes = 3;
					numberOfChannels = 3;
					break;
				case CF_A1R5G5B5:
					numberOfBytes = 2;
					numberOfChannels = 4;
					break;
				case CF_X1R5G5B5:
					numberOfBytes = 2;
					numberOfChannels = 3;
					break;
				case CF_R5G6B5:
					numberOfBytes = 2;
					numberOfChannels = 3;
					break;
				default:
					numberOfBytes = 4;
					numberOfChannels = 4;
					break;
				}

				for (AE::int32 i = 0; i < textSize; i++)
				{
					/* load glyph image into the slot (erase previous one) */
					FT_Int32 loadFlags = FT_LOAD_RENDER;
					if(mFontOptions & AE::Graphics::FO_MONOCHROME)
					{
						loadFlags |= FT_LOAD_MONOCHROME;
						loadFlags |= FT_LOAD_TARGET_MONO;
					}

					if(*cString == ' ')
					{
						// Do nothing
					}
					else if(*cString == AE::Input::KV_FILL)
					{
						for(AE::int32 y = pen.y; y < pen.y + mDimensions.y; y++)
						{
							for(AE::int32 x = pen.x; x < pen.x + mDimensions.x; x++)
							{
								destination->plot(color, AE::Math::Point2<AE::int32>(x, y));
							}
						}
					}
					else
					{
						error = FT_Load_Char(mFaceFT, cString[i], loadFlags);
						if (error)
							continue;  /* ignore errors */

						FT_Bitmap glyphBitmap = mFaceFT->glyph->bitmap;

						if(!(mFontOptions & AE::Graphics::FO_CELL_TYPE))
						{
							pen.x += mFaceFT->glyph->bitmap_left;
							//pen.y -= mFaceFT->glyph->bitmap_top
						}

						AE::Graphics::VerticalDirection verticalDirection = AE::Graphics::AxesConvention2d::verticalDirection;
						AE::uint8 *buffer = glyphBitmap.buffer;
						
						AE::int32 startY;
						AE::int32 endY;
						
						if(verticalDirection == AE::Graphics::VD_BOTTOM_TO_TOP)
						{
							startY = pen.y - ((mFaceFT->glyph->metrics.height >> 6) - (mFaceFT->glyph->metrics.horiBearingY >> 6));
							endY = startY + glyphBitmap.rows;
						}
						else // VD_TOP_TO_BOTTOM
						{
							endY = pen.y + ((mFaceFT->glyph->metrics.height >> 6) - (mFaceFT->glyph->metrics.horiBearingY >> 6));
							startY = endY - glyphBitmap.rows;
						}

						AE::uint8 channel;

						colorBufferDesc.dimensions = AE::Math::Point2<AE::uint>(glyphBitmap.width, glyphBitmap.rows);

						if(mFontOptions & AE::Graphics::FO_MONOCHROME)
						{
							AE::byte *data = new AE::byte[colorBufferDesc.dimensions.x * colorBufferDesc.dimensions.y * numberOfBytes];
							AE::uint dataIterator = 0;

							for(AE::int32 y = startY; y < endY; y++)
							{
								AE::int32 endX = pen.x + glyphBitmap.width;
								colorBufferDesc.dimensions = AE::Math::Point2<AE::uint>(endX - pen.x, endY - startY);

								for(AE::int32 x = pen.x; x < endX; /* no increment */)
								{
									AE::int16 stride = 0;
									while(stride < glyphBitmap.width)
									{
#ifdef AE_BIG_ENDIAN
										for(AE::int16 i = 0; i < 8; i++)
#else
										for(AE::int16 i = 7; i >= 0; i--)
#endif
										{
											AE::byte color;
											if(*buffer & (1 << i))
												color = 255;
											else
												color = 0;

											// WARNING: for now, it works only on 8-bit channels (ARGB or ABGR)
											if(numberOfChannels == 4)
												data[dataIterator] = color; dataIterator++;

											data[dataIterator] = color; dataIterator++;
											data[dataIterator] = color; dataIterator++;
											data[dataIterator] = color; dataIterator++;

											x++;
											stride++;

											if(stride >= glyphBitmap.width) 
												break;
										}

										*buffer++;
									}

									AE::int16 glyphWidth = glyphBitmap.pitch * 8;
									if(glyphWidth / stride > 1)
									{
										while(stride < glyphWidth)
										{
											stride += 8;
											*buffer++;
										}
									}
								}
							}

							colorBufferDesc.data = data;
							AE::Graphics::ColorBuffer *colorBuffer = new AE::Graphics::ColorBuffer(colorBufferDesc);

							AE::Math::Point2<AE::int32> position(pen.x, 0);
							position.y = startY;

							destination->blitFrom(colorBuffer, AE::Math::Point2<AE::uint>(0, 0), colorBuffer->getDimensions(), AE::Math::Point2<AE::int32>(position.x, position.y));
							
							delete colorBuffer;
							delete[] data;
						}
						else
						{
							AE::int32 endX = pen.x + glyphBitmap.width;

							AE::int32 sizeX = endX - pen.x;
							AE::int32 sizeY = endY - startY;
							AE::byte *data = static_cast<AE::byte *>(malloc(sizeX * sizeY * numberOfBytes));
							AE::byte *tempBuffer = data;

							colorBufferDesc.dimensions = AE::Math::Point2<AE::uint>(endX - pen.x, endY - startY);

							for(AE::int32 y = startY; y < endY; y++)
							{
								for(AE::int32 x = pen.x; x < endX; x++)
								{
									channel = *buffer++;
									if(channel != 0)
									{
										for(AE::uint i = 0; i < 3; i++)
										{
											*tempBuffer = channel;
											++tempBuffer;
										}
									}
									else
									{
										for(AE::uint i = 0; i < 3; i++)
										{
											*tempBuffer = 0;
											++tempBuffer;
										}
									}

									if(numberOfChannels == 4)
									{
										*tempBuffer = 255;
										++tempBuffer;
									}
								}
								buffer += (glyphBitmap.pitch - glyphBitmap.width);
							}

							AE::Math::Point2<AE::int32> position(pen.x, 0);
							if(verticalDirection == AE::Graphics::VD_BOTTOM_TO_TOP)
								position.y = endY;
							else
								position.y = startY;

							colorBufferDesc.data = data;
							AE::Graphics::ColorBuffer *colorBuffer = new AE::Graphics::ColorBuffer(colorBufferDesc);
							
							destination->blitFrom(colorBuffer, AE::Math::Point2<AE::uint>(0, 0), colorBuffer->getDimensions(), position);
							//destination->writeFrom(imageBuffer, AE::Math::Point2(0, 0), AE::Math::Point2(sizeX, sizeY), position);

							delete colorBuffer;
						}
					}

					/* increment pen position */
					pen.x += mFaceFT->glyph->advance.x >> 6;
					//pen.y += mFaceFT->glyph->advance.y >> 6; /* not useful for now */
				}
			}
		}
	}
}