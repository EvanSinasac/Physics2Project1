#include "cSpringParticle.h"

cSpringParticle::cSpringParticle(glm::vec3 startPosition, glm::vec3 anchorPos, float radius, float springConstant, float restLength)
{
	mParticleA = new nPhysics::cParticle(20000.0f, startPosition);
	mParticleA->SetAcceleration(glm::vec3(0.0f, 0.0f, 0.0f));
	mParticleA->SetRadius(radius);
	mParticleA->SetType(6);	// spring

	mSphereMesh = new cMesh();
	mSphereMesh->meshName = "Isosphere_Smooth_Normals.ply";
	mSphereMesh->positionXYZ = mParticleA->GetPosition();
	mSphereMesh->scale = glm::vec3(radius);// 1.0f;
	mSphereMesh->bUseWholeObjectDiffuseColour = true;
	mSphereMesh->wholeObjectDiffuseRGBA = glm::vec4(0.8f, 0.8f, 1.0f, 1.0f);
	mSphereMesh->bUseObjectDebugColour = true;
	mSphereMesh->objectDebugColourRGBA = glm::vec4(0.8f, 0.8f, 1.0f, 1.0f);
	mSphereMesh->bDontLight = true;
	mSphereMesh->bIsWireframe = false;
	mSphereMesh->clearTextureRatiosToZero();

	mSphereMesh2 = new cMesh();
	mSphereMesh2->meshName = "Isosphere_Smooth_Normals.ply";
	mSphereMesh2->positionXYZ = anchorPos;
	mSphereMesh2->scale = glm::vec3(0.1);// 1.0f;
	mSphereMesh2->bUseWholeObjectDiffuseColour = true;
	mSphereMesh2->wholeObjectDiffuseRGBA = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	mSphereMesh2->bUseObjectDebugColour = true;
	mSphereMesh2->objectDebugColourRGBA = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	mSphereMesh2->bDontLight = true;
	mSphereMesh2->bIsWireframe = false;
	mSphereMesh2->clearTextureRatiosToZero();

	springFG = new nPhysics::ParticleAnchoredSpring(anchorPos, springConstant, restLength);
}
cSpringParticle::~cSpringParticle()
{
	delete mParticleA;
}

//cParticle() = delete;
//cParticle(cParticle& other) = delete;
//cParticle& operator=(cParticle& other) = delete;

void cSpringParticle::AddToWorld(nPhysics::cParticleWorld* world)
{
	world->AddParticle(mParticleA);
	world->GetForceRegistry()->Register(mParticleA, springFG);
	::g_vec_pMeshes.push_back(this->mSphereMesh);
	::g_vec_pMeshes.push_back(this->mSphereMesh2);
}
void cSpringParticle::RemoveFromWorld(nPhysics::cParticleWorld* world)
{
	world->RemoveParticle(mParticleA);
}

void cSpringParticle::Update()
{
	mSphereMesh->positionXYZ = mParticleA->GetPosition();
}