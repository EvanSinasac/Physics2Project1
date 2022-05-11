//Evan Sinasac - 1081418
//INFO6019 Physics and Simulation and INFO6025 Configuration and Deployment Midterm
//cConfigReader.h description:
//						Reads config.json file and stores information in private structures

#pragma once
#include <string>
#include <rapidjson/filereadstream.h>
#include <rapidjson/document.h>
#include <vector>
#include "GLMCommon.h"
#include <string>

struct CannonInfo
{
	float yawMin;
	float yawMax;
	float pitchMax;
	float pitchMin;
	glm::vec3 position;
};

struct BulletInfo
{
	float size;
	float damping;
	float mass;
	float velocityMag;
	float lifeSpan;
};

struct LaserInfo
{
	float size;
	float damping;
	float mass;
	float velocityMag;
	float lifeSpan;
};

struct HangingChainInfo
{
	int numOfJoints;
	int numOfConstraints;
	float jointRadius;
	float jointRestitution;
	float distBetweenJoints;
	glm::vec3 startPosition;
	float targetRadius;
};

struct BoxEntityInfo
{
	float jointRadius;
	float distBetweenJoints;
	float jointRestitution;
	glm::vec3 startPosition;
};

struct SpinningBladeInfo
{
	float jointRadius;
	float distFromStart;
	float restitution;
	glm::vec3 startPosition;
	std::string lockedAxis;
};

struct TargetInfo
{
	float restitution;
	float radius;
	glm::vec3 startPosition;
};

struct SpringInfo
{
	glm::vec3 startPosition;
	glm::vec3 anchorPosition;
	float radius;
	float springConstant;
	float restLength;
	float restitution;
};


class cConfigReaderJSON
{
private:
	CannonInfo cannonInfo;
	BulletInfo bulletInfo;
	LaserInfo laserInfo;
	HangingChainInfo hangingChainInfo;
	BoxEntityInfo boxEntityInfo;
	SpinningBladeInfo spinningBladeInfo;
	TargetInfo targetInfo;
	SpringInfo springInfo;
	int numOfMeshes;

public:
	cConfigReaderJSON();
	~cConfigReaderJSON();

	bool readConfigFile(const std::string& filePath);
	
	//Cannon Info
	float GetCannonYawMax(); //{ return cannonInfo.yawMax; }
	float GetCannonYawMin(); //{ return cannonInfo.yawMin; }
	float GetCannonPitchMax(); //{ return cannonInfo.pitchMax; }
	float GetCannonPitchMin(); //{ return cannonInfo.pitchMin; }
	glm::vec3 GetCannonPosition(); //{ return cannonInfo.position; }

	//Bullet Info
	float GetBulletSize(); //{ return bulletInfo.size; }
	float GetBulletDamping(); //{ return bulletInfo.damping; }
	float GetBulletMass(); //{ return bulletInfo.mass; }
	float GetBulletVelocity(); //{ return bulletInfo.velocityMag; }
	float GetBulletLifeSpan(); //{ return bulletInfo.lifeSpan; }

	//Laser Info
	float GetLaserSize(); //{ return laserInfo.size; }
	float GetLaserDamping(); //{ return laserInfo.damping; }
	float GetLaserMass(); //{ return laserInfo.mass; }
	float GetLaserVelocity(); //{ return laserInfo.velocityMag; }
	float GetLaserLifeSpan(); //{ return laserInfo.lifeSpan; }

	// Hanging Chain Entity
	int GetHCNumOfJoints(); //{ return hangingChainInfo.numOfJoints; }
	int GetHCNumOfConstraints(); //{ return hangingChainInfo.numOfConstraints; }
	float GetHCJointRadius(); //{ return hangingChainInfo.jointRadius; }
	float GetHCJointRestitution();
	float GetHCDistBetweenJoints(); //{ return hangingChainInfo.distBetweenJoints; }
	glm::vec3 GetHCStartPos();// { return hangingChainInfo.startPosition; }
	float GetHCTargetRadius();

	// Box Entity
	float GetBEJointRadius();
	float GetBEDistBetweenJoints();
	float GetBEJointRestitution();
	glm::vec3 GetBEStartPos();

	// Spinning Blade Info
	float GetSBJointRadius();
	float GetSBDistFromStart();
	float GetSBRestitution();
	glm::vec3 GetSBStartPos();
	std::string GetSBLockedAxis();

	// Target
	float GetTargetRestitution();
	float GetTargetRadius();
	glm::vec3 GetTargetStartPos();

	// Spring
	glm::vec3 GetSpringStartPos();
	glm::vec3 GetSpringAnchorPos();
	float GetSpringRadius();
	float GetSpringConstant();
	float GetSpringRestLength();
	float GetSpringRestitution();

	int GetNumOfMeshes();
};
