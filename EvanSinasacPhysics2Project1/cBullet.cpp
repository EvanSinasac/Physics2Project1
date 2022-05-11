//Evan Sinasac - 1081418
//INFO6019 Physics and Simulation and INFO6025 Configuration and Deployment Midterm
//cBullet.cpp description:
//					The cpp file for the cBullet class.  Main difference from cParticle/cCannonShot is the change 
//					to end the particle's lifespan when the Bullet reaches the ground (y=0)

//#include <physics/cBullet.h>
#include "cBullet.h"
#include <iostream>

namespace nPhysics
{
	cBullet::cBullet(float mass, const glm::vec3& position) : cParticle(mass, position)
	{
		SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));
		SetIsAlive(true);
		this->timeAlive = 0.0f;
		this->timeToDie = 30.0f;	// safety default
	}
	cBullet::~cBullet()
	{

	}

	void cBullet::Integrate(float deltaTime)
	{
		if (GetIsAlive())
		{
			if (GetInverseMass() == 0.f)
			{
				return; // static things don't move!
			}

			SetPosition(glm::vec3(GetPosition() + GetVelocity() * deltaTime));
			// F*(1/m) = a
			SetVelocity(glm::vec3(GetVelocity() + (GetAcceleration() / GetInverseMass() * deltaTime)));

			// apply damping
			SetVelocity(glm::vec3(GetVelocity() * glm::pow(GetDamping(), deltaTime)));

			this->timeAlive += deltaTime;

			if (timeAlive >= timeToDie)
			{
				SetIsAlive(false);
			}
		}
	}

	void cBullet::SetTimeToDie(float tToD)
	{
		this->timeToDie = tToD;
	}

}