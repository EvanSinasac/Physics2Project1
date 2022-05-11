#pragma once

#include <gdpPhysics/interfaces/iPhysicsWorld.h>
#include <vector>

#include "RigidBody.h"
#include "CollisionHandler.h"


namespace gdpPhysics
{
	class PhysicsWorld : public iPhysicsWorld
	{
	public:
		PhysicsWorld();
		virtual ~PhysicsWorld();

		virtual void SetGravity(const glm::vec3& gravity);
		virtual void RegisterCollisionListener(iCollisionListener* listener);
		virtual void AddRigidBody(iRigidBody* body);
		virtual void RemoveRigidBody(iRigidBody* body);
		virtual void TimeStep(float dt);
	private:
		glm::vec3 m_Gravity;
		std::vector<RigidBody*> m_RigidBodies;
		CollisionHandler* m_CollisionHandler;
		iCollisionListener* m_CollisionListener;

		PhysicsWorld(const PhysicsWorld&) {}
		PhysicsWorld& operator=(const PhysicsWorld&) { return *this; }
	};
}