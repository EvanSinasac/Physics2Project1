//Evan Sinasac - 1081418
//INFO6019 Physics and Simulation and INFO6025 Configuration and Deployment Midterm
//cCannonShot.cpp description:
//						The cpp file for the cCannonShot class, with the actual functions and integration.
//						I also finally figured out how to actually inherit from cParticle with this lol

//#include <physics/cCannonShot.h>
#include "cCannonShot.h"
#include <iostream>

namespace nPhysics
{
	//oh...my...gawd...this was all I needed for the project...welp, I figured it out eventually lmfao
	cCannonShot::cCannonShot(float mass, const glm::vec3& position) : cParticle(mass, position)
	{
		this->isAlive = false;
		this->type = 0;
	}
	cCannonShot::~cCannonShot()
	{

	}

	void cCannonShot::Integrate(float deltaTime)
	{

	}

	void cCannonShot::SetIsAlive(bool newIsAlive)
	{
		this->isAlive = newIsAlive;
	}
	bool cCannonShot::GetIsAlive()
	{
		return this->isAlive;
	}

	void cCannonShot::SetType(int newType)
	{
		this->type = newType;
	}
	int cCannonShot::GetType()
	{
		return this->type;
	}
}