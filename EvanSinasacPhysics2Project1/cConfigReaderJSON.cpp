//Evan Sinasac - 1081418
//INFO6019 Physics and Simulation and INFO6025 Configuration and Deployment Midterm
//cConfigReader.cpp description:
//						Reads config.json file and stores information in private structures


#include "cConfigReaderJSON.h"
#include <iostream>
#include <sstream>

cConfigReaderJSON::cConfigReaderJSON()
{
	//Should probably put default safety values here... yeah
}
cConfigReaderJSON::~cConfigReaderJSON()
{

}
//read the config file
bool cConfigReaderJSON::readConfigFile(const std::string& filePath)
{
	using namespace rapidjson;

	FILE* fp = 0;
	fopen_s(&fp, filePath.c_str(), "rb");

	if (!fp)
	{
		std::cout << "fp didn't open" << std::endl;
		return false;
	}

	//char readBuffer[65536];
	char* readBuffer = new char[15000];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));

	Document d;
	d.ParseStream(is);

	if (!d["Cannon"].IsObject())
	{
		std::cout << "Cannon object didn't exist" << std::endl;
		fclose(fp);
		return false;
	}
	else
	{
		if (!d["Cannon"]["YawMax"].IsFloat())
		{
			std::cout << "YawMax wasn't a float!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			cannonInfo.yawMax = d["Cannon"]["YawMax"].GetFloat();
		}

		if (!d["Cannon"]["YawMin"].IsFloat())
		{
			std::cout << "YawMin wasn't a float!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			cannonInfo.yawMin = d["Cannon"]["YawMin"].GetFloat();
		}

		if (!d["Cannon"]["PitchMax"].IsFloat())
		{
			std::cout << "PitchMax wasn't a float!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			cannonInfo.pitchMax = d["Cannon"]["PitchMax"].GetFloat();
		}

		if (!d["Cannon"]["PitchMin"].IsFloat())
		{
			std::cout << "PitchMin wasn't a float!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			cannonInfo.pitchMin = d["Cannon"]["PitchMin"].GetFloat();
		}

		if (!d["Cannon"]["XPosition"].IsFloat())
		{
			std::cout << "XPosition wasn't a float!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			cannonInfo.position.x = d["Cannon"]["XPosition"].GetFloat();
		}

		if (!d["Cannon"]["YPosition"].IsFloat())
		{
			std::cout << "YPosition wasn't a float!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			cannonInfo.position.y = d["Cannon"]["YPosition"].GetFloat();
		}

		if (!d["Cannon"]["ZPosition"].IsFloat())
		{
			std::cout << "ZPosition wasn't a float!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			cannonInfo.position.z = d["Cannon"]["ZPosition"].GetFloat();
		}
	}

	if (!d["Bullet"].IsObject())
	{
		std::cout << "Bullet isn't an object!" << std::endl;
		fclose(fp);
		return false;
	}
	else
	{
		if (!d["Bullet"]["Size"].IsFloat())
		{
			std::cout << "Bullet Size isn't a float!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			bulletInfo.size = d["Bullet"]["Size"].GetFloat();
		}

		if (!d["Bullet"]["Damping"].IsFloat())
		{
			std::cout << "Bullet Damping isn't a float!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			bulletInfo.damping = d["Bullet"]["Damping"].GetFloat();
		}

		if (!d["Bullet"]["Mass"].IsFloat())
		{
			std::cout << "Bullet Mass isn't a float!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			bulletInfo.mass = d["Bullet"]["Mass"].GetFloat();
		}

		if (!d["Bullet"]["MuzzleVelocity"].IsFloat())
		{
			std::cout << "Bullet MuzzleVelocity isn't a float!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			bulletInfo.velocityMag = d["Bullet"]["MuzzleVelocity"].GetFloat();
		}

		if (!d["Bullet"]["LifeSpan"].IsFloat())
		{
			std::cout << "Bullet LifeSpan isn't a float!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			bulletInfo.lifeSpan = d["Bullet"]["LifeSpan"].GetFloat();
		}

	}

	if (!d["Laser"].IsObject())
	{
		std::cout << "Laser isn't an object!" << std::endl;
		fclose(fp);
		return false;
	}
	else
	{
		if (!d["Laser"]["Size"].IsFloat())
		{
			std::cout << "Laser Size isn't a float!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			laserInfo.size = d["Laser"]["Size"].GetFloat();
		}

		if (!d["Laser"]["Damping"].IsFloat())
		{
			std::cout << "Laser Damping isn't a float!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			laserInfo.damping = d["Laser"]["Damping"].GetFloat();
		}

		if (!d["Laser"]["Mass"].IsFloat())
		{
			std::cout << "Laser Mass isn't a float!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			laserInfo.mass = d["Laser"]["Mass"].GetFloat();
		}

		if (!d["Laser"]["MuzzleVelocity"].IsFloat())
		{
			std::cout << "Laser MuzzleVelocity isn't a float!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			laserInfo.velocityMag = d["Laser"]["MuzzleVelocity"].GetFloat();
		}

		if (!d["Laser"]["LifeSpan"].IsFloat())
		{
			std::cout << "Laser LifeSpan isn't a float!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			laserInfo.lifeSpan = d["Laser"]["LifeSpan"].GetFloat();
		}
	}

	if (!d["Target"].IsObject())
	{
		std::cout << "Target isn't an object!" << std::endl;
		fclose(fp);
		return false;
	}
	else
	{
		if (!d["Target"]["Restitution"].IsFloat())
		{
			std::cout << "Target Restitution isn't a float!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			targetInfo.restitution = d["Target"]["Restitution"].GetFloat();
		}

		if (!d["Target"]["Radius"].IsFloat())
		{
			std::cout << "Target Radius isn't a float!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			targetInfo.radius = d["Target"]["Radius"].GetFloat();
		}

		if (!d["Target"]["StartPos"].IsObject())
		{
			std::cout << "Target StartPos isn't an object!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			if (!d["Target"]["StartPos"]["X"].IsFloat())
			{
				std::cout << "Target StartPos X isn't a float!" << std::endl;
				fclose(fp);
				return false;
			}
			else
			{
				targetInfo.startPosition.x = d["Target"]["StartPos"]["X"].GetFloat();
			}

			if (!d["Target"]["StartPos"]["Y"].IsFloat())
			{
				std::cout << "Target StartPos Y isn't a float!" << std::endl;
				fclose(fp);
				return false;
			}
			else
			{
				targetInfo.startPosition.y = d["Target"]["StartPos"]["Y"].GetFloat();
			}

			if (!d["Target"]["StartPos"]["Z"].IsFloat())
			{
				std::cout << "Target StartPos Z isn't a float!" << std::endl;
				fclose(fp);
				return false;
			}
			else
			{
				targetInfo.startPosition.z = d["Target"]["StartPos"]["Z"].GetFloat();
			}
		}
	}

	if (!d["HangingChainEntity"].IsObject())
	{
		std::cout << "HangingChainEntity isn't an object!" << std::endl;
		fclose(fp);
		return false;
	}
	else
	{
		if (!d["HangingChainEntity"]["NumOfJoints"].IsInt())
		{
			std::cout << "Hanging Chain NumOfJoints isn't an int!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			hangingChainInfo.numOfJoints = d["HangingChainEntity"]["NumOfJoints"].GetInt();
		}

		if (!d["HangingChainEntity"]["NumOfConstraints"].IsInt())
		{
			std::cout << "Hanging Chain NumOfConstraints isn't an int!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			hangingChainInfo.numOfConstraints = d["HangingChainEntity"]["NumOfConstraints"].GetInt();
		}

		if (!d["HangingChainEntity"]["JointRadius"].IsFloat())
		{
			std::cout << "Hanging Chain JointRadius isn't a float!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			hangingChainInfo.jointRadius = d["HangingChainEntity"]["JointRadius"].GetFloat();
		}

		if (!d["HangingChainEntity"]["JointRestitution"].IsFloat())
		{
			std::cout << "HangingChain JointRestitution isn't a float!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			hangingChainInfo.jointRestitution = d["HangingChainEntity"]["JointRestitution"].GetFloat();
		}

		if (!d["HangingChainEntity"]["DistBetweenJoints"].IsFloat())
		{
			std::cout << "Hanging Chain DistBetweenJoints isn't a float!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			hangingChainInfo.distBetweenJoints = d["HangingChainEntity"]["DistBetweenJoints"].GetFloat();
		}

		if (!d["HangingChainEntity"]["StartPos"].IsObject())
		{
			std::cout << "Hanging Chain StartPos isn't an object!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			if (!d["HangingChainEntity"]["StartPos"]["X"].IsFloat())
			{
				std::cout << "Hanging Chaing StartPos X isn't a float!" << std::endl;
				fclose(fp);
				return false;
			}
			else
			{
				hangingChainInfo.startPosition.x = d["HangingChainEntity"]["StartPos"]["X"].GetFloat();
			}

			if (!d["HangingChainEntity"]["StartPos"]["Y"].IsFloat())
			{
				std::cout << "Hanging Chaing StartPos Y isn't a float!" << std::endl;
				fclose(fp);
				return false;
			}
			else
			{
				hangingChainInfo.startPosition.y = d["HangingChainEntity"]["StartPos"]["Y"].GetFloat();
			}

			if (!d["HangingChainEntity"]["StartPos"]["Z"].IsFloat())
			{
				std::cout << "Hanging Chaing StartPos Z isn't a float!" << std::endl;
				fclose(fp);
				return false;
			}
			else
			{
				hangingChainInfo.startPosition.z = d["HangingChainEntity"]["StartPos"]["Z"].GetFloat();
			}
		}

		if (!d["HangingChainEntity"]["TargetRadius"].IsFloat())
		{
			std::cout << "Hanging Chain TargetRadius isn't a float!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			hangingChainInfo.targetRadius = d["HangingChainEntity"]["TargetRadius"].GetFloat();
		}
	}

	if (!d["BoxEntity"].IsObject())
	{
		std::cout << "BoxEntity isn't an object!" << std::endl;
		return false;
	}
	else
	{
		if (!d["BoxEntity"]["JointRadius"].IsFloat())
		{
			std::cout << "BoxEntity JointRadius isn't a float" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			boxEntityInfo.jointRadius = d["BoxEntity"]["JointRadius"].GetFloat();
		}

		if (!d["BoxEntity"]["DistBetweenJoints"].IsFloat())
		{
			std::cout << "BoxEntity DistBetweenJoints isn't a float!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			boxEntityInfo.distBetweenJoints = d["BoxEntity"]["DistBetweenJoints"].GetFloat();
		}

		if (!d["BoxEntity"]["JointRestitution"].IsFloat())
		{
			std::cout << "BoxEntity JointRestitution isn't a float!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			boxEntityInfo.jointRestitution = d["BoxEntity"]["JointRestitution"].GetFloat();
		}

		if (!d["BoxEntity"]["StartPos"].IsObject())
		{
			std::cout << "BoxEntity StartPos isn't an object!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			if (!d["BoxEntity"]["StartPos"]["X"].IsFloat())
			{
				std::cout << "BoxEntity StartPos X isn't a float!" << std::endl;
				fclose(fp);
				return false;
			}
			else
			{
				boxEntityInfo.startPosition.x = d["BoxEntity"]["StartPos"]["X"].GetFloat();
			}

			if (!d["BoxEntity"]["StartPos"]["Y"].IsFloat())
			{
				std::cout << "BoxEntity StartPos Y isn't a float!" << std::endl;
				fclose(fp);
				return false;
			}
			else
			{
				boxEntityInfo.startPosition.y = d["BoxEntity"]["StartPos"]["Y"].GetFloat();
			}

			if (!d["BoxEntity"]["StartPos"]["Z"].IsFloat())
			{
				std::cout << "BoxEntity StartPos Z isn't a float!" << std::endl;
				fclose(fp);
				return false;
			}
			else
			{
				boxEntityInfo.startPosition.z = d["BoxEntity"]["StartPos"]["Z"].GetFloat();
			}
		}
	}

	if (!d["SpinningBlade"].IsObject())
	{
		std::cout << "SpinningBlade is not an object!" << std::endl;
		fclose(fp);
		return false;
	}
	else
	{
		if (!d["SpinningBlade"]["JointRadius"].IsFloat())
		{
			std::cout << "SpinningBlade JointRadius isn't a float!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			spinningBladeInfo.jointRadius = d["SpinningBlade"]["JointRadius"].GetFloat();
		}

		if (!d["SpinningBlade"]["DistFromStart"].IsFloat())
		{
			std::cout << "SpinningBlade DistFromStart isn't a float!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			spinningBladeInfo.distFromStart = d["SpinningBlade"]["DistFromStart"].GetFloat();
		}

		if (!d["SpinningBlade"]["Restitution"].IsFloat())
		{
			std::cout << "SpinningBlade Restitution isn't a float!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			spinningBladeInfo.restitution = d["SpinningBlade"]["Restitution"].GetFloat();
		}

		if (!d["SpinningBlade"]["LockedAxis"].IsString())
		{
			std::cout << "SpinningBlade LockedAxis isn't a string!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			spinningBladeInfo.lockedAxis = d["SpinningBlade"]["LockedAxis"].GetString();
		}

		if (!d["SpinningBlade"]["StartPos"].IsObject())
		{
			std::cout << "SpinningBlade StartPos isn't an object!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			if (!d["SpinningBlade"]["StartPos"]["X"].IsFloat())
			{
				std::cout << "SpinningBlade StartPos X isn't a float!" << std::endl;
				fclose(fp);
				return false;
			}
			else
			{
				spinningBladeInfo.startPosition.x = d["SpinningBlade"]["StartPos"]["X"].GetFloat();
			}

			if (!d["SpinningBlade"]["StartPos"]["Y"].IsFloat())
			{
				std::cout << "SpinningBlade StartPos Y isn't a float!" << std::endl;
				fclose(fp);
				return false;
			}
			else
			{
				spinningBladeInfo.startPosition.y = d["SpinningBlade"]["StartPos"]["Y"].GetFloat();
			}

			if (!d["SpinningBlade"]["StartPos"]["Z"].IsFloat())
			{
				std::cout << "SpinningBlade StartPos Z isn't a float!" << std::endl;
				fclose(fp);
				return false;
			}
			else
			{
				spinningBladeInfo.startPosition.z = d["SpinningBlade"]["StartPos"]["Z"].GetFloat();
			}
		}
	}

	if (!d["SpringParticle"].IsObject())
	{
		std::cout << "SpringParticle isn't an object!" << std::endl;
		fclose(fp);
		return false;
	}
	else
	{
		if (!d["SpringParticle"]["StartPos"].IsObject())
		{
			std::cout << "SpringParticle StartPos isn't an object!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			if (!d["SpringParticle"]["StartPos"]["X"].IsFloat())
			{
				std::cout << "SpringParticle StartPos X isn't a float!" << std::endl;
				fclose(fp);
				return false;
			}
			else
			{
				springInfo.startPosition.x = d["SpringParticle"]["StartPos"]["X"].GetFloat();
			}

			if (!d["SpringParticle"]["StartPos"]["Y"].IsFloat())
			{
				std::cout << "SpringParticle StartPos Y isn't a float!" << std::endl;
				fclose(fp);
				return false;
			}
			else
			{
				springInfo.startPosition.y = d["SpringParticle"]["StartPos"]["Y"].GetFloat();
			}

			if (!d["SpringParticle"]["StartPos"]["Z"].IsFloat())
			{
				std::cout << "SpringParticle StartPos Z isn't a float!" << std::endl;
				fclose(fp);
				return false;
			}
			else
			{
				springInfo.startPosition.z = d["SpringParticle"]["StartPos"]["Z"].GetFloat();
			}
		}

		if (!d["SpringParticle"]["AnchorPos"].IsObject())
		{
			std::cout << "SpringParticle AnchorPos isn't an object!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			if (!d["SpringParticle"]["AnchorPos"]["X"].IsFloat())
			{
				std::cout << "SpringParticle AnchorPos X isn't a float!" << std::endl;
				fclose(fp);
				return false;
			}
			else
			{
				springInfo.anchorPosition.x = d["SpringParticle"]["AnchorPos"]["X"].GetFloat();
			}

			if (!d["SpringParticle"]["AnchorPos"]["Y"].IsFloat())
			{
				std::cout << "SpringParticle AnchorPos Y isn't a float!" << std::endl;
				fclose(fp);
				return false;
			}
			else
			{
				springInfo.anchorPosition.y = d["SpringParticle"]["AnchorPos"]["Y"].GetFloat();
			}

			if (!d["SpringParticle"]["AnchorPos"]["Z"].IsFloat())
			{
				std::cout << "SpringParticle AnchorPos Z isn't a float!" << std::endl;
				fclose(fp);
				return false;
			}
			else
			{
				springInfo.anchorPosition.z = d["SpringParticle"]["AnchorPos"]["Z"].GetFloat();
			}
		}

		if (!d["SpringParticle"]["Radius"].IsFloat())
		{
			std::cout << "SpringParticle Radius isn't a float!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			springInfo.radius = d["SpringParticle"]["Radius"].GetFloat();
		}

		if (!d["SpringParticle"]["SpringConstant"].IsFloat())
		{
			std::cout << "SpringParticle SpringConstant isn't a float!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			springInfo.springConstant = d["SpringParticle"]["SpringConstant"].GetFloat();
		}

		if (!d["SpringParticle"]["RestLength"].IsFloat())
		{
			std::cout << "SpringParticle RestLength isn't a float!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			springInfo.restLength = d["SpringParticle"]["RestLength"].GetFloat();
		}

		if (!d["SpringParticle"]["Restitution"].IsFloat())
		{
			std::cout << "SpringParticle Restitution isn't a float!" << std::endl;
			fclose(fp);
			return false;
		}
		else
		{
			springInfo.restitution = d["SpringParticle"]["Restitution"].GetFloat();
		}
	}

	if (!d["NumberOfMeshesWithoutHC"].IsInt())
	{
		std::cout << "NumberOfMeshesWithoutHC isn't an int!" << std::endl;
		fclose(fp);
		return false;
	}
	else
	{
		this->numOfMeshes = d["NumberOfMeshesWithoutHC"].GetInt();
	}

	fclose(fp);
	return true;
}

