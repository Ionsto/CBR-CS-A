#include "CBRCase.h"
#include "CBREnviroment.h"
CBRCase::CBRCase()
{
	ExplorationMaxTests = 10;
	ExplorationTestsCount = 0;
}


CBRCase::~CBRCase()
{
}

void CBRCase::GenerateRandomMove()
{
	this->Move = rand()%4;
}

bool CBRCase::Exploit()
{
	return (exp(Exploration) * (rand()%50)) > 25;	
}

void CBRCase::CalculateUtility()
{
	Utility = CalculateFitness(EndEnviroment.get()) - CalculateFitness(StartEnviroment.get());
}

float CBRCase::CalculateFitness(CBREnviroment * env)
{
	//This is the fittness function
	return env->GetAttribute(0) - env->GetAttribute(24);
}
