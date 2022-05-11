#include "globalThings.h"
//Stuff done in class with Michael Feeney

//cFlyCamera* g_pFlyCamera = NULL;

// particle world
std::vector<nPhysics::cParticle*> g_vec_pProjectiles;
nPhysics::cParticleWorld* g_world = new nPhysics::cParticleWorld(1000);
// rigidbody
// done in startup
gdpPhysics::iPhysicsFactory* g_rbPhysicsFactory;// = new gdpPhysics::PhysicsFactory();
gdpPhysics::iPhysicsWorld* g_rbPhysicsWorld;// = g_rbPhysicsFactory->CreateWorld();
gdpPhysics::iRigidBody* g_RigidBody;
// entities
std::vector<cEntity*> g_vec_pEntities;
int g_SelectedEntityIndex = 0;
glm::vec4 g_notSelectedColour = glm::vec4(1.0f, 0.6f, 0.0f, 1.0f);
glm::vec4 g_SelectedColour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

// Physics and Simulation 1 Final Project stuff, unused for physics 2 but removing it makes too much cleanup
// (would have to remove the config reader and basically all of or most of the entities)
float g_cannonPitch = 3.0f * glm::pi<float>() / 4.0f;
float g_cannonYaw = glm::pi<float>();
float g_cannonMaxPitch = 158.0f;
float g_cannonMinPitch = 90.0f;
float g_cannonMaxYaw = 225.0f;
float g_cannonMinYaw = 135.0f;

cConfigReaderJSON g_config;

//glm::vec3 g_cameraEye = glm::vec3(0.0f, 0.0f, +4.0f);
//glm::vec3 g_cameraAt = glm::vec3(0.0f, 0.0f, 0.0f);
// Default starting values (TODO: change)
glm::vec3 cameraEye = glm::vec3(0.0f, 15.0f, -30.0f);
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraForward = cameraTarget - cameraEye;

cVAOManager* g_pVAOManager = NULL;
cShaderManager* g_pShaderManager = NULL;
cBasicTextureManager* g_pTextureManager = NULL;

cLightManager* g_pTheLights = NULL;
// This got moved into the light manager class
//extern cLightHelper* g_pTheLightHelper;


// List of objects to draw
std::vector< cMesh* > g_vec_pMeshes;


cMesh* g_pDebugSphere = NULL;
bool g_bShowDebugShere = true;


unsigned int g_selectedObject = 0;
unsigned int g_selectedLight = 0;


// This will be printed in the title bar
std::string g_TitleText = "";





bool g_FindObjectByUniqueID(unsigned int uniqueID_toFind, cMesh*& theObjectIFound);



cMesh* g_findObjectByUniqueID(unsigned int uniqueID_toFind)
{
    for (unsigned int index = 0; index != ::g_vec_pMeshes.size(); index++)
    {
        if (::g_vec_pMeshes[index]->getUniqueID() == uniqueID_toFind)
        {
            return ::g_vec_pMeshes[index];
        }
    }
    return NULL;
}

bool g_findObjectByUniqueID(unsigned int uniqueID_toFind, cMesh& theObjectIFound)
{
    for (unsigned int index = 0; index != ::g_vec_pMeshes.size(); index++)
    {
        if (::g_vec_pMeshes[index]->getUniqueID() == uniqueID_toFind)
        {
            // Dereferences and returns a stack based copy
            theObjectIFound = *(::g_vec_pMeshes[index]);
            return true;
        }
    }
    return false;
}

bool g_FindObjectByUniqueID(unsigned int uniqueID_toFind, cMesh*& theObjectIFound)
{
    for (unsigned int index = 0; index != ::g_vec_pMeshes.size(); index++)
    {
        if (::g_vec_pMeshes[index]->getUniqueID() == uniqueID_toFind)
        {
            // Returns a pointer to the object
            theObjectIFound = ::g_vec_pMeshes[index];
            return true;
        }
    }
    return false;
}

// If not found, return NULL (0)
cMesh* g_findObjectByFriendlyName(std::string NametoFind)
{
    for (unsigned int index = 0; index != ::g_vec_pMeshes.size(); index++)
    {
        cMesh* pMeshToTest = ::g_vec_pMeshes[index];

        // Is functionally the same thing as using a reference:
        //cMesh& meshToTest = g_vecMeshes[index];

        if (pMeshToTest->friendlyName == NametoFind)
        {
            return pMeshToTest;
        }
    }
    // DIDN'T find it, return NULL
    return NULL;
}

cMesh* g_FindObjectByUniqueID(unsigned int uniqueID_toFind)
{
    for (unsigned int index = 0; index != ::g_vec_pMeshes.size(); index++)
    {
        cMesh* pMeshToTest = ::g_vec_pMeshes[index];

        // Is functionally the same thing as using a reference:
        //cMesh& meshToTest = g_vecMeshes[index];

        if (pMeshToTest->getUniqueID() == uniqueID_toFind)
        {
            return pMeshToTest;
        }
    }
    // DIDN'T find it, return NULL
    return NULL;
}


