#pragma once

#include <physics/cParticle.h>
#include <physics/particle_constraints.h>
#include <physics/cParticleWorld.h>
#include <../cMesh.h>
#include <../cEntity.h>
#include "globalThings.h"

class cTarget : public cEntity
{
protected:
	
	nPhysics::cParticle* mParticleA;
	
	cMesh* mSphereMesh;
public:
	cTarget(glm::vec3 startPosition, float radius);
	virtual ~cTarget();

	cTarget() = delete;
	cTarget(cTarget& other) = delete;
	cTarget& operator=(cTarget& other) = delete;

	//cParticle() = delete;
	//cParticle(cParticle& other) = delete;
	//cParticle& operator=(cParticle& other) = delete;

	void AddToWorld(nPhysics::cParticleWorld* world);
	void RemoveFromWorld(nPhysics::cParticleWorld* world);

	virtual void Update();
};