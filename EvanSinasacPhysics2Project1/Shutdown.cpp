#include "globalThings.h"
//Stuff done in class with Michael Feeney

// Deletes global things, etc. 
bool g_ShutDown(GLFWwindow* pWindow)
{

	delete ::g_pShaderManager;

	delete ::g_pVAOManager;

	delete ::g_pTheLights;

	//delete ::g_pFlyCamera;

	delete ::g_pTextureManager;

	delete ::g_rbPhysicsFactory;
	delete ::g_rbPhysicsWorld;

	return true;
}