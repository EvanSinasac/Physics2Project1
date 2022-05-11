#pragma once

#include <physics/cParticle.h>
#include <physics/particle_constraints.h>
#include <physics/cParticleWorld.h>
#include <../cMesh.h>
#include <../cEntity.h>
#include "globalThings.h"

class cHangingChainEntity : public cEntity
{
protected:

	std::vector< nPhysics::cParticle*> mParticles;
	std::vector<nPhysics::cParticleRopeConstraint*> mConstraints;
	std::vector<cMesh*> mSphereMeshes;
public:
	cHangingChainEntity(glm::vec3 startPosition, float radius, float distBetweenJoints, int numOfJoints, int numOfConstraints);
	virtual ~cHangingChainEntity();

	cHangingChainEntity() = delete;
	cHangingChainEntity(cHangingChainEntity& other) = delete;
	cHangingChainEntity& operator=(cHangingChainEntity& other) = delete;

	//cParticle() = delete;
	//cParticle(cParticle& other) = delete;
	//cParticle& operator=(cParticle& other) = delete;

	void AddToWorld(nPhysics::cParticleWorld* world);
	void RemoveFromWorld(nPhysics::cParticleWorld* world);

	virtual void Update();
};