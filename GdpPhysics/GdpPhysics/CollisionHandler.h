#pragma once

#include <vector>
#include <gdpPhysics/interfaces/shapes.h>

namespace gdpPhysics
{
	class RigidBody;
	struct CollidingBodies
	{
		CollidingBodies(RigidBody* bodyA, RigidBody* bodyB)
			: BodyA(bodyA)
			, BodyB(bodyB)
		{}
		RigidBody* BodyA;
		RigidBody* BodyB;
	};

	class CollisionHandler
	{
	public:
		CollisionHandler();
		~CollisionHandler();

		bool CollideSphereSphere(float dt, RigidBody* bodyA, SphereShape* sphereA,
			RigidBody* bodyB, SphereShape* sphereB);

		bool CollideSpherePlane(float dt, RigidBody* sphere, SphereShape* spehreShape,
			RigidBody* plane, PlaneShape* planeShape);

		void Collide(float dt, std::vector<RigidBody*>& bodies, std::vector<CollidingBodies>& collidingBodies);
	};
}