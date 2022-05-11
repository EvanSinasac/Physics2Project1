//Evan Sinasac - 1081418
//INFO6022 Physics and Simulation II Project 1
//main.cpp description:
//					Yeah, I'm taking the Physics and Simulation I & Configuration final program and making modifications
//					to incorporate the rigidbody system we've been working on.  As such, there is a lot of messy code
//					here that is related to it.  I'm keeping it because I want to handle rigidbodies in a similar (but better) fashion.
//					The main purpose of project 1 is to incorporate the rigidbody system and demonstrate various collision
//					detection between spheres of different size/mass with the spheres trapped in an enclosed area
//					(enclosed by planes)


// Particle physics (namespace nPhysics)
#include <physics/cParticleWorld.h>
#include <physics/random_helpers.h>
#include <physics/particle_contact_generators.h>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm>

#include "GLCommon.h"
#include "GLMCommon.h"
#include "globalThings.h"

// Physics 2 Project 1
#include "rbSphereEntity.h"
#include <GdpPhysics/interfaces/shapes.h>
#include <GdpPhysics/interfaces/cRigidBodyDesc.h>


//Globals;
float lastX = 600.f;
float lastY = 320.f;
bool firstMouse = true;
float cameraYaw = 90.f;
float cameraPitch = 0.f;

double deltaTime = 0.0;
double lastFrame = 0.0;

int numberOfTransparentObjects = 0;


std::vector<std::string> modelLocations;

//Function signature for DrawObject()
void DrawObject(
	cMesh* pCurrentMesh,
	glm::mat4 matModel,
	GLint matModel_Location,
	GLint matModelInverseTranspose_Location,
	GLuint program,
	cVAOManager* pVAOManager);


//callbacks
static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

// Decided not to use loadWorldFile for Project 3 but I didn't want to remove it completely just in case
bool loadWorldFile();
bool loadLightsFile();


