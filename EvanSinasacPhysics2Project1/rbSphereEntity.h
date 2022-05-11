#pragma once


#include "cMesh.h"
#include "cEntity.h"
#include "globalThings.h"
#include "RigidBody.h"


class rbSphereEntity : public cEntity
{
public:
	rbSphereEntity(float radius, float mass, glm::vec3 pos);
	virtual ~rbSphereEntity(void);

	rbSphereEntity() = delete;
	rbSphereEntity(rbSphereEntity& other) = delete;
	rbSphereEntity& operator=(rbSphereEntity& other) = delete;

	//void AddToWorld(gdpPhysics::iPhysicsWorld* world);
	//void RemoveFromWorld(gdpPhysics::iPhysicsWorld* world);
	//void AddToWorld(nPhysics::cParticleWorld* world);
	//void RemoveFromWorld(nPhysics::cParticleWorld* world);

	virtual void Update();


	cMesh* m_Mesh;
	RigidBody* m_RB;

private:

protected:
	float m_Radius;
	float m_Mass;
};