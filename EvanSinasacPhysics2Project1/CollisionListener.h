#pragma once

#include <GdpPhysics/interfaces/iCollisionListener.h>

class CollisionListener : public gdpPhysics::iCollisionListener
{
public:
	CollisionListener() { }
	virtual ~CollisionListener() { }

	virtual void Collision(gdpPhysics::iRigidBody* bodyA, gdpPhysics::iRigidBody* bodyB);

};