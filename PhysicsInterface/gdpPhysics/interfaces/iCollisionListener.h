#pragma once

#include "iRigidBody.h"

namespace gdpPhysics
{
	class iCollisionListener
	{
	public:
		virtual ~iCollisionListener(void) { }

		virtual void Collision(iRigidBody* bodyA, iRigidBody* bodyB) = 0;

	protected:
		iCollisionListener(void) { }

	private:
		iCollisionListener(const iCollisionListener&) { }
		iCollisionListener& operator=(const iCollisionListener&) { return *this; }
	};
}