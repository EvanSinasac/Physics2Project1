#include "particle_force_generators.h"

using namespace nPhysics;

ParticleSpring::ParticleSpring(cParticle* other, float sc, float rl)
	: other(other), springConstant(sc), restLength(rl)
{

}

void ParticleSpring::updateForce(cParticle* particle, float deltaTime)
{
	// Calculate the vector of the spring
	glm::vec3 force;
	particle->GetPosition(force);
	force -= other->GetPosition();

	// Calculate the magnitude of the force
	float magnitude = force.length();
	magnitude = fabs(magnitude - restLength);
	magnitude *= springConstant;

	// Calculate the final force and apply it
	force = glm::normalize(force);
	force *= -magnitude;
	particle->ApplyForce(force);

}

ParticleAnchoredSpring::ParticleAnchoredSpring()
{

}

ParticleAnchoredSpring::ParticleAnchoredSpring(glm::vec3 anchor, float sc, float rl)
	: anchor(anchor), springConstant(sc), restLength(rl)
{

}

void ParticleAnchoredSpring::init(glm::vec3 anchor, float springConst, float restLen)
{
	ParticleAnchoredSpring::anchor = anchor;
	ParticleAnchoredSpring::springConstant = springConst;
	ParticleAnchoredSpring::restLength = restLen;
}

void ParticleAnchoredSpring::Update(cParticle* particle, float deltaTime)
{
	// Calculate the vector of the spring
	glm::vec3 force;
	particle->GetPosition(force);
	force -= anchor;

	// Calculate the magnitude of the force
	float magnitude = force.length();
	magnitude = (restLength - magnitude) * springConstant;

	// Calculate the final force and apply it
	force = glm::normalize(force);
	force *= magnitude;
	particle->ApplyForce(force);
}