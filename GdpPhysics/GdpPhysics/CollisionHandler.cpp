#include "CollisionHandler.h"
#include "RigidBody.h"

namespace gdpPhysics
{
	CollisionHandler::CollisionHandler() {}
	CollisionHandler::~CollisionHandler() {}

	glm::vec3 ProjectOn(glm::vec3 b, glm::vec3 a)
	{
		float mult = ((a.x * b.x) + (a.y * b.y) + (a.z * b.z)) / ((b.x * b.x) + (b.y * b.y) + (b.z * b.z));
		return glm::vec3(b.x * mult, b.y * mult, b.z * mult);
	}

	// Page 224 Chapter 5 Basic Primitive Tests
	// Christer Ericson - Real-time Collision Detection
	bool TestMovingSphereSphere(
		const glm::vec3& s0Center, const float s0Radius,
		const glm::vec3& s1Center, const float s1Radius,
		const glm::vec3& v0, const glm::vec3& v1, float& t)
	{
		// Textbook orange... Eric one
		glm::vec3 s = s1Center - s0Center;	// Vector between sphere centers
		glm::vec3 v = v1 - v0;				// Relative motion of s1 with respect to stationary s0
		float r = s1Radius + s0Radius;		// SUm of sphere radii
		float c = glm::dot(s, s) - r * r;

		if (c < 0.0f) {
			// Already intersecting, not moving towards a collision
			t = 0.0f;
			return true;
		}

		float a = glm::dot(v, v);
		if (a < std::numeric_limits<float>::epsilon())
			return false;		// Spheres not moving relative to eachother

		float b = glm::dot(v, s);
		if (b >= 0.0f)
			return false;		// Spherse not moving towards eachother

		float d = (b * b) - (a * c);
		if (d < 0.0f)
			return false;		// No real-valued root,  spheres do not intersect

		t = (-b - sqrt(d)) / a;
		return true;
	}

