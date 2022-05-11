#pragma once

#include <gdpPhysics/interfaces/iPhysicsFactory.h>

namespace gdpPhysics
{
	class PhysicsFactory : public iPhysicsFactory
	{
	public:
		PhysicsFactory();
		virtual ~PhysicsFactory();

		virtual iPhysicsWorld* CreateWorld();

		virtual iRigidBody* CreateRigidBody(const cRigidBodyDesc& desc, iShape* shape);
	};
}
