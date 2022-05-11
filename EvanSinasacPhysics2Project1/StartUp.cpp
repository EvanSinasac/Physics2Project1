#include "globalThings.h"
//Stuff done in class with Michael Feeney
#include "CollisionListener.h"

bool g_StartUp(GLFWwindow* pWindow)
{

	//::g_pFlyCamera = new cFlyCamera();

	// Create the shader manager
	::g_pShaderManager = new cShaderManager();

	::g_pTheLights = new cLightManager();

	::g_pVAOManager = new cVAOManager();

	::g_pTextureManager = new cBasicTextureManager();

	::g_rbPhysicsFactory = new gdpPhysics::PhysicsFactory();
	::g_rbPhysicsWorld = g_rbPhysicsFactory->CreateWorld();
	::g_rbPhysicsWorld->RegisterCollisionListener(new CollisionListener());
	::g_rbPhysicsWorld->SetGravity(glm::vec3(0.0f, -9.81f, 0.0f));

	return true;
}
