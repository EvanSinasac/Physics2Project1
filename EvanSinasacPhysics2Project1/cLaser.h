//Evan Sinasac - 1081418
//INFO6019 Physics and Simulation and INFO6025 Configuration and Deployment Midterm
//cLaser.h description:
//					Header file for cLaser, the Laser has an additional and more likely end of life condition in the
//					distance it is from the cannon, so we have added a variable to keep store the distance from the 
//					cannon that we kill the particle at (so we can update it from external file), as well as a function
//					that calculates the distance between the particle and the cannon

#pragma once

// Realized we have an isAlive stuff in cParticle, so my inbetween CannonShot is no longer needed
#include <physics/cParticle.h>

namespace nPhysics
{
	class cLaser : public cParticle
	{
	private:
		/*float distanceToDeath;
		glm::vec3 cannonPosition;*/
		float timeToDie;
		float timeAlive;
	public:
		cLaser(float mass, const glm::vec3& position);
		virtual ~cLaser();

		virtual void Integrate(float deltaTime);

		void SetTimeToDie(float tToD);

		// By timer instead of distance
		/*void SetDistanceToDeath(float dToD);

		float DistanceFromCanon(glm::vec3 cannonPos);
		void SetCannonPosition(glm::vec3 cannonPos);*/
	};
}