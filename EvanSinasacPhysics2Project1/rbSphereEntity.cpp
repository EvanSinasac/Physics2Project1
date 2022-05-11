#include "rbSphereEntity.h"
#include <GdpPhysics/interfaces/shapes.h>
#include <GdpPhysics/interfaces/cRigidBodyDesc.h>

rbSphereEntity::rbSphereEntity(float radius, float mass, glm::vec3 pos)
	: m_Radius(radius)
	, m_Mass(mass)
{
	// Mesh
	m_Mesh = new cMesh();
	m_Mesh->meshName = "Isosphere_Smooth_Normals.ply";
	m_Mesh->positionXYZ = pos;
	m_Mesh->scale = glm::vec3(m_Radius);// 1.0f;
	m_Mesh->bUseWholeObjectDiffuseColour = true;
	m_Mesh->wholeObjectDiffuseRGBA = glm::vec4(1.0f, 0.6f, 1.0f, 1.0f);
	m_Mesh->bUseObjectDebugColour = true;
	m_Mesh->objectDebugColourRGBA = glm::vec4(1.0f, 0.6f, 0.0f, 1.0f);
	m_Mesh->bDontLight = true;
	m_Mesh->bIsWireframe = false;
	m_Mesh->clearTextureRatiosToZero();

	// Rigidbody
	gdpPhysics::iShape* sphereShape = new gdpPhysics::SphereShape(m_Radius);
	// This stuff can be inputted from the constructor but these are decent defaults
	gdpPhysics::cRigidBodyDesc sphereDesc;
	sphereDesc.damping = 0.001f;
	sphereDesc.IsStatic = false;
	sphereDesc.mass = m_Mass;
	sphereDesc.position = pos;
	sphereDesc.velocity = glm::vec3(0.0f);
	sphereDesc.restitution = 0.8f;

	gdpPhysics::iRigidBody* newRigidBody = ::g_rbPhysicsFactory->CreateRigidBody(sphereDesc, sphereShape);
	m_RB = new RigidBody();
	m_RB->ptr = newRigidBody;

	// oh, guess I'm doing this instead of using the AddToWorld function...
	// should still make the RemoveFromWorld just in case...
	//::g_rbPhysicsWorld->AddRigidBody(newRigidBody);
	::g_rbPhysicsWorld->AddRigidBody(m_RB->ptr);
	::g_vec_pMeshes.push_back(m_Mesh);

}
rbSphereEntity::~rbSphereEntity(void)
{

}


void rbSphereEntity::Update()
{
	glm::vec3 pos;
	this->m_RB->ptr->GetPosition(pos);
	this->m_Mesh->positionXYZ = pos;
}