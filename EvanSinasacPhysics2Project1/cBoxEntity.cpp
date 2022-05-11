#include "cBoxEntity.h"

cBoxEntity::cBoxEntity(glm::vec3 startPosition, float radius, float distBetweenJoints)
{
	mParticleA = new nPhysics::cParticle(50.0f, startPosition);
	mParticleA->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));
	mParticleA->SetRadius(radius);
	mParticleA->SetType(3);

	mParticleB = new nPhysics::cParticle(50.0f, glm::vec3(startPosition.x, startPosition.y, startPosition.z + distBetweenJoints));
	mParticleB->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));
	mParticleB->SetRadius(radius);
	mParticleB->SetType(3);

	mParticleC = new nPhysics::cParticle(50.0f, glm::vec3(startPosition.x + distBetweenJoints, startPosition.y, startPosition.z + distBetweenJoints));
	mParticleC->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));
	mParticleC->SetRadius(radius);
	mParticleC->SetType(3);

	mParticleD = new nPhysics::cParticle(50.0f, glm::vec3(startPosition.x + distBetweenJoints, startPosition.y, startPosition.z));
	mParticleD->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));
	mParticleD->SetRadius(radius);
	mParticleD->SetType(3);

	mParticleE = new nPhysics::cParticle(50.0f, glm::vec3(startPosition.x, startPosition.y + distBetweenJoints, startPosition.z));
	mParticleE->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));
	mParticleE->SetRadius(radius);
	mParticleE->SetType(3);

	mParticleF = new nPhysics::cParticle(50.0f, glm::vec3(startPosition.x, startPosition.y + distBetweenJoints, startPosition.z + distBetweenJoints));
	mParticleF->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));
	mParticleF->SetRadius(radius);
	mParticleF->SetType(3);

	mParticleG = new nPhysics::cParticle(50.0f, glm::vec3(startPosition.x + distBetweenJoints, startPosition.y + distBetweenJoints, startPosition.z + distBetweenJoints));
	mParticleG->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));
	mParticleG->SetRadius(radius);
	mParticleG->SetType(3);

	mParticleH = new nPhysics::cParticle(50.0f, glm::vec3(startPosition.x + distBetweenJoints, startPosition.y + distBetweenJoints, startPosition.z));
	mParticleH->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));
	mParticleH->SetRadius(radius);
	mParticleH->SetType(3);


	mConstraintAB = new nPhysics::cParticleRodConstraint(mParticleA, mParticleB);
	mConstraintAD = new nPhysics::cParticleRodConstraint(mParticleA, mParticleD);
	mConstraintAE = new nPhysics::cParticleRodConstraint(mParticleA, mParticleE);
	mConstraintAG = new nPhysics::cParticleRodConstraint(mParticleA, mParticleG);

	mConstraintBC = new nPhysics::cParticleRodConstraint(mParticleB, mParticleC);
	mConstraintBF = new nPhysics::cParticleRodConstraint(mParticleB, mParticleF);
	mConstraintBH = new nPhysics::cParticleRodConstraint(mParticleB, mParticleH);

	mConstraintCD = new nPhysics::cParticleRodConstraint(mParticleC, mParticleD);
	mConstraintCG = new nPhysics::cParticleRodConstraint(mParticleC, mParticleG);
	mConstraintCE = new nPhysics::cParticleRodConstraint(mParticleC, mParticleE);

	mConstraintDH = new nPhysics::cParticleRodConstraint(mParticleD, mParticleH);
	mConstraintDF = new nPhysics::cParticleRodConstraint(mParticleD, mParticleF);

	mConstraintEF = new nPhysics::cParticleRodConstraint(mParticleE, mParticleF);
	mConstraintEH = new nPhysics::cParticleRodConstraint(mParticleE, mParticleH);

	mConstraintFG = new nPhysics::cParticleRodConstraint(mParticleF, mParticleG);

	mConstraintGH = new nPhysics::cParticleRodConstraint(mParticleG, mParticleH);


	// Meshes
	mSphereMeshes[0] = new cMesh();
	mSphereMeshes[0]->meshName = "Isosphere_Smooth_Normals.ply";
	mSphereMeshes[0]->positionXYZ = mParticleA->GetPosition();
	mSphereMeshes[0]->scale = glm::vec3(radius);// 1.0f;
	mSphereMeshes[0]->bUseWholeObjectDiffuseColour = true;
	mSphereMeshes[0]->wholeObjectDiffuseRGBA = glm::vec4(1.0f, 0.6f, 1.0f, 1.0f);
	mSphereMeshes[0]->bUseObjectDebugColour = true;
	mSphereMeshes[0]->objectDebugColourRGBA = glm::vec4(1.0f, 0.6f, 0.0f, 1.0f);
	mSphereMeshes[0]->bDontLight = true;
	mSphereMeshes[0]->bIsWireframe = false;
	mSphereMeshes[0]->clearTextureRatiosToZero();

	mSphereMeshes[1] = new cMesh();
	mSphereMeshes[1]->meshName = "Isosphere_Smooth_Normals.ply";
	mSphereMeshes[1]->positionXYZ = mParticleB->GetPosition();
	mSphereMeshes[1]->scale = glm::vec3(radius);// 1.0f;
	mSphereMeshes[1]->bUseWholeObjectDiffuseColour = true;
	mSphereMeshes[1]->wholeObjectDiffuseRGBA = glm::vec4(1.0f, 0.6f, 1.0f, 1.0f);
	mSphereMeshes[1]->bUseObjectDebugColour = true;
	mSphereMeshes[1]->objectDebugColourRGBA = glm::vec4(1.0f, 0.6f, 0.0f, 1.0f);
	mSphereMeshes[1]->bDontLight = true;
	mSphereMeshes[1]->bIsWireframe = false;
	mSphereMeshes[1]->clearTextureRatiosToZero();

	mSphereMeshes[2] = new cMesh();
	mSphereMeshes[2]->meshName = "Isosphere_Smooth_Normals.ply";
	mSphereMeshes[2]->positionXYZ = mParticleC->GetPosition();
	mSphereMeshes[2]->scale = glm::vec3(radius);// 1.0f;
	mSphereMeshes[2]->bUseWholeObjectDiffuseColour = true;
	mSphereMeshes[2]->wholeObjectDiffuseRGBA = glm::vec4(1.0f, 0.6f, 1.0f, 1.0f);
	mSphereMeshes[2]->bUseObjectDebugColour = true;
	mSphereMeshes[2]->objectDebugColourRGBA = glm::vec4(1.0f, 0.6f, 0.0f, 1.0f);
	mSphereMeshes[2]->bDontLight = true;
	mSphereMeshes[2]->bIsWireframe = false;
	mSphereMeshes[2]->clearTextureRatiosToZero();

	mSphereMeshes[3] = new cMesh();
	mSphereMeshes[3]->meshName = "Isosphere_Smooth_Normals.ply";
	mSphereMeshes[3]->positionXYZ = mParticleD->GetPosition();
	mSphereMeshes[3]->scale = glm::vec3(radius);// 1.0f;
	mSphereMeshes[3]->bUseWholeObjectDiffuseColour = true;
	mSphereMeshes[3]->wholeObjectDiffuseRGBA = glm::vec4(1.0f, 0.6f, 1.0f, 1.0f);
	mSphereMeshes[3]->bUseObjectDebugColour = true;
	mSphereMeshes[3]->objectDebugColourRGBA = glm::vec4(1.0f, 0.6f, 0.0f, 1.0f);
	mSphereMeshes[3]->bDontLight = true;
	mSphereMeshes[3]->bIsWireframe = false;
	mSphereMeshes[3]->clearTextureRatiosToZero();

	mSphereMeshes[4] = new cMesh();
	mSphereMeshes[4]->meshName = "Isosphere_Smooth_Normals.ply";
	mSphereMeshes[4]->positionXYZ = mParticleE->GetPosition();
	mSphereMeshes[4]->scale = glm::vec3(radius);// 1.0f;
	mSphereMeshes[4]->bUseWholeObjectDiffuseColour = true;
	mSphereMeshes[4]->wholeObjectDiffuseRGBA = glm::vec4(1.0f, 0.6f, 1.0f, 1.0f);
	mSphereMeshes[4]->bUseObjectDebugColour = true;
	mSphereMeshes[4]->objectDebugColourRGBA = glm::vec4(1.0f, 0.6f, 0.0f, 1.0f);
	mSphereMeshes[4]->bDontLight = true;
	mSphereMeshes[4]->bIsWireframe = false;
	mSphereMeshes[4]->clearTextureRatiosToZero();

	mSphereMeshes[5] = new cMesh();
	mSphereMeshes[5]->meshName = "Isosphere_Smooth_Normals.ply";
	mSphereMeshes[5]->positionXYZ = mParticleF->GetPosition();
	mSphereMeshes[5]->scale = glm::vec3(radius);// 1.0f;
	mSphereMeshes[5]->bUseWholeObjectDiffuseColour = true;
	mSphereMeshes[5]->wholeObjectDiffuseRGBA = glm::vec4(1.0f, 0.6f, 1.0f, 1.0f);
	mSphereMeshes[5]->bUseObjectDebugColour = true;
	mSphereMeshes[5]->objectDebugColourRGBA = glm::vec4(1.0f, 0.6f, 0.0f, 1.0f);
	mSphereMeshes[5]->bDontLight = true;
	mSphereMeshes[5]->bIsWireframe = false;
	mSphereMeshes[5]->clearTextureRatiosToZero();

	mSphereMeshes[6] = new cMesh();
	mSphereMeshes[6]->meshName = "Isosphere_Smooth_Normals.ply";
	mSphereMeshes[6]->positionXYZ = mParticleG->GetPosition();
	mSphereMeshes[6]->scale = glm::vec3(radius);// 1.0f;
	mSphereMeshes[6]->bUseWholeObjectDiffuseColour = true;
	mSphereMeshes[6]->wholeObjectDiffuseRGBA = glm::vec4(1.0f, 0.6f, 1.0f, 1.0f);
	mSphereMeshes[6]->bUseObjectDebugColour = true;
	mSphereMeshes[6]->objectDebugColourRGBA = glm::vec4(1.0f, 0.6f, 0.0f, 1.0f);
	mSphereMeshes[6]->bDontLight = true;
	mSphereMeshes[6]->bIsWireframe = false;
	mSphereMeshes[6]->clearTextureRatiosToZero();

	mSphereMeshes[7] = new cMesh();
	mSphereMeshes[7]->meshName = "Isosphere_Smooth_Normals.ply";
	mSphereMeshes[7]->positionXYZ = mParticleH->GetPosition();
	mSphereMeshes[7]->scale = glm::vec3(radius);// 1.0f;
	mSphereMeshes[7]->bUseWholeObjectDiffuseColour = true;
	mSphereMeshes[7]->wholeObjectDiffuseRGBA = glm::vec4(1.0f, 0.6f, 1.0f, 1.0f);
	mSphereMeshes[7]->bUseObjectDebugColour = true;
	mSphereMeshes[7]->objectDebugColourRGBA = glm::vec4(1.0f, 0.6f, 0.0f, 1.0f);
	mSphereMeshes[7]->bDontLight = true;
	mSphereMeshes[7]->bIsWireframe = false;
	mSphereMeshes[7]->clearTextureRatiosToZero();
	

}
cBoxEntity::~cBoxEntity()
{
	for (size_t idx = 0; idx < 8; idx++)
	{
		delete mParticles[idx];
	}
	for (size_t idx = 0; idx < 16; idx++)
	{
		delete mConstraints[idx];
	}
}

