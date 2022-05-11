#pragma once

#include <physics/cParticle.h>
#include <physics/particle_constraints.h>
#include <physics/cParticleWorld.h>
#include <../cMesh.h>
#include <../cEntity.h>
#include "globalThings.h"

class cSpinningBladeEntity : public cEntity
{
protected:
	//Blade just has 2 particles
	union
	{
		struct
		{
			nPhysics::cParticle* mParticleA;
			nPhysics::cParticle* mParticleB;
		};
		nPhysics::cParticle* mParticles[2];
	};
	// So only 1 rod constraint.  The question is, do I make the locked value here (like my initial plan)
	// OR, make a new kinds of constraints that lock certain axis of movement... initial plan for time's sake
	union
	{
		struct
		{
			nPhysics::cParticleRodConstraint* mConstraintAB;
		};
		nPhysics::cParticleRodConstraint* mConstraints[1];
	};
	cMesh* mSphereMeshes[2];

	float lockedValue;
	std::string locked;
public:
	cSpinningBladeEntity(glm::vec3 startPosition, float radius, float distFromStart, std::string lockedAxis);
	virtual ~cSpinningBladeEntity();

	cSpinningBladeEntity() = delete;
	cSpinningBladeEntity(cSpinningBladeEntity& other) = delete;
	cSpinningBladeEntity& operator=(cSpinningBladeEntity& other) = delete;

	//cParticle() = delete;
	//cParticle(cParticle& other) = delete;
	//cParticle& operator=(cParticle& other) = delete;

	void AddToWorld(nPhysics::cParticleWorld* world);
	void RemoveFromWorld(nPhysics::cParticleWorld* world);

	virtual void Update();
};