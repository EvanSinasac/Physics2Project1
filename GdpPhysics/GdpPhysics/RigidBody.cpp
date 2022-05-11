#include "RigidBody.h"

namespace gdpPhysics
{
	RigidBody::RigidBody(const cRigidBodyDesc& desc, iShape* shape)
		: iRigidBody()
		, m_Shape(shape)
		, m_Mass(desc.mass)
		, m_IsStatic(desc.IsStatic)
		, m_Position(desc.position)
		, m_Velocity(desc.velocity)
		, m_Damping(desc.damping)
		, m_Restitution(desc.restitution)
		, m_Friction(desc.friction)
	{
		if (m_IsStatic || desc.mass <= 0.0f)
		{
			m_Mass = 0.f;
			m_InvMass = 0.f;
			m_IsStatic;
		}
		else
		{
			m_Mass = desc.mass;
			m_InvMass = 1.0f / desc.mass;
		}
	}

	RigidBody::~RigidBody() {}

	bool RigidBody::IsStatic() const
	{
		return m_IsStatic;
	}

	iShape* RigidBody::GetShape()
	{
		return m_Shape;
	}

	void RigidBody::GetPosition(glm::vec3& positionOut)
	{
		positionOut = m_Position;
	}

	void RigidBody::SetPosition(const glm::vec3& positionIn)
	{
		m_Position = positionIn;
	}

	void RigidBody::GetOrientation(glm::quat& orientationOut)
	{
		// TODO:
	}

	void RigidBody::SetOrientation(const glm::quat& orientationIn)
	{
		// TODO:
	}

	void RigidBody::ApplyForce(const glm::vec3& force)
	{
		m_Force += force;
	}

	void RigidBody::SetGravityAcceleration(const glm::vec3& gravity)	
	{
		m_Gravity = gravity;
	}

	void RigidBody::UpdateAcceleration()								
	{
		if (m_IsStatic)
			return;

		m_Acceleration = m_Force * m_InvMass + m_Gravity;
	}

	void RigidBody::KillForces()										
	{
		m_Force = glm::vec3(0.0f);
	}

	void RigidBody::ApplyDamping(float dt)								
	{
		m_Velocity *= pow(1.f - m_Damping, dt);

		if (glm::length(m_Velocity) < 0.001f)
			m_Velocity = glm::vec3(0.0f);
	}

	void RigidBody::VerletStep1(float dt)								
	{
		if (m_IsStatic)
			return;

		m_PreviousPosition = m_Position;
		m_Position += (m_Velocity + m_Acceleration * (dt * 0.5f)) * dt;
	}

	void RigidBody::VerletStep2(float dt)								
	{
		if (m_IsStatic)
			return;

		m_Velocity += m_Acceleration * (dt * 0.5f);
	}

	void RigidBody::VerletStep3(float dt)								
	{
		VerletStep2(dt);
	}
}
