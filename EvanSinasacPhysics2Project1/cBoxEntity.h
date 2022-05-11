#pragma once

#include <physics/cParticle.h>
#include <physics/particle_constraints.h>
#include <physics/cParticleWorld.h>
#include <../cMesh.h>
#include <../cEntity.h>
#include "globalThings.h"

class cBoxEntity : public cEntity
{
protected:
	//Box has 8 corners
	union
	{
		struct
		{
			nPhysics::cParticle* mParticleA;
			nPhysics::cParticle* mParticleB;
			nPhysics::cParticle* mParticleC;
			nPhysics::cParticle* mParticleD;

			nPhysics::cParticle* mParticleE;
			nPhysics::cParticle* mParticleF;
			nPhysics::cParticle* mParticleG;
			nPhysics::cParticle* mParticleH;
		};
		nPhysics::cParticle* mParticles[8];
	};
	// And 12 links
	// And the 4 diagonals?
	union
	{
		struct
		{
			nPhysics::cParticleRodConstraint* mConstraintAB;
			nPhysics::cParticleRodConstraint* mConstraintAD;
			nPhysics::cParticleRodConstraint* mConstraintAE;
			nPhysics::cParticleRodConstraint* mConstraintAG;

			nPhysics::cParticleRodConstraint* mConstraintBC;
			nPhysics::cParticleRodConstraint* mConstraintBF;
			nPhysics::cParticleRodConstraint* mConstraintBH;

			nPhysics::cParticleRodConstraint* mConstraintCD;
			nPhysics::cParticleRodConstraint* mConstraintCG;
			nPhysics::cParticleRodConstraint* mConstraintCE;

			nPhysics::cParticleRodConstraint* mConstraintDH;
			nPhysics::cParticleRodConstraint* mConstraintDF;

			nPhysics::cParticleRodConstraint* mConstraintEF;
			nPhysics::cParticleRodConstraint* mConstraintEH;

			nPhysics::cParticleRodConstraint* mConstraintFG;

			nPhysics::cParticleRodConstraint* mConstraintGH;
		};
		nPhysics::cParticleRodConstraint* mConstraints[16];
	};
	cMesh* mSphereMeshes[8];
public:
	cBoxEntity(glm::vec3 startPosition, float radius, float distBetweenJoints);
	virtual ~cBoxEntity();

	cBoxEntity() = delete;
	cBoxEntity(cBoxEntity& other) = delete;
	cBoxEntity& operator=(cBoxEntity& other) = delete;

	//cParticle() = delete;
	//cParticle(cParticle& other) = delete;
	//cParticle& operator=(cParticle& other) = delete;

	void AddToWorld(nPhysics::cParticleWorld* world);
	void RemoveFromWorld(nPhysics::cParticleWorld* world);

	virtual void Update();
};