//Cannon Info
float cConfigReaderJSON::GetCannonYawMax() { return cannonInfo.yawMax; }
float cConfigReaderJSON::GetCannonYawMin() { return cannonInfo.yawMin; }
float cConfigReaderJSON::GetCannonPitchMax() { return cannonInfo.pitchMax; }
float cConfigReaderJSON::GetCannonPitchMin() { return cannonInfo.pitchMin; }
glm::vec3 cConfigReaderJSON::GetCannonPosition() { return cannonInfo.position; }

//Bullet Info
float cConfigReaderJSON::GetBulletSize() { return bulletInfo.size; }
float cConfigReaderJSON::GetBulletDamping() { return bulletInfo.damping; }
float cConfigReaderJSON::GetBulletMass() { return bulletInfo.mass; }
float cConfigReaderJSON::GetBulletVelocity() { return bulletInfo.velocityMag; }
float cConfigReaderJSON::GetBulletLifeSpan(){ return bulletInfo.lifeSpan; }

//Laser Info
float cConfigReaderJSON::GetLaserSize() { return laserInfo.size; }
float cConfigReaderJSON::GetLaserDamping() { return laserInfo.damping; }
float cConfigReaderJSON::GetLaserMass() { return laserInfo.mass; }
float cConfigReaderJSON::GetLaserVelocity() { return laserInfo.velocityMag; }
float cConfigReaderJSON::GetLaserLifeSpan() { return laserInfo.lifeSpan; }

