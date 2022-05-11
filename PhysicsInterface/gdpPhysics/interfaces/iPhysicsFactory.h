#pragma once

#include "cRigidBodyDesc.h"
#include "iRigidBody.h"
#include "iShape.h"
#include "iPhysicsWorld.h"

namespace gdpPhysics
{
	class iPhysicsFactory
	{
	public:
		virtual ~iPhysicsFactory() {}

		virtual iPhysicsWorld* CreateWorld() = 0;

		virtual iRigidBody* CreateRigidBody(
			const cRigidBodyDesc& desc, iShape* shape) = 0;

	protected:
		iPhysicsFactory() {}

	private:
		iPhysicsFactory(const iPhysicsFactory&) {}
		iPhysicsFactory& operator=(const iPhysicsFactory&) { return *this; }
	};
}