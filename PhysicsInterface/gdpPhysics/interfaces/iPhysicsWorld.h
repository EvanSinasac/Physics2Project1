#pragma once

#include <glm/glm.hpp>
#include "iRigidBody.h"
#include "iCollisionListener.h"

namespace gdpPhysics
{
	class iPhysicsWorld
	{
	public:
		virtual ~iPhysicsWorld() { }

		virtual void SetGravity(const glm::vec3& gravity) = 0;
		virtual void RegisterCollisionListener(iCollisionListener* listener) = 0;
		virtual void AddRigidBody(iRigidBody* body) = 0;
		virtual void RemoveRigidBody(iRigidBody* body) = 0;
		virtual void TimeStep(float dt) = 0;

	protected:
		iPhysicsWorld() { }

	private:
		iPhysicsWorld(const iPhysicsWorld&) { }
		iPhysicsWorld& operator=(const iPhysicsWorld&) { return *this; }
	};
}
