#pragma once

#include <physics/iParticleForceGenerator.h>
#include <physics/cParticle.h>
#include <vector>

// took excerpts from Ian Millington's cyclone engine

namespace nPhysics
{
	/*class ParticleForceGenerator : public iParticleForceGenerator
	{
	public:
		virtual void Update(cParticle* particle, float deltaTime) = 0;
	};*/

	class ParticleSpring : public iParticleForceGenerator
	{
	protected:
		cParticle* other;
		float springConstant;
		float restLength;

	public:
		ParticleSpring(cParticle* other, float springConst, float reastLen);

		virtual void updateForce(cParticle* particle, float deltaTime);
	};

	class ParticleAnchoredSpring : public iParticleForceGenerator
	{
	protected:
		glm::vec3 anchor;
		float springConstant;
		float restLength;

	public:
		ParticleAnchoredSpring();
		ParticleAnchoredSpring(glm::vec3 anchor, float springConst, float restLen);

		const glm::vec3 GetAnchor() const { return anchor; }

		void init(glm::vec3 anchor, float springConst, float restLen);

		virtual void Update(cParticle* particle, float deltaTime);
	};
}