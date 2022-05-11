#pragma once

#include "PhysicsFactory.h"

#include "PhysicsWorld.h"
#include "RigidBody.h"

namespace gdpPhysics
{
	PhysicsFactory::PhysicsFactory()
		: iPhysicsFactory()
	{
	}

	PhysicsFactory::~PhysicsFactory()
	{
	}

	iPhysicsWorld* PhysicsFactory::CreateWorld()
	{
		return new PhysicsWorld();
	}

	iRigidBody* PhysicsFactory::CreateRigidBody(const cRigidBodyDesc& desc, iShape* shape)
	{
		return new RigidBody(desc, shape);
	}
}
