#ifndef __AE_PHYSICS2D_CONTACT_LISTENER_BOX2D__
#define __AE_PHYSICS2D_CONTACT_LISTENER_BOX2D__

#include "Box2d/Box2d.h"

namespace AE
{
	namespace Physics2d
	{
		class Body;

		class ContactListener : public AE::Physics2d::ContactListener, public b2ContactListener
		{
		public:
							ContactListenerBox2d() { }			
			virtual			~ContactListenerBox2d() { }

			// Inherited from AE::Physics::ContactListener2d
			virtual void	onBeginContact(AE::Physics2d::Body *body1, AE::Physics2d::Body *body2) { }
			virtual void	onEndContact(AE::Physics2d::Body *body1, AE::Physics2d::Body *body2) { }

			// Inherited from b2ContactListener
			void			BeginContact(b2Contact *contact);
			void			EndContact(b2Contact *contact);
		};
	}
}

#endif