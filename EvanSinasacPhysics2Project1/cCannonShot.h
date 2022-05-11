//Evan Sinasac - 1081418
//INFO6019 Physics and Simulation and INFO6025 Configuration and Deployment Midterm
//cCannonShot.h description:
//						The cCannonShot header file, this class inherits from cParticle and adds two variables that
//						each shot requires.  isAlive is the important one, I wanted to do some type specific stuff 
//						to the meshes in the main (mostly just make the energy shot get bigger over time)
//						Also add the getters and setters for the new variables

#pragma once

#include <physics/cParticle.h>

namespace nPhysics
{
	class cCannonShot : public cParticle
	{
	private:
		bool isAlive;
		int type;
	public:
		cCannonShot(float mass, const glm::vec3& position);
		virtual ~cCannonShot();

		virtual void Integrate(float deltaTime);


		virtual void SetIsAlive(bool newIsAlive);
		virtual bool GetIsAlive();

		void SetType(int newType);
		int GetType();
	};
}