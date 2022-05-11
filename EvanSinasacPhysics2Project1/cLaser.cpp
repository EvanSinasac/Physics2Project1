//Evan Sinasac - 1081418
//INFO6019 Physics and Simulation and INFO6025 Configuration and Deployment Midterm
//cLaser.cpp description:
//					The cpp file for cLaser class, implementation for the distance from the cannon death condition,
//					Laser's also die if they hit the ground

#include <../cLaser.h>
#include <iostream>

namespace nPhysics
{

	cLaser::cLaser(float mass, const glm::vec3& position) : cParticle(mass, position)
	{
		SetAcceleration(glm::vec3(0.0f, -3.2f, 0.0f)); //safety default, gets overriden when the shot is made
		SetIsAlive(true);
		this->timeAlive = 0.0f;
		this->timeToDie = 30.0f;	// safety default
	}
	cLaser::~cLaser()
	{

	}

	void cLaser::Integrate(float deltaTime)
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

			timeAlive += deltaTime;

			if (timeAlive >= timeToDie)
			{
				SetIsAlive(false);
			}
		}
	}

	void cLaser::SetTimeToDie(float tToD)
	{
		this->timeToDie = tToD;
	}


}