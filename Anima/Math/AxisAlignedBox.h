#ifndef __TR_MATH_AXIS_ALIGNED_BOX__
#define __TR_MATH_AXIS_ALIGNED_BOX__

// Precompiler options
//#include "AnimaPrerequisites.h"
#include "Anima/Math/Vector3.h"
#include "Anima/Math/Matrix4.h"
#include "Anima/Math/Math.h"

namespace AE
{
	namespace Math
	{

		/** A 3D box aligned with the x/y/z axes.
		@remarks
		This class represents a simple box which is aligned with the
		axes. Internally it only stores 2 points as the extremeties of
		the box, one which is the minima of all 3 axes, and the other
		which is the maxima of all 3 axes. This class is typically used
		for an axis-aligned bounding box (AABB) for collision and
		visibility determination.
		*/
		class AxisAlignedBox
		{
		protected:
			enum Extent
			{
				EXTENT_NULL,
				EXTENT_FINITE,
				EXTENT_INFINITE
			};

			Vector3 mMinimum;
			Vector3 mMaximum;
			Extent mExtent;
			mutable Vector3* mCorners;

		public:
			/*
			1-----2
			/|    /|
			/ |   / |
			5-----4  |
			|  0--|--3
			| /   | /
			|/    |/
			6-----7
			*/
			typedef enum
			{
				FAR_LEFT_BOTTOM = 0,
				FAR_LEFT_TOP = 1,
				FAR_RIGHT_TOP = 2,
				FAR_RIGHT_BOTTOM = 3,
				NEAR_RIGHT_BOTTOM = 7,
				NEAR_LEFT_BOTTOM = 6,
				NEAR_LEFT_TOP = 5,
				NEAR_RIGHT_TOP = 4
			} CornerEnum;

			inline AxisAlignedBox() : mCorners(0)
			{
				// Default to a null box
				setMinimum( -0.5, -0.5, -0.5 );
				setMaximum( 0.5, 0.5, 0.5 );
				mExtent = EXTENT_NULL;
			}

			inline AxisAlignedBox(const AxisAlignedBox &box) : mCorners(0)
			{
				if (box.isNull())
					setNull();
				else if (box.isInfinite())
					setInfinite();
				else
					setExtents( box.mMinimum, box.mMaximum );
			}

			inline AxisAlignedBox( const Vector3& min, const Vector3& max ) : mCorners(0)
			{
				setExtents( min, max );
			}

			inline AxisAlignedBox(
				Real mx, Real my, Real mz,
				Real Mx, Real My, Real Mz ) : mCorners(0)
			{
				setExtents( mx, my, mz, Mx, My, Mz );
			}

			AxisAlignedBox& operator=(const AxisAlignedBox& rhs)
			{
				// Specifically override to avoid copying mCorners
				if (rhs.isNull())
					setNull();
				else if (rhs.isInfinite())
					setInfinite();
				else
					setExtents(rhs.mMinimum, rhs.mMaximum);

				return *this;
			}

			~AxisAlignedBox()
			{
				if (mCorners)
					delete [] mCorners;
			}


			/** Gets the minimum corner of the box.
			*/
			inline const Vector3& getMinimum(void) const
			{
				return mMinimum;
			}

			/** Gets a modifiable version of the minimum
			corner of the box.
			*/
			inline Vector3& getMinimum(void)
			{
				return mMinimum;
			}

			/** Gets the maximum corner of the box.
			*/
			inline const Vector3& getMaximum(void) const
			{
				return mMaximum;
			}

			/** Gets a modifiable version of the maximum
			corner of the box.
			*/
			inline Vector3& getMaximum(void)
			{
				return mMaximum;
			}


			/** Sets the minimum corner of the box.
			*/
			inline void setMinimum( const Vector3& vec )
			{
				mExtent = EXTENT_FINITE;
				mMinimum = vec;
			}

