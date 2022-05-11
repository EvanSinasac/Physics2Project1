#include "cSpinningBladeEntity.h"

cSpinningBladeEntity::cSpinningBladeEntity(glm::vec3 startPosition, float radius, float distFromStart, std::string lockedAxis)
{
	// Pivot particle
	mParticleA = new nPhysics::cParticle(0.0f, startPosition);
	mParticleA->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));
	mParticleA->SetRadius(radius / 2.0f);

	this->locked = lockedAxis;

	// Depending on which axis is locked determines which plane the particles are allowed to move on
	if (lockedAxis == "X")
	{
		// If the x-axis is locked, particle moves in YZ-plane
		this->lockedValue = startPosition.x;
		mParticleB = new nPhysics::cParticle(2.0f, glm::vec3(startPosition.x, startPosition.y + distFromStart, startPosition.z));
		mParticleB->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));	// gravity still affects it, should bring it to rest eventually
		mParticleB->SetRadius(radius);
	}
	else if (lockedAxis == "Y")
	{
		// If the y-axis is locked, partile moves in XZ-plane
		this->lockedValue = startPosition.y;
		mParticleB = new nPhysics::cParticle(2.0f, glm::vec3(startPosition.x + distFromStart, startPosition.y, startPosition.z));
		mParticleB->SetAcceleration(glm::vec3(0.0f));	// No acceleration when horizontal
		mParticleB->SetRadius(radius);
	}
	else if (lockedAxis == "Z")
	{
		// If the z-axis is locked, particle moves in XZ-plane
		this->lockedValue = startPosition.z;
		mParticleB = new nPhysics::cParticle(2.0f, glm::vec3(startPosition.x, startPosition.y + distFromStart, startPosition.z));
		mParticleB->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));  // gravity still affects it, should bring it to rest eventually
		mParticleB->SetRadius(radius);
	}
	else
	{
		// Default, if lockedAxis isn't stored correctly, particles placed on top of each other
		mParticleB = new nPhysics::cParticle(0.0f, startPosition);
		mParticleB->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));
		mParticleB->SetRadius(radius);
	}
	mParticleB->SetType(4);
	mConstraintAB = new nPhysics::cParticleRodConstraint(mParticleA, mParticleB);


	// Meshes
	mSphereMeshes[0] = new cMesh();
	mSphereMeshes[0]->meshName = "Isosphere_Smooth_Normals.ply";
	mSphereMeshes[0]->positionXYZ = mParticleA->GetPosition();
	mSphereMeshes[0]->scale = glm::vec3(radius / 2.0f);// 1.0f;
	mSphereMeshes[0]->bUseWholeObjectDiffuseColour = true;
	mSphereMeshes[0]->wholeObjectDiffuseRGBA = glm::vec4(1.0f, 0.8f, 0.89f, 1.0f);
	mSphereMeshes[0]->bUseObjectDebugColour = true;
	mSphereMeshes[0]->objectDebugColourRGBA = glm::vec4(1.0f, 0.8f, 0.89f, 1.0f);
	mSphereMeshes[0]->bDontLight = true;
	mSphereMeshes[0]->bIsWireframe = false;
	mSphereMeshes[0]->clearTextureRatiosToZero();

	mSphereMeshes[1] = new cMesh();
	mSphereMeshes[1]->meshName = "Isosphere_Smooth_Normals.ply";
	mSphereMeshes[1]->positionXYZ = mParticleB->GetPosition();
	mSphereMeshes[1]->scale = glm::vec3(radius);// 1.0f;
	mSphereMeshes[1]->bUseWholeObjectDiffuseColour = true;
	mSphereMeshes[1]->wholeObjectDiffuseRGBA = glm::vec4(0.3f, 0.0f, 0.6f, 1.0f);
	mSphereMeshes[1]->bUseObjectDebugColour = true;
	mSphereMeshes[1]->objectDebugColourRGBA = glm::vec4(0.3f, 0.0f, 0.6f, 1.0f);
	mSphereMeshes[1]->bDontLight = true;
	mSphereMeshes[1]->bIsWireframe = false;
	mSphereMeshes[1]->clearTextureRatiosToZero();


}
cSpinningBladeEntity::~cSpinningBladeEntity()
{
	for (size_t idx = 0; idx < 2; idx++)
	{
		delete mParticles[idx];
	}
	for (size_t idx = 0; idx < 1; idx++)
	{
		delete mConstraints[idx];
	}
}

void cSpinningBladeEntity::AddToWorld(nPhysics::cParticleWorld* world)
{
	for (size_t idx = 0; idx < 2; idx++)
	{
		world->AddParticle(mParticles[idx]);
		::g_vec_pMeshes.push_back(this->mSphereMeshes[idx]);
	}
	for (size_t idx = 0; idx < 1; idx++)
	{
		world->AddContactGenerator(mConstraints[idx]);
	}
}
void cSpinningBladeEntity::RemoveFromWorld(nPhysics::cParticleWorld* world)
{
	for (size_t idx = 0; idx < 2; idx++)
	{
		world->RemoveParticle(mParticles[idx]);
	}
	for (size_t idx = 0; idx < 1; idx++)
	{
		world->RemoveContactGenerator(mConstraints[idx]);
	}
}

void cSpinningBladeEntity::Update()
{
	//nInput::cKey* keyA = nInput::cInputManager::GetInstance()->ListenToKey(nInput::KeyCode::KEY_A);
	//if (keyA->IsJustPressed())
	//{
	//	mParticleA->ApplyImpulse(glm::vec3(0.0f, 15.0f, 0.0f));
	//}
	if (this->locked == "X")
	{
		mParticleB->SetPosition(glm::vec3(this->lockedValue, mParticleB->GetPosition().y, mParticleB->GetPosition().z));
	}
	else if (this->locked == "Y")
	{
		mParticleB->SetPosition(glm::vec3(mParticleB->GetPosition().x, this->lockedValue, mParticleB->GetPosition().z));
	}
	else if (this->locked == "Z")
	{
		mParticleB->SetPosition(glm::vec3(mParticleB->GetPosition().x, mParticleB->GetPosition().y, this->lockedValue));
	}


	for (size_t idx = 0; idx < 2; idx++)
	{
		mSphereMeshes[idx]->positionXYZ = mParticles[idx]->GetPosition();
	}
}