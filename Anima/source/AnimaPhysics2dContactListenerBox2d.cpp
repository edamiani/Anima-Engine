#include "../include/AnimaPhysics2dContactListenerBox2d.h"

#include "../include/AnimaPhysics2dBodyBox2d.h"

namespace AE
{
	namespace Physics2d
	{
		void ContactListenerBox2d::BeginContact(b2Contact *contact)
		{
			b2Body *b2Body1 = contact->GetFixtureA()->GetBody();
			b2Body *b2Body2 = contact->GetFixtureB()->GetBody();

			AE::Physics2d::Body *body1 = static_cast<AE::Physics2d::Body *>(b2Body1->GetUserData());
			AE::Physics2d::Body *body2 = static_cast<AE::Physics2d::Body *>(b2Body2->GetUserData());

			onBeginContact(body1, body2);
		}

		void ContactListenerBox2d::EndContact(b2Contact *contact)
		{
			b2Body *b2Body1 = contact->GetFixtureA()->GetBody();
			b2Body *b2Body2 = contact->GetFixtureB()->GetBody();

			AE::Physics2d::Body *body1 = static_cast<AE::Physics2d::Body *>(b2Body1->GetUserData());
			AE::Physics2d::Body *body2 = static_cast<AE::Physics2d::Body *>(b2Body2->GetUserData());

			onEndContact(body1, body2);
		}
	}
}