			inline void setMinimum( Real x, Real y, Real z )
			{
				mExtent = EXTENT_FINITE;
				mMinimum.x = x;
				mMinimum.y = y;
				mMinimum.z = z;
			}

			/** Changes one of the components of the minimum corner of the box
			used to resize only one dimension of the box
			*/
			inline void setMinimumX(Real x)
			{
				mMinimum.x = x;
			}

			inline void setMinimumY(Real y)
			{
				mMinimum.y = y;
			}

			inline void setMinimumZ(Real z)
			{
				mMinimum.z = z;
			}

			/** Sets the maximum corner of the box.
			*/
			inline void setMaximum( const Vector3& vec )
			{
				mExtent = EXTENT_FINITE;
				mMaximum = vec;
			}

			inline void setMaximum( Real x, Real y, Real z )
			{
				mExtent = EXTENT_FINITE;
				mMaximum.x = x;
				mMaximum.y = y;
				mMaximum.z = z;
			}

			/** Changes one of the components of the maximum corner of the box
			used to resize only one dimension of the box
			*/
			inline void setMaximumX( Real x )
			{
				mMaximum.x = x;
			}

			inline void setMaximumY( Real y )
			{
				mMaximum.y = y;
			}

			inline void setMaximumZ( Real z )
			{
				mMaximum.z = z;
			}

			/** Sets both minimum and maximum extents at once.
			*/
			inline void setExtents( const Vector3& min, const Vector3& max )
			{
				mExtent = EXTENT_FINITE;
				mMinimum = min;
				mMaximum = max;
			}

			inline void setExtents(
				Real mx, Real my, Real mz,
				Real Mx, Real My, Real Mz )
			{
				mExtent = EXTENT_FINITE;

				mMinimum.x = mx;
				mMinimum.y = my;
				mMinimum.z = mz;

				mMaximum.x = Mx;
				mMaximum.y = My;
				mMaximum.z = Mz;

			}

			/** Returns a pointer to an array of 8 corner points, useful for
			collision vs. non-aligned objects.
			@remarks
			If the order of these corners is important, they are as
			follows: The 4 points of the minimum Z face (note that
			because TR uses right-handed coordinates, the minimum Z is
			at the 'back' of the box) starting with the minimum point of
			all, then anticlockwise around this face (if you are looking
			onto the face from outside the box). Then the 4 points of the
			maximum Z face, starting with maximum point of all, then
			anticlockwise around this face (looking onto the face from
			outside the box). Like this:
			<pre>
			1-----2
			/|    /|
			/ |   / |
			5-----4  |
			|  0--|--3
			| /   | /
			|/    |/
			6-----7
			</pre>
			@remarks as this implementation uses a static member, make sure to use your own copy !
			*/
			inline const Vector3* getAllCorners(void) const
			{
				assert( (mExtent == EXTENT_FINITE) && "Can't get corners of a null or infinite AAB" );

				// The order of these items is, using right-handed co-ordinates:
				// Minimum Z face, starting with Min(all), then anticlockwise
				//   around face (looking onto the face)
				// Maximum Z face, starting with Max(all), then anticlockwise
				//   around face (looking onto the face)
				// Only for optimization/compatibility.
				if (!mCorners)
					mCorners = new Vector3[8];

				mCorners[0] = mMinimum;
				mCorners[1].x = mMinimum.x; mCorners[1].y = mMaximum.y; mCorners[1].z = mMinimum.z;
				mCorners[2].x = mMaximum.x; mCorners[2].y = mMaximum.y; mCorners[2].z = mMinimum.z;
				mCorners[3].x = mMaximum.x; mCorners[3].y = mMinimum.y; mCorners[3].z = mMinimum.z;

				mCorners[4] = mMaximum;
				mCorners[5].x = mMinimum.x; mCorners[5].y = mMaximum.y; mCorners[5].z = mMaximum.z;
				mCorners[6].x = mMinimum.x; mCorners[6].y = mMinimum.y; mCorners[6].z = mMaximum.z;
				mCorners[7].x = mMaximum.x; mCorners[7].y = mMinimum.y; mCorners[7].z = mMaximum.z;

				return mCorners;
			}

