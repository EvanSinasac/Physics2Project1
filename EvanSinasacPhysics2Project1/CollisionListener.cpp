#include "CollisionListener.h"
#include <GdpPhysics/RigidBody.h>
#include <iostream>

void CollisionListener::Collision(gdpPhysics::iRigidBody* bodyA, gdpPhysics::iRigidBody* bodyB)
{
	//printf("Collision!\n");
	// TODO: Bonus marks, make a sound effect when two balls hit each other
	// sorry, I'm being a little lazy, so this is here, just not finished (I just never got around to implementing FMOD into this project)
	if (((gdpPhysics::RigidBody*)bodyA)->GetShape()->GetShapeType() == eShapeType::ShapeTypeSphere
		&& ((gdpPhysics::RigidBody*)bodyB)->GetShape()->GetShapeType() == eShapeType::ShapeTypeSphere)
	{
		// Play a sound effect, if I wasn't being stubborn and just implemented FMOD
		std::cout << "Balls hit!" << std::endl;
	}
}