#include <../cHangingChainEntity.h>

cHangingChainEntity::cHangingChainEntity(glm::vec3 startPosition, float radius, float distBetweenJoints, int numOfJoints, int numOfConstraints)
{
	nPhysics::cParticle* pivotParticle = new nPhysics::cParticle(0.0f, startPosition);
	pivotParticle->SetAcceleration(glm::vec3(0.0f));
	pivotParticle->SetRadius(radius / 2.0f);
	this->mParticles.push_back(pivotParticle);

	cMesh* pivotMesh = new cMesh();
	pivotMesh->meshName = "Isosphere_Smooth_Normals.ply";
	pivotMesh->positionXYZ = pivotParticle->GetPosition();
	pivotMesh->scale = glm::vec3(radius / 2.0f);// 1.0f;
	pivotMesh->bUseWholeObjectDiffuseColour = true;
	pivotMesh->wholeObjectDiffuseRGBA = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	pivotMesh->bUseObjectDebugColour = true;
	pivotMesh->objectDebugColourRGBA = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	pivotMesh->bDontLight = true;
	pivotMesh->bIsWireframe = false;
	pivotMesh->clearTextureRatiosToZero();

	this->mSphereMeshes.push_back(pivotMesh);


	for (unsigned int index = 1; index < numOfJoints - 1; index++)
	{
		nPhysics::cParticle* tempParticle = new nPhysics::cParticle(2.0f, 
			glm::vec3(startPosition.x, 
			startPosition.y - (distBetweenJoints * index), 
			startPosition.z));
		tempParticle->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));
		tempParticle->SetRadius(radius);
		tempParticle->SetType(2);
		this->mParticles.push_back(tempParticle);

		cMesh* tempMesh = new cMesh();
		tempMesh->meshName = "Isosphere_Smooth_Normals.ply";
		tempMesh->positionXYZ = tempParticle->GetPosition();
		tempMesh->scale = glm::vec3(radius);// 1.0f;
		tempMesh->bUseWholeObjectDiffuseColour = true;
		tempMesh->wholeObjectDiffuseRGBA = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
		tempMesh->bUseObjectDebugColour = true;
		tempMesh->objectDebugColourRGBA = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
		tempMesh->bDontLight = true;
		tempMesh->bIsWireframe = false;
		tempMesh->clearTextureRatiosToZero();
		this->mSphereMeshes.push_back(tempMesh);
	}

	// TODO: make a target that inherits from cParticle (maybe, idk, it wouldn't really change anything for this)
	nPhysics::cParticle* targetParticle = new nPhysics::cParticle(2.0f,
		glm::vec3(startPosition.x,
			startPosition.y - (distBetweenJoints * numOfJoints),
			startPosition.z));
	targetParticle->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));
	targetParticle->SetRadius(::g_config.GetHCTargetRadius());
	targetParticle->SetType(1);
	mParticles.push_back(targetParticle);


	cMesh* targetMesh = new cMesh();
	targetMesh->meshName = "Isosphere_Smooth_Normals.ply";
	targetMesh->positionXYZ = targetParticle->GetPosition();
	targetMesh->scale = glm::vec3(radius * 10.0f);// 1.0f;
	targetMesh->bUseWholeObjectDiffuseColour = true;
	targetMesh->wholeObjectDiffuseRGBA = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	targetMesh->bUseObjectDebugColour = true;
	targetMesh->objectDebugColourRGBA = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
	targetMesh->bDontLight = true;
	targetMesh->bIsWireframe = false;
	targetMesh->clearTextureRatiosToZero();

	this->mSphereMeshes.push_back(targetMesh);

	for (unsigned int index = 0; index < numOfConstraints; index++)
	{
		nPhysics::cParticleRopeConstraint* tempConstraint = new nPhysics::cParticleRopeConstraint(mParticles[index], mParticles[index + 1]);
		mConstraints.push_back(tempConstraint);
	}

}

cHangingChainEntity::~cHangingChainEntity()
{
	for (size_t idx = 0; idx < ::g_config.GetHCNumOfJoints(); idx++)
	{
		delete mParticles[idx];
		delete mSphereMeshes[idx];
	}
	for (size_t idx = 0; idx < ::g_config.GetHCNumOfConstraints(); idx++)
	{
		delete mConstraints[idx];
	}
}

void cHangingChainEntity::AddToWorld(nPhysics::cParticleWorld* world)
{
	for (size_t idx = 0; idx < ::g_config.GetHCNumOfJoints(); idx++)
	{
		world->AddParticle(mParticles[idx]);
		::g_vec_pMeshes.push_back(mSphereMeshes[idx]);
	}
	for (size_t idx = 0; idx < ::g_config.GetHCNumOfConstraints(); idx++)
	{
		world->AddContactGenerator(mConstraints[idx]);
	}
}

void cHangingChainEntity::RemoveFromWorld(nPhysics::cParticleWorld* world)
{
	for (size_t idx = 0; idx < ::g_config.GetHCNumOfJoints(); idx++)
	{
		world->RemoveParticle(mParticles[idx]);
	}
	for (size_t idx = 0; idx < ::g_config.GetHCNumOfConstraints(); idx++)
	{
		world->RemoveContactGenerator(mConstraints[idx]);
	}
}

void cHangingChainEntity::Update()
{
	for (size_t idx = 0; idx < mParticles.size(); idx++)
	{
		mSphereMeshes[idx]->positionXYZ = mParticles[idx]->GetPosition();
	}
}