			/** gets the position of one of the corners
			*/
			Vector3 getCorner(CornerEnum cornerToGet)
			{
				switch(cornerToGet)
				{
				case FAR_LEFT_BOTTOM:
					return mMinimum;
				case FAR_LEFT_TOP:
					return Vector3(mMinimum.x, mMaximum.y, mMinimum.z);
				case FAR_RIGHT_TOP:
					return Vector3(mMaximum.x, mMaximum.y, mMinimum.z);
				case FAR_RIGHT_BOTTOM:
					return Vector3(mMaximum.x, mMinimum.y, mMinimum.z);
				case NEAR_RIGHT_BOTTOM:
					return Vector3(mMaximum.x, mMinimum.y, mMaximum.z);
				case NEAR_LEFT_BOTTOM:
					return Vector3(mMinimum.x, mMinimum.y, mMaximum.z);
				case NEAR_LEFT_TOP:
					return Vector3(mMinimum.x, mMaximum.y, mMaximum.z);
				case NEAR_RIGHT_TOP:
					return mMaximum;
				default:
					return Vector3();
				}
			}

			friend std::ostream& operator<<( std::ostream& o, AxisAlignedBox aab )
			{
				switch (aab.mExtent)
				{
				case EXTENT_NULL:
					o << "AxisAlignedBox(null)";
					return o;

				case EXTENT_FINITE:
					o << "AxisAlignedBox(min=" << aab.mMinimum << ", max=" << aab.mMaximum << ")";
					return o;

				case EXTENT_INFINITE:
					o << "AxisAlignedBox(infinite)";
					return o;

				default: // shut up compiler
					assert( false && "Never reached" );
					return o;
				}
			}

			/** Sets the box to a 'null' value i.e. not a box.
			*/
			inline void setNull()
			{
				mExtent = EXTENT_NULL;
			}

			/** Returns true if the box is null i.e. empty.
			*/
			inline bool isNull(void) const
			{
				return (mExtent == EXTENT_NULL);
			}

			/** Returns true if the box is finite.
			*/
			bool isFinite(void) const
			{
				return (mExtent == EXTENT_FINITE);
			}

			/** Sets the box to 'infinite'
			*/
			inline void setInfinite()
			{
				mExtent = EXTENT_INFINITE;
			}

			/** Returns true if the box is infinite.
			*/
			bool isInfinite(void) const
			{
				return (mExtent == EXTENT_INFINITE);
			}

			/// Calculate the volume of this box
			Real volume(void) const
			{
				switch (mExtent)
				{
				case EXTENT_NULL:
					return 0.0f;

				case EXTENT_FINITE:
					{
						Vector3 diff = mMaximum - mMinimum;
						return diff.x * diff.y * diff.z;
					}

				case EXTENT_INFINITE:
					return AE::Math::POS_INFINITY;

				default: // shut up compiler
					assert( false && "Never reached" );
					return 0.0f;
				}
			}

			/** Scales the AABB by the vector given. */
			inline void scale(const Vector3& s)
			{
				// Do nothing if current null or infinite
				if (mExtent != EXTENT_FINITE)
					return;

				// NB assumes centered on origin
				Vector3 min = mMinimum * s;
				Vector3 max = mMaximum * s;
				setExtents(min, max);
			}

			/** Tests 2 boxes for equality.
			*/
			bool operator== (const AxisAlignedBox& rhs) const
			{
				if (this->mExtent != rhs.mExtent)
					return false;

				if (!this->isFinite())
					return true;

				return this->mMinimum == rhs.mMinimum &&
					   this->mMaximum == rhs.mMaximum;
			}

			/** Tests 2 boxes for inequality.
			*/
			bool operator!= (const AxisAlignedBox& rhs) const
			{
				return !(*this == rhs);
			}

		};

	} // namespace Math
} // namespace AE

#endif