void cBoxEntity::AddToWorld(nPhysics::cParticleWorld* world)
{
	for (size_t idx = 0; idx < 8; idx++)
	{
		world->AddParticle(mParticles[idx]);
		::g_vec_pMeshes.push_back(this->mSphereMeshes[idx]);
	}
	for (size_t idx = 0; idx < 16; idx++)
	{
		world->AddContactGenerator(mConstraints[idx]);
	}
}
void cBoxEntity::RemoveFromWorld(nPhysics::cParticleWorld* world)
{
	for (size_t idx = 0; idx < 8; idx++)
	{
		world->RemoveParticle(mParticles[idx]);
	}
	for (size_t idx = 0; idx < 16; idx++)
	{
		world->RemoveContactGenerator(mConstraints[idx]);
	}
}

void cBoxEntity::Update()
{
	//nInput::cKey* keyA = nInput::cInputManager::GetInstance()->ListenToKey(nInput::KeyCode::KEY_A);
	//if (keyA->IsJustPressed())
	//{
	//	mParticleA->ApplyImpulse(glm::vec3(0.0f, 15.0f, 0.0f));
	//}

	for (size_t idx = 0; idx < 8; idx++)
	{
		mSphereMeshes[idx]->positionXYZ = mParticles[idx]->GetPosition();
	}
}