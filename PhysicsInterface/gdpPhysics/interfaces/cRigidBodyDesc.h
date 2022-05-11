#pragma once

#include <glm/glm.hpp>

namespace gdpPhysics
{
	class cRigidBodyDesc
	{
	public:
		cRigidBodyDesc()
			: mass(1.f)
			, IsStatic(false)
			, position(glm::vec3(0.f))
			, velocity(glm::vec3(0.f)) 
			, damping (0.1f)
			, restitution(0.8f)
			, friction(0.95f) {}

		float mass;

		bool IsStatic;

		glm::vec3 position;
		glm::vec3 velocity;

		float damping;
		float restitution;
		float friction;
	};
}