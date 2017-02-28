#include "CBRCase.h"
#include "CBREnviroment.h"
CBRCase::CBRCase()
{
	ExplorationMaxTests = 10;
	ExplorationTestsCount = 0;
}


CBRCase::~CBRCase()
{
	StartEnviroment.reset();
	EndEnviroment.reset();
}

void CBRCase::GenerateRandomMove()
{
	this->Move = rand()%4;
}

bool CBRCase::Exploit()
{
	return !((exp(Exploration) * (rand()%50)) > 25);	
}

void CBRCase::CalculateUtility(CBRWeights * weight)
{
	Utility = CalculateFitness(EndEnviroment.get(),weight) - CalculateFitness(StartEnviroment.get(),weight);
}

float CBRCase::CalculateFitness(CBREnviroment * env,CBRWeights * weight)
{
	//This is the fittness function
	float distancesqrd = 0;
	//List all elements
	for (int i = 0; i < env->ElementCount; ++i)
	{
		distancesqrd += expf(weight->GetFitnessAttributes(i)) * env->GetAttributes(i);
	}
	//
	return sqrt(distancesqrd);
	//return env->Owned.Health - env->Opponent.Health;
}

void CBRCase::Save(std::ofstream &s)
{
	StartEnviroment->Save(s);
	EndEnviroment->Save(s);
	s << Move << " ";
	s << Utility << " ";
	s << Exploration << " ";
	s << ExplorationMaxTests << " ";
	s << ExplorationTestsCount << " ";
}
void CBRCase::Load(std::ifstream &s)
{
	StartEnviroment = std::make_unique<CBREnviroment>();
	EndEnviroment = std::make_unique<CBREnviroment>();
	StartEnviroment->Load(s);
	EndEnviroment->Load(s);
	s >> Move;
	s >> Utility;
	s >> Exploration;
	s >> ExplorationMaxTests;
	s >> ExplorationTestsCount;
}