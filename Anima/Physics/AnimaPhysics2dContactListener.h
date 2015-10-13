#ifndef __AE_PHYSICS2D_CONTACT_LISTENER__
#define __AE_PHYSICS2D_CONTACT_LISTENER__

namespace AE
{
	namespace Physics2d
	{
		class Body;

		class ContactListener
		{
		public:
							ContactListener() {  }			
			virtual			~ContactListener() {  }

			virtual void	onBeginContact(AE::Physics2d::Body *body1, AE::Physics2d::Body *body2) = 0;
			virtual void	onEndContact(AE::Physics2d::Body *body1, AE::Physics2d::Body *body2) = 0;
		};
	}
}

#endif