	bool CollisionHandler::CollideSphereSphere(
		float dt, RigidBody* bodyA, SphereShape* sphereA,
		RigidBody* bodyB, SphereShape* sphereB)
	{
		if (bodyA->IsStatic() && bodyB->IsStatic())
			return false;

		glm::vec3 vA = bodyA->m_Position - bodyA->m_PreviousPosition;
		glm::vec3 vB = bodyB->m_Position - bodyB->m_PreviousPosition;

		float t = 0.f;
		if (!TestMovingSphereSphere(bodyA->m_PreviousPosition, sphereA->GetRadius()
			, bodyB->m_PreviousPosition, sphereB->GetRadius()
			, vA, vB, t))
		{
			// No current or future collision
			return false;
		}

		if (t > dt)
			return false; // No collision this update step.

		float fractDt = t / (glm::length(vA) + glm::length(vB));
		fractDt = glm::clamp(fractDt, 0.f, 1.f);
		float revDt = (1.0f - fractDt) * dt;
		bodyA->VerletStep1(-revDt);
		bodyB->VerletStep1(-revDt);

		float totalMass = bodyA->m_Mass + bodyB->m_Mass;

		float aFactor = bodyB->m_Mass / totalMass;
		float bFactor = bodyA->m_Mass / totalMass;

		glm::vec3 ab = bodyB->m_Position - bodyA->m_Position;
		float lengthAB = glm::length(ab);
		float overlap = lengthAB - (sphereA->GetRadius() + sphereB->GetRadius());

		if (overlap < std::numeric_limits<float>::epsilon())
		{
			glm::vec3 overlapVec = ab;
			overlapVec = glm::normalize(overlapVec);
			overlapVec *= -overlap;

			if (!bodyA->m_IsStatic) bodyB->m_Position += overlapVec * bFactor;
			if (!bodyB->m_IsStatic) bodyA->m_Position -= overlapVec * aFactor;

			ab = bodyB->m_Position - bodyA->m_Position;
			lengthAB = glm::length(ab);
		}
		ab /= lengthAB;

		// p = m*v
		// p: momentum
		// m: mass
		// v: velocity

		// Reactions to collisions conserve momentum, and involve both elastic
		// and inelastic components. It "looks right" - meaning I should see
		// what I would expect to happen in the real world: small spheres
		// being pushed around and bouncing off of larger ones, while larger
		// spheres more easily push past smaller ones

		glm::vec3 momentumA = bodyA->m_Velocity * bodyA->m_Mass;
		glm::vec3 momentumB = bodyB->m_Velocity * bodyB->m_Mass;
		glm::vec3 totalMomentum = momentumA + momentumB;

		momentumA = totalMomentum * aFactor;
		momentumB = totalMomentum * bFactor;

		float elasticity = 0.4f;	// This can be changed from a value between 0.0 and 1.0;

		glm::vec3 elasticMomentumB = ab * (glm::length(momentumB) * elasticity) * (-1.0f);
		glm::vec3 inelasticMomentumB = ab * glm::length(momentumB) * (1.0f - elasticity);

		glm::vec3 elasticMomentumA = ab * (glm::length(momentumA) * elasticity);
		glm::vec3 inelasticMomentumA = ab * glm::length(momentumA) * (1.0f - elasticity);

		bodyA->m_Velocity -= (elasticMomentumA + inelasticMomentumA) * (bodyA->m_InvMass * bodyA->m_Restitution);
		bodyB->m_Velocity += (elasticMomentumB + inelasticMomentumB) * (bodyB->m_InvMass * bodyB->m_Restitution);

		//printf("BodyA: Velocity(%.2f, %.2f)", bodyA->m_Velocity.x, bodyA->m_Velocity.y);
		//printf("BodyB: Velocity(%.2f, %.2f)", bodyB->m_Velocity.x, bodyB->m_Velocity.y);

		// Integrate
		bodyA->VerletStep1(revDt);
		bodyB->VerletStep1(revDt);

		return true;
	}

	bool TestMovingSpherePlane(const glm::vec3& a, const glm::vec3& b, float r, const glm::vec3& norm, float dotProduct)
	{
		// Get distance for both a and b form the plane
		float adist = glm::dot(a, norm) - dotProduct;
		float bdist = glm::dot(b, norm) - dotProduct;

		// Intersects if on different sides of plane (distances have different signs)
		if (adist * bdist < 0.0f)
			return true;

		// Interesects if start or end position within radius form plane
		if (abs(adist) <= r || abs(bdist) < r)			// <---- HERE --- REPLACE bdist compare <= with <
			return true;

		// No intersection
		return false;
	}

	glm::vec3 ClosestPtPointPlane(const glm::vec3& pt, const glm::vec3& norm, float dotProduct)
	{
		float t = glm::dot(norm, pt) - dotProduct;
		return pt - t * norm;
	}

