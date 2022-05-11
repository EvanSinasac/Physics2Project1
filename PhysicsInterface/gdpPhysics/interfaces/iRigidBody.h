#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace gdpPhysics
{
	class iRigidBody
	{
	public:
		virtual ~iRigidBody() {}

		virtual void GetPosition(glm::vec3& positionOut) = 0;
		virtual void SetPosition(const glm::vec3& positionIn) = 0;

		virtual void GetOrientation(glm::quat& orientationOut) = 0;
		virtual void SetOrientation(const glm::quat& orientationIn) = 0;

		virtual void ApplyForce(const glm::vec3& force) = 0;
		//virtual void ApplyForceAtPoint(const glm::vec3& force, const glm::vec3& relativePoint) = 0;

	protected:
		iRigidBody() {}

	private:
		iRigidBody(const iRigidBody&) {}
		iRigidBody& operator=(const iRigidBody&) { return *this; }
	};
}