int main(int argc, char** argv)
{
	GLFWwindow* pWindow;

	GLuint program = 0;		//0 means no shader program

	GLint mvp_location = -1;
	std::stringstream ss;


	// This is the old particle physics stuff, I'm treating rigid body physics very similarly so this is still here for reference
	// Physics Project 3 stuff is basically going to be converted to rigidbody stuff
	// *******************************************
	// Physics Project 3 stuff
	//std::vector<nPhysics::cParticle*> projectiles;
	//nPhysics::cParticleWorld* world = new nPhysics::cParticleWorld(50);

	//nPhysics::cPlaneParticleContactGenerator* groundGenerator = new nPhysics::cPlaneParticleContactGenerator(glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
	//::g_world->AddContactGenerator(groundGenerator);

	////nPhysics::cPlaneParticleContactGenerator ceilWallGenerator(glm::vec3(0.0f, -1.0f, 0.0f), -5.0f);
	////::g_world->AddContactGenerator(&ceilWallGenerator);

	//// For some reason the distance needs to be negative for the "walls" of the box, but positive works for the "ground"
	//nPhysics::cPlaneParticleContactGenerator* leftWallGenerator = new nPhysics::cPlaneParticleContactGenerator(glm::vec3(-1.0f, 0.0f, 0.0f), -25.0f);
	//::g_world->AddContactGenerator(leftWallGenerator);

	//nPhysics::cPlaneParticleContactGenerator* rightWallGenerator = new nPhysics::cPlaneParticleContactGenerator(glm::vec3(1.0f, 0.0f, 0.0f), -25.0f);
	//::g_world->AddContactGenerator(rightWallGenerator);

	//nPhysics::cPlaneParticleContactGenerator* backWallGenerator = new nPhysics::cPlaneParticleContactGenerator(glm::vec3(0.0f, 0.0f, -1.0f), -25.0f);
	//::g_world->AddContactGenerator(backWallGenerator);

	//nPhysics::cPlaneParticleContactGenerator* frontWallGenerator = new nPhysics::cPlaneParticleContactGenerator(glm::vec3(0.0f, 0.0f, 1.0f), -25.0f);
	//::g_world->AddContactGenerator(frontWallGenerator);

	//// And the particle collision detection
	//nPhysics::cParticle2ParticleContactGenerator* particleCollider = new nPhysics::cParticle2ParticleContactGenerator();
	//::g_world->AddContactGenerator(particleCollider);

	// *******************************************

	glfwSetErrorCallback(GLFW_error_callback);

	if (!glfwInit())
	{
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	pWindow = glfwCreateWindow(1200, 640, "Physics Project 3", NULL, NULL);

	if (!pWindow)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(pWindow, GLFW_key_callback);

	glfwSetCursorEnterCallback(pWindow, GLFW_cursor_enter_callback);
	glfwSetCursorPosCallback(pWindow, GLFW_cursor_position_callback);
	glfwSetScrollCallback(pWindow, GLFW_scroll_callback);
	glfwSetMouseButtonCallback(pWindow, GLFW_mouse_button_callback);
	glfwSetWindowSizeCallback(pWindow, GLFW_window_size_callback);

	// Physics 2 Project 1, camera will rotate around the sphere's in the scene, so no need for this fly camera
	// Even though I like it very much and it's very nice to look around the scene with :(
	//glfwSetCursorPosCallback(pWindow, mouse_callback);

	// Keep the cursor visible since we're not using the fly camera anymore
	//glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwMakeContextCurrent(pWindow);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);


	GLint max_uniform_location = 0;
	GLint* p_max_uniform_location = NULL;
	p_max_uniform_location = &max_uniform_location;
	glGetIntegerv(GL_MAX_UNIFORM_LOCATIONS, p_max_uniform_location);

	std::cout << "GL_MAX_UNIFORM_LOCATIONS: " << max_uniform_location << std::endl;

	// Create global things
	::g_StartUp(pWindow);


	// Shaders with textures and lights, probably going to disable lights unless it looks OK
	cShaderManager::cShader vertShader;
	ss.str("");
	ss << SOLUTION_DIR << "common\\assets\\shaders\\vertShader_01.glsl";
	vertShader.fileName = ss.str();

	cShaderManager::cShader geomShader;
	ss.str("");
	ss << SOLUTION_DIR << "common\\assets\\shaders\\geomShader.glsl";
	geomShader.fileName = ss.str();;

	cShaderManager::cShader fragShader;
	ss.str("");
	ss << SOLUTION_DIR << "common\\assets\\shaders\\fragShader_01.glsl";
	fragShader.fileName = ss.str();

	if (::g_pShaderManager->createProgramFromFile("Shader#1", vertShader, geomShader, fragShader))
	{
		std::cout << "Shader compiled OK" << std::endl;
		// 
		// Set the "program" variable to the one the Shader Manager used...
		program = ::g_pShaderManager->getIDFromFriendlyName("Shader#1");
	}
	else
	{
		std::cout << "Error making shader program: " << std::endl;
		std::cout << ::g_pShaderManager->getLastError() << std::endl;
	}


	// Select the shader program we want to use
	// (Note we only have one shader program at this point)
	glUseProgram(program);

	// TODO (Eventually): Go make this a function and set all the uniform locations at once so I never have to look
	// for them again and can just call the pShaderProc whenever I need to set something
	// *******************************************************
	// Now, I'm going to "load up" all the uniform locations
	// (This was to show how a map could be used)
	// Stuff we've started doing in graphics to make things faster 
	cShaderManager::cShaderProgram* pShaderProc = ::g_pShaderManager->pGetShaderProgramFromFriendlyName("Shader#1");
	int theUniformIDLoc = -1;
	theUniformIDLoc = glGetUniformLocation(program, "matModel");

	pShaderProc->mapUniformName_to_UniformLocation["matModel"] = theUniformIDLoc;

	// Or...
	pShaderProc->mapUniformName_to_UniformLocation["matModel"] = glGetUniformLocation(program, "matModel");

	pShaderProc->mapUniformName_to_UniformLocation["matView"] = glGetUniformLocation(program, "matView");
	pShaderProc->mapUniformName_to_UniformLocation["matProjection"] = glGetUniformLocation(program, "matProjection");
	pShaderProc->mapUniformName_to_UniformLocation["matModelInverseTranspose"] = glGetUniformLocation(program, "matModelInverseTranspose");

	// *******************************************************

	//GLint mvp_location = -1;
	mvp_location = glGetUniformLocation(program, "MVP");

	// Get "uniform locations" (aka the registers these are in)
	GLint matModel_Location = glGetUniformLocation(program, "matModel");
	//	GLint matView_Location = glGetUniformLocation(program, "matView");
	GLint matProjection_Location = glGetUniformLocation(program, "matProjection");
	GLint matModelInverseTranspose_Location = glGetUniformLocation(program, "matModelInverseTranspose");

	GLint bDiscardTransparencyWindowsON_LocID = glGetUniformLocation(program, "bDiscardTransparencyWindowsOn");

	//Lights stuff here, this is just how to set light information, I'm keeping this around just so I have reference to it
	// but for the most part, the loadLightsFile will handle it from now on and I'll just make changes to the function
	// and the lights file

	//    	vec4 param1;	// x = lightType, y = inner angle, z = outer angle, w = TBD
//	                // 0 = pointlight
//					// 1 = spot light
//					// 2 = directional light
	//::g_pTheLights->theLights[0].position = glm::vec4(0.0f, 110.0f, 0.0f, 1.0f);
	////::g_pTheLights->theLights[0].diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	////::g_pTheLights->theLights[0].specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	//::g_pTheLights->theLights[0].param1.x = 0.0f;	// Pointlight
	////::g_pTheLights->theLights[0].param1.y = 10.0f;   // Inner
	////::g_pTheLights->theLights[0].param1.z = 12.0f;   // Outer
	////::g_pTheLights->theLights[0].direction = glm::vec4(1.0f, -0.1f, 0.0f, 1.0f);
	//::g_pTheLights->theLights[0].atten.x = 1.0f;
	//::g_pTheLights->theLights[0].atten.y = 0.0000000000001f;
	//::g_pTheLights->theLights[0].atten.z = 0.00000000000001f;
	//::g_pTheLights->TurnOnLight(0);

	// loads all the lights from a file instead of individually setting them here
	if (loadLightsFile())
	{
		std::cout << "loadLightsFile finished ok!" << std::endl;
	}
	else
	{
		std::cout << "loadLightsFile did NOT finish ok!  Aborting!" << std::endl;
		return -1;
	}

	// Get the uniform locations of the light shader values
	::g_pTheLights->SetUpUniformLocations(program);

	// Set the default file path for the models in the scene
	ss.str("");
	ss << SOLUTION_DIR << "common\\assets\\models\\";

	::g_pVAOManager->setFilePath(ss.str());

	// Load ALL the models
	// Some projects I make a function and change what models are being made there, for this I'm not going to have that
	// many so we're just doing it here
	modelLocations.push_back("SM_Env_Floor_01_xyz_n_rgba_uv.ply");
	modelLocations.push_back("SM_Env_Floor_04_xyz_n_rgba_uv.ply");
	modelLocations.push_back("Isosphere_Smooth_Normals.ply");
	modelLocations.push_back("ISO_Sphere_flat_4div_xyz_n_rgba_uv.ply");
	//modelLocations.push_back("Turret_Simple_01_xyz_n_rgba_uv.ply");				// not going to need the turret for this project
	modelLocations.push_back("SM_Env_Construction_Wall_01_xyz_n_rgba_uv.ply");
	modelLocations.push_back("Isosphere_Smooth_Inverted_Normals_for_SkyBox.ply");

	unsigned int totalVerticesLoaded = 0;
	unsigned int totalTrianglesLoaded = 0;
	for (std::vector<std::string>::iterator itModel = modelLocations.begin(); itModel != modelLocations.end(); itModel++)
	{
		sModelDrawInfo theModel;
		std::string modelName = *itModel;
		std::cout << "Loading " << modelName << "...";
		if (!::g_pVAOManager->LoadModelIntoVAO(modelName, theModel, program))
		{
			std::cout << "didn't work because: " << std::endl;
			std::cout << ::g_pVAOManager->getLastError(true) << std::endl;
		}
		else
		{
			std::cout << "OK." << std::endl;
			std::cout << "\t" << theModel.numberOfVertices << " vertices and " << theModel.numberOfTriangles << " triangles loaded." << std::endl;
			totalTrianglesLoaded += theModel.numberOfTriangles;
			totalVerticesLoaded += theModel.numberOfVertices;
		}
	} //end of for (std::vector<std::string>::iterator itModel

	std::cout << "Done loading models." << std::endl;
	std::cout << "Total vertices loaded = " << totalVerticesLoaded << std::endl;
	std::cout << "Total triangles loaded = " << totalTrianglesLoaded << std::endl;

	// Make static meshes OR start loading the world file
	//cMesh* cannonFloorMesh = new cMesh();
	//cannonFloorMesh->meshName = "SM_Env_Floor_01_xyz_n_rgba_uv.ply";
	//cannonFloorMesh->positionXYZ = glm::vec3(2.5f, 0.0f, -17.5f);
	//cannonFloorMesh->orientationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
	//cannonFloorMesh->scale = glm::vec3(1.0f);
	//cannonFloorMesh->bUseWholeObjectDiffuseColour = false;
	//cannonFloorMesh->wholeObjectDiffuseRGBA = glm::vec4(0.88f, 0.88f, 0.88f, 1.0f);
	//cannonFloorMesh->alphaTransparency = 1.0f;
	//cannonFloorMesh->bDontLight = false;

	//cannonFloorMesh->clearTextureRatiosToZero();
	//cannonFloorMesh->textureNames[1] = "SpaceInteriors_Texture.bmp";
	//cannonFloorMesh->textureRatios[1] = 1.0f;

	//::g_vec_pMeshes.push_back(cannonFloorMesh);

	//World file stuff here
	if (loadWorldFile())
	{
		std::cout << "loadWorldFile finished OK" << std::endl;
	}
	else
	{
		std::cout << "loadWorldFile did not finish OK, aborting" << std::endl;
		return -1;
	}

	// So, I've made the RigidBody physics stuff, and made them global pointers...
	// So somewhere I need to make the new sphere entities...
	// Which means I either have to incorporate the lukgus Entities (which would mean implementing the entire component stuff)
	// Or make my own version similar to how I handled the particle entities, where each entity contains all it's information
	// And then some world or manager that updates all the entities
	// And I also need to make the planes

	// *******************************************************************
	// RigidBodies

	// Project 2, 5 spheres with different radiuses and masses
	rbSphereEntity* rbSphere1 = new rbSphereEntity(1.0f, 10.0f, glm::vec3(0.0f, 10.0f, 0.0f));
	::g_vec_pEntities.push_back(rbSphere1);
	::g_SelectedEntityIndex = 0;
	((rbSphereEntity*)::g_vec_pEntities[::g_SelectedEntityIndex])->m_Mesh->objectDebugColourRGBA = ::g_SelectedColour;

	rbSphereEntity* rbSphere2 = new rbSphereEntity(5.0f, 50.0f, glm::vec3(10.0f, 10.0f, 10.0f));
	::g_vec_pEntities.push_back(rbSphere2);

	rbSphereEntity* rbSphere3 = new rbSphereEntity(0.5f, 5.0f, glm::vec3(-10.0f, 10.0f, 10.0f));
	::g_vec_pEntities.push_back(rbSphere3);

	rbSphereEntity* rbSphere4 = new rbSphereEntity(3.0f, 30.0f, glm::vec3(10.0f, 10.0f, -10.0f));
	::g_vec_pEntities.push_back(rbSphere4);

	rbSphereEntity* rbSphere5 = new rbSphereEntity(2.5f, 25.0f, glm::vec3(-10.0f, 10.0f, -10.0f));
	::g_vec_pEntities.push_back(rbSphere5);

	// *******************************************************************
	// Planes
	gdpPhysics::iShape* groundPlaneShape = new gdpPhysics::PlaneShape(0, glm::vec3(0.0f, 1.0f, 0.0f));
	gdpPhysics::cRigidBodyDesc groundPlaneDesc;
	groundPlaneDesc.damping = 0.f;
	groundPlaneDesc.IsStatic = true;
	groundPlaneDesc.mass = 1.f;
	groundPlaneDesc.position = glm::vec3(0.f);
	groundPlaneDesc.velocity = glm::vec3(0.f);
	groundPlaneDesc.friction = 0.8f;

	gdpPhysics::iRigidBody* groundRigidBody = g_rbPhysicsFactory->CreateRigidBody(groundPlaneDesc, groundPlaneShape);

	// Create RigidBody Component, and store the pointer
	RigidBody* groundRigidBodyCmp = new RigidBody();	// ground->AddComponent<RigidBody>();
	groundRigidBodyCmp->ptr = groundRigidBody;

	// Add the Rigid Body to the physics world
	g_rbPhysicsWorld->AddRigidBody(groundRigidBody);

	//
	gdpPhysics::iShape* rightPlaneShape = new gdpPhysics::PlaneShape(25.0f, glm::vec3(-1.0f, 0.0f, 0.0f));
	gdpPhysics::cRigidBodyDesc rightPlaneDesc;
	rightPlaneDesc.damping = 0.f;
	rightPlaneDesc.IsStatic = true;
	rightPlaneDesc.mass = 1.f;
	rightPlaneDesc.position = glm::vec3(0.f);
	rightPlaneDesc.velocity = glm::vec3(0.f);
	rightPlaneDesc.friction = 0.8f;

	gdpPhysics::iRigidBody* rightRigidBody = g_rbPhysicsFactory->CreateRigidBody(rightPlaneDesc, rightPlaneShape);

	// Create RigidBody Component, and store the pointer
	RigidBody* rightRigidBodyCmp = new RigidBody();	// ground->AddComponent<RigidBody>();
	rightRigidBodyCmp->ptr = rightRigidBody;

	// Add the Rigid Body to the physics world
	g_rbPhysicsWorld->AddRigidBody(rightRigidBody);

	//
	gdpPhysics::iShape* leftPlaneShape = new gdpPhysics::PlaneShape(25.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	gdpPhysics::cRigidBodyDesc leftPlaneDesc;
	leftPlaneDesc.damping = 0.f;
	leftPlaneDesc.IsStatic = true;
	leftPlaneDesc.mass = 1.f;
	leftPlaneDesc.position = glm::vec3(0.f);
	leftPlaneDesc.velocity = glm::vec3(0.f);
	leftPlaneDesc.friction = 0.8f;

	gdpPhysics::iRigidBody* leftRigidBody = g_rbPhysicsFactory->CreateRigidBody(leftPlaneDesc, leftPlaneShape);

	// Create RigidBody Component, and store the pointer
	RigidBody* leftRigidBodyCmp = new RigidBody();	// ground->AddComponent<RigidBody>();
	leftRigidBodyCmp->ptr = leftRigidBody;

	// Add the Rigid Body to the physics world
	g_rbPhysicsWorld->AddRigidBody(leftRigidBody);

	//
	gdpPhysics::iShape* backPlaneShape = new gdpPhysics::PlaneShape(25.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	gdpPhysics::cRigidBodyDesc backPlaneDesc;
	backPlaneDesc.damping = 0.f;
	backPlaneDesc.IsStatic = true;
	backPlaneDesc.mass = 1.f;
	backPlaneDesc.position = glm::vec3(0.f);
	backPlaneDesc.velocity = glm::vec3(0.f);
	backPlaneDesc.friction = 0.8f;

	gdpPhysics::iRigidBody* backRigidBody = g_rbPhysicsFactory->CreateRigidBody(backPlaneDesc, backPlaneShape);

	// Create RigidBody Component, and store the pointer
	RigidBody* backRigidBodyCmp = new RigidBody();	// ground->AddComponent<RigidBody>();
	backRigidBodyCmp->ptr = backRigidBody;

	// Add the Rigid Body to the physics world
	g_rbPhysicsWorld->AddRigidBody(backRigidBody);

	//
	gdpPhysics::iShape* frontPlaneShape = new gdpPhysics::PlaneShape(25.0f, glm::vec3(0.0f, 0.0f, -1.0f));
	gdpPhysics::cRigidBodyDesc frontPlaneDesc;
	frontPlaneDesc.damping = 0.f;
	frontPlaneDesc.IsStatic = true;
	frontPlaneDesc.mass = 1.f;
	frontPlaneDesc.position = glm::vec3(0.f);
	frontPlaneDesc.velocity = glm::vec3(0.f);
	frontPlaneDesc.friction = 0.8f;

	gdpPhysics::iRigidBody* frontRigidBody = g_rbPhysicsFactory->CreateRigidBody(frontPlaneDesc, frontPlaneShape);

	// Create RigidBody Component, and store the pointer
	RigidBody* frontRigidBodyCmp = new RigidBody();	// ground->AddComponent<RigidBody>();
	frontRigidBodyCmp->ptr = frontRigidBody;

	// Add the Rigid Body to the physics world
	g_rbPhysicsWorld->AddRigidBody(frontRigidBody);


	// *******************************************************************

	// Particle physics entities, removed but not forgotten
	// After making the static meshes, we make the entities, these entities are going to be replaced by ones that use rigidbodies
	// But I'm keeping them here for now for reference to how I handle them
	/*cHangingChainEntity* hangingChainEntity = new cHangingChainEntity(g_config.GetHCStartPos(), g_config.GetHCJointRadius(),
		g_config.GetHCDistBetweenJoints(), g_config.GetHCNumOfJoints(),
		g_config.GetHCNumOfConstraints());

	hangingChainEntity->AddToWorld(g_world);

	cSpringParticle* springEntity = new cSpringParticle(g_config.GetSpringStartPos(), g_config.GetSpringAnchorPos(),
		g_config.GetSpringRadius(), g_config.GetSpringConstant(), g_config.GetSpringRestLength());
	springEntity->AddToWorld(g_world);


	cBoxEntity* boxEntity = new cBoxEntity(::g_config.GetBEStartPos(), ::g_config.GetBEJointRadius(), ::g_config.GetBEDistBetweenJoints());
	boxEntity->AddToWorld(::g_world);


	cSpinningBladeEntity* spinningBladeEntity = new cSpinningBladeEntity(::g_config.GetSBStartPos(),
		::g_config.GetSBJointRadius(), ::g_config.GetSBDistFromStart(), ::g_config.GetSBLockedAxis());
	spinningBladeEntity->AddToWorld(::g_world);


	cTarget* targetEntity = new cTarget(::g_config.GetTargetStartPos(), ::g_config.GetTargetRadius());
	targetEntity->AddToWorld(::g_world);*/



	// Transparent objects get made last (and sorted before being drawn)


	//Michael Feeney's BMP texture mapping, this is basically forever unchanged until I either learn or implement a different texture manager
	//// Load the textures
	ss.str("");
	ss << SOLUTION_DIR << "common\\assets\\textures\\";
	::g_pTextureManager->SetBasePath(ss.str());

	if (::g_pTextureManager->Create2DTextureFromBMPFile("SpaceInteriors_Texture.bmp", true))
		//if (::g_pTextureManager->Create2DTextureFromBMPFile("Pebbleswithquarzite.bmp", true))
	{
		std::cout << "Loaded the texture" << std::endl;
	}
	else
	{
		std::cout << "DIDN'T load the texture" << std::endl;
	}

	::g_pTextureManager->Create2DTextureFromBMPFile("SpaceInteriors_Emmision.bmp", true);
	::g_pTextureManager->Create2DTextureFromBMPFile("WorldMap.bmp", true);
	::g_pTextureManager->Create2DTextureFromBMPFile("2k_jupiter.bmp", true);

	::g_pTextureManager->Create2DTextureFromBMPFile("Wall_Atlas_01_ID.bmp", true);
	::g_pTextureManager->Create2DTextureFromBMPFile("Wall_Atlas_03_ID.bmp", true);
	::g_pTextureManager->Create2DTextureFromBMPFile("Wall_Atlas_08_ID.bmp", true);
	::g_pTextureManager->Create2DTextureFromBMPFile("Wall_Atlas_11_ID.bmp", true);

	// Default don't have a texture
	if (::g_pTextureManager->Create2DTextureFromBMPFile("BrightColouredUVMap.bmp", true))
		//if (::g_pTextureManager->Create2DTextureFromBMPFile("Pebbleswithquarzite.bmp", true))
	{
		std::cout << "Loaded the texture" << std::endl;
	}
	else
	{
		std::cout << "DIDN'T load the texture" << std::endl;
	}

	// Add a skybox texture, same with these, this is just how we do skyboxes until I learn another way
	std::string errorTextString;
	ss.str("");
	ss << SOLUTION_DIR << "common\\assets\\textures\\cubemaps\\";
	::g_pTextureManager->SetBasePath(ss.str());		// update base path to cube texture location

	if (!::g_pTextureManager->CreateCubeTextureFromBMPFiles("TropicalSunnyDay",
		"TropicalSunnyDayRight2048.bmp",	/* +X */	"TropicalSunnyDayLeft2048.bmp" /* -X */,
		"TropicalSunnyDayUp2048.bmp",		/* +Y */	"TropicalSunnyDayDown2048.bmp" /* -Y */,
		"TropicalSunnyDayFront2048.bmp",	/* +Z */	"TropicalSunnyDayBack2048.bmp" /* -Z */,
		true, errorTextString))
	{
		std::cout << "Didn't load because: " << errorTextString << std::endl;
	}


	if (!::g_pTextureManager->CreateCubeTextureFromBMPFiles("Space01",
		"SpaceBox_right1_posX.bmp",		/* +X */	"SpaceBox_left2_negX.bmp" /* -X */,
		"SpaceBox_top3_posY.bmp",		/* +Y */	"SpaceBox_bottom4_negY.bmp" /* -Y */,
		"SpaceBox_front5_posZ.bmp",		/* +Z */	"SpaceBox_back6_negZ.bmp" /* -Z */,
		true, errorTextString))
	{
		std::cout << "Didn't load because: " << errorTextString << std::endl;
	}

	if (!::g_pTextureManager->CreateCubeTextureFromBMPFiles("City01",
		"city_lf.bmp",		/* +X */	"city_rt.bmp" /* -X */,
		"city_dn.bmp",		/* +Y */	"city_up.bmp" /* -Y */,
		"city_ft.bmp",		/* +Z */	"city_bk.bmp" /* -Z */,
		true, errorTextString))
	{
		std::cout << "Didn't load because: " << errorTextString << std::endl;
	}

	if (!::g_pTextureManager->CreateCubeTextureFromBMPFiles("Skyrim",
		"Skyrim_Right.bmp",		/* +X */	"Skyrim_Left.bmp" /* -X */,
		"Skyrim_Top.bmp",		/* +Y */	"Skyrim_Bottom.bmp" /* -Y */,
		"Skyrim_Forward.bmp",		/* +Z */	"Skyrim_Back.bmp" /* -Z */,
		true, errorTextString))
	{
		std::cout << "Didn't load because: " << errorTextString << std::endl;
	}

	// Make sphere for "skybox" before world file
	cMesh* sphereSky = new cMesh();
	//sphereSky->meshName = "Isosphere_Smooth_Normals.ply";
	// We are using a sphere with INWARD facing normals, so we see the "back" of the sphere
	sphereSky->meshName = "Isosphere_Smooth_Inverted_Normals_for_SkyBox.ply";
	// 2 main ways we can do a skybox:
	//
	// - Make a sphere really big, so everything fits inside
	// (be careful of the far clipping plane)
	//
	// - Typical way is:
	//	- Turn off the depth test
	//	- Turn off the depth function (i.e. writing to the depth buffer)
	//	- Draw the skybox object (which can be really small, since it's not interacting with the depth buffer)
	//	- Once drawn:
	//		- Turn on the depth function
	//		- Turn on the depth test

	sphereSky->positionXYZ = ::cameraEye;	//glm::vec3(100.0f, -250.0f, 100.0f);
	//sphereSky->orientationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
	sphereSky->scale = glm::vec3(10000.0f, 10000.0f, 10000.0f);
	//sphereSky->bUseWholeObjectDiffuseColour = false;
	//sphereSky->wholeObjectDiffuseRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	sphereSky->bDontLight = true;
	sphereSky->clearTextureRatiosToZero();
	//sphereSky->textureNames[1] = "2k_jupiter.bmp";
	sphereSky->textureRatios[1] = 1.0f;


	// Not using this camera for Physics 2, Project 1 
	// Also, I don't think this works anymore anyways and need to re do it lol
	// Face camera towards origin
	/*if (::cameraEye.x > 0 && ::cameraEye.z > 0)
	{
		::cameraYaw = 180.f + (atan(::cameraEye.z / ::cameraEye.x) * 180.f / glm::pi<float>());
	}
	else if (::cameraEye.x > 0 && ::cameraEye.z < 0)
	{
		::cameraYaw = 90.f - (atan(::cameraEye.z / ::cameraEye.x) * 180.f / glm::pi<float>());
	}
	else if (::cameraEye.x < 0 && ::cameraEye.z > 0)
	{
		::cameraYaw = (atan(::cameraEye.z / ::cameraEye.x) * 180.f / glm::pi<float>());
	}
	else if (::cameraEye.x < 0 && ::cameraEye.z < 0)
	{
		::cameraYaw = (atan(::cameraEye.z / ::cameraEye.x) * 180.f / glm::pi<float>());
	}
	else if (::cameraEye.x == 0.f)
	{
		if (::cameraEye.z >= 0.f)
		{
			::cameraYaw = 270.f;
		}
		else
		{
			::cameraYaw = 90.f;
		}
	}
	else if (::cameraEye.z == 0.f)
	{
		if (::cameraEye.x <= 0)
		{
			::cameraYaw = 0.f;
		}
		else
		{
			::cameraYaw = 180.f;
		}
	}*/
	//anyways, after figuring out the yaw, we set the target at the negative of the xz of the ::camera position and y=0 (this faces the ::camera towards the origin)
	//::cameraTarget = glm::vec3(-1.f * ::cameraEye.x, 0, -1.f * ::cameraEye.z);
	//glm::normalize(::cameraTarget);

	const double MAX_DELTA_TIME = 0.1;	//100 ms
	double previousTime = glfwGetTime();

	// I know in graphics 2 we started moving some of the start stuff out of the while loop so I'm just putting these here now
	float ratio;
	int width, height;

	while (!glfwWindowShouldClose(pWindow))
	{
		// not moving these out cause I want to ensure they're reset and not using last frame's information
		glm::mat4 matModel;				// used to be "m"; Sometimes it's called "world"
		glm::mat4 matProjection;        // used to be "p";
		glm::mat4 matView;              // used to be "v";

		double currentTime = glfwGetTime();
		deltaTime = currentTime - previousTime;
		deltaTime = (deltaTime > MAX_DELTA_TIME ? MAX_DELTA_TIME : deltaTime);
		previousTime = currentTime;

		glfwGetFramebufferSize(pWindow, &width, &height);
		ratio = width / (float)height;


		// ***************************************************
		// Physics
		::g_world->TimeStep((float)deltaTime);
		// Yeah, we never implemented the entity update in the world, so I needed to call update on each entity individually
		// honestly, looking at it, don't know why I didn't just have the world go through and call update on each entity
		//hangingChainEntity->Update();
		//boxEntity->Update();
		//spinningBladeEntity->Update();
		//targetEntity->Update();
		//springEntity->Update();

		// Update the rbWorld
		::g_rbPhysicsWorld->TimeStep((float)deltaTime);
		for (unsigned int index = 0; index != ::g_vec_pEntities.size(); index++)
		{
			// then run the Update on each entity, entities' mesh are pushed onto ::g_vec_pMeshes at creation
			::g_vec_pEntities[index]->Update();		// This basically just updates the mesh position
		}

		// ***************************************************


		//Turn on the depth buffer
		glEnable(GL_DEPTH);         // Turns on the depth buffer
		glEnable(GL_DEPTH_TEST);    // Check if the pixel is already closer

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// *******************************************************
		// Screen is cleared and we are ready to draw the scene...
		// *******************************************************

		// Update the title text
		glfwSetWindowTitle(pWindow, ::g_TitleText.c_str());



		// Copy the light information into the shader to draw the scene
		::g_pTheLights->CopyLightInfoToShader();

		/*matProjection = glm::perspective(0.6f,
			ratio,
			0.1f,
			1000.0f);*/

		matProjection = glm::perspective(0.6f,	// FOV variable later
			ratio,
			0.1f,								// Near plane
			1'000'000.0f);						// Far plane



		matView = glm::mat4(1.0f);
		//matView = glm::lookAt(	cameraEye,   // "eye"
		//						cameraAt,    // "at"
		//						cameraUp);

		// This isn't going to change super much, need to figure out how to change the camera controls for this project
		// Ok, so cameraTarget needs to change to be the direction from the camera to the currently selected sphere

		// took out to keep target at origin for now
		//::cameraTarget = ((rbSphereEntity*)::g_vec_pEntities[::g_SelectedEntityIndex])->m_Mesh->positionXYZ;
		// The mesh and rigid body positions should be equivalent
		//((rbSphereEntity*)::g_vec_pEntities[::g_SelectedEntityIndex])->m_RB->ptr->GetPosition();

		// This follows the sphere but doesn't move the camera, so the angle changes depending on where the ball is
		::cameraForward = ::cameraTarget - ::cameraEye;
		::cameraForward = glm::normalize(::cameraForward);
		matView = glm::lookAt(	::cameraEye,
								::cameraEye + ::cameraForward,
								::upVector);


		// For the fly camera I use
		//matView = glm::lookAt(::cameraEye,
		//	::cameraEye + ::cameraTarget,
		//	upVector);

		//	glUniformMatrix4fv(matView_Location, 1, GL_FALSE, glm::value_ptr(matView));

		glUniformMatrix4fv(pShaderProc->getUniformID_From_Name("matView"),
			1, GL_FALSE, glm::value_ptr(matView));


		glUniformMatrix4fv(matProjection_Location, 1, GL_FALSE, glm::value_ptr(matProjection));


		// Since this is a space game (most of the screen is filled with "sky"),
		// I'll draw the skybox first

		GLint bIsSkyBox_LocID = glGetUniformLocation(program, "bIsSkyBox");
		glUniform1f(bIsSkyBox_LocID, (GLfloat)GL_TRUE);

		// Move the "skybox object" with the camera
		sphereSky->positionXYZ = ::cameraEye;
		DrawObject(sphereSky, glm::mat4(1.0f),
			matModel_Location, matModelInverseTranspose_Location,
			program, ::g_pVAOManager);

		glUniform1f(bIsSkyBox_LocID, (GLfloat)GL_FALSE);

		// If there were transparent objects, this is where I would sort them

		// **********************************************************************
		// Draw the "scene" of all objects.
		// i.e. go through the vector and draw each one...
		// **********************************************************************
		for (unsigned int index = 0; index != ::g_vec_pMeshes.size(); index++)
		{
			// So the code is a little easier...
			cMesh* pCurrentMesh = ::g_vec_pMeshes[index];

			matModel = glm::mat4(1.0f);  // "Identity" ("do nothing", like x1)
			//mat4x4_identity(m);

			if (pCurrentMesh->bHasDiscardTexture)
			{
				// Discard texture
				{
					//GLuint discardTextureNumber = ::g_pTextureManager->getTextureIDFromName("Lisse_mobile_shipyard-mal1.bmp");
					GLuint discardTextureNumber = ::g_pTextureManager->getTextureIDFromName(pCurrentMesh->discardTexture);

					// I'm picking texture unit 30 since it's not in use.
					GLuint textureUnit = 30;
					glActiveTexture(textureUnit + GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, discardTextureNumber);
					GLint discardTexture_LocID = glGetUniformLocation(program, "discardTexture");
					glUniform1i(discardTexture_LocID, textureUnit);


					// Turn it on
					glUniform1f(bDiscardTransparencyWindowsON_LocID, (GLfloat)GL_TRUE);
					DrawObject(pCurrentMesh,
						matModel,
						matModel_Location,
						matModelInverseTranspose_Location,
						program,
						::g_pVAOManager);

					// Turn it off
					glUniform1f(pShaderProc->mapUniformName_to_UniformLocation["bDiscardTransparencyWindowsOn"], (GLfloat)GL_FALSE);
				}
			}
			else
			{
				DrawObject(pCurrentMesh,
					matModel,
					matModel_Location,
					matModelInverseTranspose_Location,
					program,
					::g_pVAOManager);
			}


		}//for (unsigned int index


		// Scene is drawn
		// **********************************************************************

		// "Present" what we've drawn.
		glfwSwapBuffers(pWindow);        // Show what we've drawn

		// Process any events that have happened
		glfwPollEvents();

		// Handle OUR keyboard, mouse stuff
		handleAsyncKeyboard(pWindow, deltaTime);
		handleAsyncMouse(pWindow, deltaTime);
	} //while (!glfwWindowShouldClose(window))

	// All done, so delete things...
	::g_ShutDown(pWindow);


	glfwDestroyWindow(pWindow);

	glfwTerminate();
	exit(EXIT_SUCCESS);

} //end of main

// Modified from previous versions to take texture information
bool loadWorldFile()
{
	std::stringstream ss;
	std::stringstream sFile;


	ss << SOLUTION_DIR << "common\\assets\\worldFile.txt";

	std::ifstream theFile(ss.str());

	if (!theFile.is_open())
	{
		fprintf(stderr, "Could not open worldFile.txt");
		return false;
	}

	std::string nextToken;
	ss.str("");

	//Throwaway text describing the format of the file
	theFile >> nextToken;       //ModelFileName(extension)
	theFile >> nextToken;       //Position(x,y,z)
	theFile >> nextToken;       //Orientation(x,y,z)
	theFile >> nextToken;       //Scale(x,y,z)
	theFile >> nextToken;       //Colour(r,g,b,a)
	theFile >> nextToken;		//Light
	theFile >> nextToken;		//TextureOp
	theFile >> nextToken;		//TextureName1
	theFile >> nextToken;		//Ratio1
	theFile >> nextToken;		//TextureName2
	theFile >> nextToken;		//Ratio2
	theFile >> nextToken;		//TextureName3
	theFile >> nextToken;		//Ratio3
	theFile >> nextToken;		//DiscardTexture

	theFile >> nextToken;		//Camera(x,y,z)
	theFile >> nextToken;		//x position
	::cameraEye.x = std::stof(nextToken);
	theFile >> nextToken;		//y position
	::cameraEye.y = std::stof(nextToken);
	theFile >> nextToken;		//z position
	::cameraEye.z = std::stof(nextToken);

	theFile >> nextToken;		//number of transparent objects
	numberOfTransparentObjects = std::stoi(nextToken);

	//From here modify based on worldFile format
	while (theFile >> nextToken)    //this should always be the name of the model to load or end.  Potential error check, add a check for "ply" in the mdoel name
	{
		cMesh* curMesh = new cMesh;
		if (nextToken == "end")
		{
			break;
		}
		std::cout << nextToken << std::endl;        //Printing model names to console, just making sure we're loading ok.  Can be commented out whenever
		//First is the file name of model
		//ss << SOLUTION_DIR << "common\\assets\\models\\" << nextToken;		// don't need this with the setBasePath function for the loading intot the VAO
		curMesh->meshName = nextToken;
		//Next 3 are the position of the model
		theFile >> nextToken;                                               //x position for the model
		curMesh->positionXYZ.x = std::stof(nextToken);
		theFile >> nextToken;                                               //y position for the model
		curMesh->positionXYZ.y = std::stof(nextToken);
		theFile >> nextToken;                                               //z position for the model
		curMesh->positionXYZ.z = std::stof(nextToken);
		//Next 3 are the orientation of the model
		theFile >> nextToken;                                               //x orientation value
		//curMesh.orientationXYZ.x = std::stof(nextToken);
		curMesh->orientationXYZ.x = glm::radians(std::stof(nextToken));
		theFile >> nextToken;                                               //y orientation value
		//curMesh.orientationXYZ.y = std::stof(nextToken);
		curMesh->orientationXYZ.y = glm::radians(std::stof(nextToken));
		theFile >> nextToken;                                               //z orientation value
		//curMesh.orientationXYZ.z = std::stof(nextToken);
		curMesh->orientationXYZ.z = glm::radians(std::stof(nextToken));
		// TODO: Update this to 3 values
		//Next is the scale to multiply the model by
		theFile >> nextToken;
		curMesh->scale.x = std::stof(nextToken);
		theFile >> nextToken;
		curMesh->scale.y = std::stof(nextToken);
		theFile >> nextToken;
		curMesh->scale.z = std::stof(nextToken);
		//Next 3 are the r, g, b values for the model
		curMesh->bUseWholeObjectDiffuseColour = false;
		theFile >> nextToken;													//RGB red value
		curMesh->wholeObjectDiffuseRGBA.r = std::stof(nextToken) / 255.0f;		//convert to nice shader value (between 0 and 1)
		theFile >> nextToken;													//RGB green value
		curMesh->wholeObjectDiffuseRGBA.g = std::stof(nextToken) / 255.0f;		//convert to nice shader value (between 0 and 1)
		theFile >> nextToken;													//RGB blue value
		curMesh->wholeObjectDiffuseRGBA.b = std::stof(nextToken) / 255.0f;		//convert to nice shader value (between 0 and 1)
		theFile >> nextToken;
		curMesh->wholeObjectDiffuseRGBA.a = std::stof(nextToken);
		curMesh->alphaTransparency = std::stof(nextToken);

		// Light
		theFile >> nextToken;
		curMesh->bDontLight = (nextToken == "0");		// set to true or "0" in the worldFile to see textures without lighting

		// Texture operator
		theFile >> nextToken;
		curMesh->textureOperator = std::stoi(nextToken);

		// texture for mesh is in worldFile.txt now
		curMesh->clearTextureRatiosToZero();

		theFile >> nextToken;
		if (nextToken != "null")
		{
			curMesh->textureNames[1] = nextToken;
			theFile >> nextToken;
			curMesh->textureRatios[1] = std::stof(nextToken);
		}
		else
		{
			theFile >> nextToken;	// throw away the ratio number
		}

		theFile >> nextToken;
		if (nextToken != "null")
		{
			curMesh->textureNames[2] = nextToken;
			theFile >> nextToken;
			curMesh->textureRatios[2] = std::stof(nextToken);
		}
		else
		{
			theFile >> nextToken;	// throw away the ratio number
		}

		theFile >> nextToken;
		if (nextToken != "null")
		{
			curMesh->textureNames[3] = nextToken;
			theFile >> nextToken;
			curMesh->textureRatios[3] = std::stof(nextToken);
		}
		else
		{
			theFile >> nextToken;	// throw away the ratio number
		}

		if (curMesh->textureRatios[1] == 0.0f && curMesh->textureRatios[2] == 0.0f && curMesh->textureRatios[3] == 0.0f)
		{
			curMesh->textureRatios[0] = 1.0f;
		}

		// Discard texture
		theFile >> nextToken;
		if (nextToken != "null")
		{
			curMesh->discardTexture = nextToken;
			curMesh->bHasDiscardTexture = true;
		}

		::g_vec_pMeshes.push_back(curMesh);     //push the model onto our vector of meshes
		ss.str("");                         //reset the stringstream
	} //end of while
	theFile.close();
	return true;
}	//end of load world file

bool loadLightsFile()
{
	std::stringstream ss;
	std::stringstream sFile;


	ss << SOLUTION_DIR << "common\\assets\\lights.txt";

	std::ifstream theFile(ss.str());

	if (!theFile.is_open())
	{
		fprintf(stderr, "Could not open lights.txr");
		return false;
	}

	std::string nextToken;
	ss.str("");

	// Throw away description 
	theFile >> nextToken;		// position(x,y,z)
	theFile >> nextToken;		// diffuse(r,g,b)
	theFile >> nextToken;		// specular(r,g,b)
	theFile >> nextToken;		// atten(x,y,z)
	theFile >> nextToken;		// direction(x,y,z)
	theFile >> nextToken;		// param1(x,y,z)
	theFile >> nextToken;		// param2(x)

	::g_pTheLights->TurnOffLight(0);

	// Let's try 0 again
	unsigned int index = 0;	// can't start at 0 because for some reason the 0 light over writes all other lights

	while (theFile >> nextToken)
	{
		if (nextToken == "end" || index >= cLightManager::NUMBER_OF_LIGHTS)
		{
			break;
		}
		glm::vec3 position;
		glm::vec3 diffuse;
		glm::vec3 specular;
		glm::vec3 atten;
		glm::vec3 direction;
		glm::vec3 param1;
		float param2;

		// Position
		position.x = std::stof(nextToken);
		theFile >> nextToken;
		position.y = std::stof(nextToken);
		theFile >> nextToken;
		position.z = std::stof(nextToken);

		// Diffuse
		theFile >> nextToken;
		diffuse.x = std::stof(nextToken);
		theFile >> nextToken;
		diffuse.y = std::stof(nextToken);
		theFile >> nextToken;
		diffuse.z = std::stof(nextToken);

		// Specular
		theFile >> nextToken;
		specular.x = std::stof(nextToken);
		theFile >> nextToken;
		specular.y = std::stof(nextToken);
		theFile >> nextToken;
		specular.z = std::stof(nextToken);

		// Atten
		theFile >> nextToken;
		atten.x = std::stof(nextToken);
		theFile >> nextToken;
		atten.y = std::stof(nextToken);
		theFile >> nextToken;
		atten.z = std::stof(nextToken);

		// Direction
		theFile >> nextToken;
		direction.x = std::stof(nextToken);
		theFile >> nextToken;
		direction.y = std::stof(nextToken);
		theFile >> nextToken;
		direction.z = std::stof(nextToken);

		// Param1
		theFile >> nextToken;
		param1.x = std::stof(nextToken);;
		theFile >> nextToken;
		param1.y = std::stof(nextToken);
		theFile >> nextToken;
		param1.z = std::stof(nextToken);

		// Param2
		theFile >> nextToken;
		param2 = std::stof(nextToken);


		// Load everything into the lights
		::g_pTheLights->theLights[index].position = glm::vec4(position, 1.0f);
		::g_pTheLights->theLights[index].diffuse = glm::vec4(diffuse, 1.0f);
		::g_pTheLights->theLights[index].specular = glm::vec4(specular, 1.0f);
		::g_pTheLights->theLights[index].atten = glm::vec4(atten, 1.0f);
		::g_pTheLights->theLights[index].direction = glm::vec4(direction, 1.0f);
		::g_pTheLights->theLights[index].param1 = glm::vec4(param1, 1.0f);
		::g_pTheLights->theLights[index].param2 = glm::vec4(param2, 0.0f, 0.0f, 1.0f);

		index++;

	} //end of while

	theFile.close();
	return true;

} //end of load lights

// Not used for this project, can probably comment out
//Figured out the math for how to do this from https://learnopengl.com/Getting-started/Camera and http://www.opengl-tutorial.org/beginners-tutorials/tutorial-6-keyboard-and-mouse/
//Using the mouse position we calculate the direction that the camera will be facing
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	//if it's the start of the program this smooths out a potentially glitchy jump
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	//find the offset of where the mouse positions have moved
	float xOffset = xpos - lastX;
	float yOffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	//multiply by sensitivity so that it's not potentially crazy fast
	float sensitivity = 0.1f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	::cameraYaw += xOffset;         // The yaw is the rotation around the ::camera's y-axis (so we want to add the xOffset to it)
	::cameraPitch += yOffset;       // The pitch is the rotation around the ::camera's x-axis (so we want to add the yOffset to it)
	//This limits the pitch so that we can't just spin the ::camera under/over itself
	if (::cameraPitch > 89.0f)
		::cameraPitch = 89.0f;
	if (::cameraPitch < -89.0f)
		::cameraPitch = -89.0f;
	//calculations for the new direction based on the mouse movements
	glm::vec3 direction;
	direction.x = cos(glm::radians(::cameraYaw)) * cos(glm::radians(::cameraPitch));
	direction.y = sin(glm::radians(::cameraPitch));
	direction.z = sin(glm::radians(::cameraYaw)) * cos(glm::radians(::cameraPitch));
	::cameraTarget = glm::normalize(direction);
} //fly ::camera