	bool  CollisionHandler::CollideSpherePlane(float dt, RigidBody* sphere, SphereShape* sphereShape,
		RigidBody* plane, PlaneShape* planeShape)
	{
		// TestMovingSpherePlane(...) ericson textbook
		if (!TestMovingSpherePlane(sphere->m_PreviousPosition, sphere->m_Position, sphereShape->GetRadius(),
			planeShape->GetNormal(), planeShape->GetDotProduct()))
		{
			return false;
		}

		glm::vec3 closestPoint = ClosestPtPointPlane(sphere->m_Position, planeShape->GetNormal(), planeShape->GetDotProduct());
		glm::vec3 overlapVec = closestPoint - sphere->m_Position;
		float overlapLength = glm::length(overlapVec);

		float velocityLength = glm::length(sphere->m_Velocity);

		if (velocityLength > 0.000001f)
		{
			float overlapLength = glm::length(overlapVec);
			float velocity = glm::length(sphere->m_Velocity);

			// fractDt is the overlap "ratio" of the timestep
			float fractDt = sphereShape->GetRadius() * ((sphereShape->GetRadius() / overlapLength) - 1.0f) / velocity;

			// partialDt is the part of the dt contributed to the overlap
			float partialDt = (1.f - fractDt) * dt;

			// Backing up the sphere so it should be just touching the plane
			sphere->VerletStep1(-partialDt);

			// Bouncing off
			glm::vec3 reflect = glm::reflect(sphere->m_Velocity, planeShape->GetNormal());
			sphere->m_Velocity = reflect;

			glm::vec3 previousVelocity = sphere->m_Velocity;
			sphere->m_Velocity = reflect;

			glm::vec3 impactComponent = ProjectOn(sphere->m_Velocity, planeShape->GetNormal());
			glm::vec3 impactTangent = previousVelocity - impactComponent;
			sphere->ApplyForce(impactTangent * -1.f * sphere->m_Mass * plane->m_Friction);


			sphere->VerletStep1(partialDt);

			closestPoint = ClosestPtPointPlane(sphere->m_Position, planeShape->GetNormal(), planeShape->GetDotProduct());
			overlapVec = closestPoint - sphere->m_Position;
			overlapLength = glm::length(overlapVec);
			if (overlapLength < sphereShape->GetRadius())
			{
				sphere->m_Position += planeShape->GetNormal() * (sphereShape->GetRadius() - overlapLength);
				float velDotNorm = glm::dot(sphere->m_Velocity, planeShape->GetNormal());
				if (velDotNorm < 0.f)
				{
					sphere->m_Velocity -= planeShape->GetNormal() * velDotNorm;
				}
			}
			else
			{
				// Should reduce the velocity after impact
				sphere->m_Velocity *= sphere->m_Restitution;
			}

		}
		/*else
		{
			return false;
		}*/

		return true;
	}

	void CollisionHandler::Collide(
		float dt, std::vector<RigidBody*>& bodies, std::vector<CollidingBodies>& collidingBodies)
	{
		iShape* shapeA;
		iShape* shapeB;

		int bodyCount = bodies.size();
		for (int idxA = 0; idxA < bodyCount - 1; idxA++)
		{
			for (int idxB = idxA + 1; idxB < bodyCount; idxB++)
			{
				bool collision = false;
				
				RigidBody* bodyA = bodies[idxA];
				RigidBody* bodyB = bodies[idxB];

				shapeA = bodyA->GetShape();
				shapeB = bodyB->GetShape();

				if (shapeA->GetShapeType() == eShapeType::ShapeTypeSphere)
				{
					if (shapeB->GetShapeType() == eShapeType::ShapeTypeSphere)
					{
						if (CollideSphereSphere(dt, 
							bodyA, dynamic_cast<SphereShape*>(shapeA), 
							bodyB, dynamic_cast<SphereShape*>(shapeB)))
						{
							collision = true;
						}
					}
					else if (shapeB->GetShapeType() == eShapeType::ShapeTypePlane)
					{
						if (CollideSpherePlane(dt,
							bodyA, SphereShape::Cast(shapeA),
							bodyB, PlaneShape::Cast(shapeB)))
						{
							collision = true;
						}
					}
				}
				else if (shapeA->GetShapeType() == eShapeType::ShapeTypePlane)
				{
					if (shapeB->GetShapeType() == eShapeType::ShapeTypeSphere)
					{
						if (CollideSpherePlane(dt,
							bodyB, SphereShape::Cast(shapeB),
							bodyA, PlaneShape::Cast(shapeA)))
						{
							collision = true;
						}
					}
					else if (shapeB->GetShapeType() == eShapeType::ShapeTypePlane)
					{
						// Nope!
					}
				}

				if (collision)
				{
					// Add collision to vector
					collidingBodies.push_back(CollidingBodies(bodyA, bodyB));
				}
			}
		}
	}
}