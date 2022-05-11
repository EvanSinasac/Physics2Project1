#pragma once

#include <physics/cParticle.h>
#include <physics/cParticleWorld.h>
#include "particle_force_generators.h"
#include <../cMesh.h>
#include <../cEntity.h>
#include "globalThings.h"

class cSpringParticle : public cEntity
{
protected:

	nPhysics::cParticle* mParticleA;
	nPhysics::ParticleAnchoredSpring* springFG;

	cMesh* mSphereMesh;
	cMesh* mSphereMesh2;
public:
	cSpringParticle(glm::vec3 startPosition, glm::vec3 anchorPos, float radius, float springConstant, float restLength);
	virtual ~cSpringParticle();

	cSpringParticle() = delete;
	cSpringParticle(cSpringParticle& other) = delete;
	cSpringParticle& operator=(cSpringParticle& other) = delete;

	//cParticle() = delete;
	//cParticle(cParticle& other) = delete;
	//cParticle& operator=(cParticle& other) = delete;

	void AddToWorld(nPhysics::cParticleWorld* world);
	void RemoveFromWorld(nPhysics::cParticleWorld* world);

	virtual void Update();
};