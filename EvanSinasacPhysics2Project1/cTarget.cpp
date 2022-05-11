#include "cTarget.h"

cTarget::cTarget(glm::vec3 startPosition, float radius)
{
	mParticleA = new nPhysics::cParticle(-1.0f, startPosition);
	mParticleA->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));
	mParticleA->SetRadius(radius);
	mParticleA->SetType(5);

	mSphereMesh = new cMesh();
	mSphereMesh->meshName = "Isosphere_Smooth_Normals.ply";
	mSphereMesh->positionXYZ = mParticleA->GetPosition();
	mSphereMesh->scale = glm::vec3(radius);// 1.0f;
	mSphereMesh->bUseWholeObjectDiffuseColour = true;
	mSphereMesh->wholeObjectDiffuseRGBA = glm::vec4(1.0f, 1.0f, 0.2f, 0.8f);
	mSphereMesh->bUseObjectDebugColour = true;
	mSphereMesh->objectDebugColourRGBA = glm::vec4(1.0f, 1.0f, 0.2f, 0.8f);
	mSphereMesh->bDontLight = true;
	mSphereMesh->bIsWireframe = false;
	mSphereMesh->clearTextureRatiosToZero();
}
cTarget::~cTarget()
{
	delete mParticleA;
}

//cParticle() = delete;
//cParticle(cParticle& other) = delete;
//cParticle& operator=(cParticle& other) = delete;

void cTarget::AddToWorld(nPhysics::cParticleWorld* world)
{
	world->AddParticle(mParticleA);
	::g_vec_pMeshes.push_back(this->mSphereMesh);
}
void cTarget::RemoveFromWorld(nPhysics::cParticleWorld* world)
{
	world->RemoveParticle(mParticleA);
}

void cTarget::Update()
{
	mSphereMesh->positionXYZ = mParticleA->GetPosition();
}