// Hanging Chain Entity
int cConfigReaderJSON::GetHCNumOfJoints() { return hangingChainInfo.numOfJoints; }
int cConfigReaderJSON::GetHCNumOfConstraints() { return hangingChainInfo.numOfConstraints; }
float cConfigReaderJSON::GetHCJointRadius() { return hangingChainInfo.jointRadius; }
float cConfigReaderJSON::GetHCJointRestitution() { return hangingChainInfo.jointRestitution; }
float cConfigReaderJSON::GetHCDistBetweenJoints() { return hangingChainInfo.distBetweenJoints; }
glm::vec3 cConfigReaderJSON::GetHCStartPos() { return hangingChainInfo.startPosition; }
float cConfigReaderJSON::GetHCTargetRadius() { return hangingChainInfo.targetRadius; }

// Box Entity
float cConfigReaderJSON::GetBEJointRadius() { return boxEntityInfo.jointRadius; }
float cConfigReaderJSON::GetBEDistBetweenJoints() { return boxEntityInfo.distBetweenJoints; }
float cConfigReaderJSON::GetBEJointRestitution() { return boxEntityInfo.jointRestitution; }
glm::vec3 cConfigReaderJSON::GetBEStartPos() { return boxEntityInfo.startPosition; }

// Spinning Blade Info
float cConfigReaderJSON::GetSBJointRadius() { return spinningBladeInfo.jointRadius; }
float cConfigReaderJSON::GetSBDistFromStart() { return spinningBladeInfo.distFromStart; }
float cConfigReaderJSON::GetSBRestitution() { return spinningBladeInfo.restitution; }
glm::vec3 cConfigReaderJSON::GetSBStartPos() { return spinningBladeInfo.startPosition; }
std::string cConfigReaderJSON::GetSBLockedAxis() { return spinningBladeInfo.lockedAxis; }

// Target
float cConfigReaderJSON::GetTargetRestitution() { return targetInfo.restitution; }
float cConfigReaderJSON::GetTargetRadius() { return targetInfo.radius; }
glm::vec3 cConfigReaderJSON::GetTargetStartPos() { return targetInfo.startPosition; }

// Spring
glm::vec3 cConfigReaderJSON::GetSpringStartPos() { return springInfo.startPosition; }
glm::vec3 cConfigReaderJSON::GetSpringAnchorPos() { return springInfo.anchorPosition; }
float cConfigReaderJSON::GetSpringRadius() { return springInfo.radius; }
float cConfigReaderJSON::GetSpringConstant() { return springInfo.springConstant; }
float cConfigReaderJSON::GetSpringRestLength() { return springInfo.restLength; }
float cConfigReaderJSON::GetSpringRestitution() { return springInfo.restitution; }

int cConfigReaderJSON::GetNumOfMeshes()
{
	return this->numOfMeshes + this->GetHCNumOfJoints();
}