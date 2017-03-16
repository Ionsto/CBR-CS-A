#include "CBRCase.h"
#include "CBREnviroment.h"
CBRCase::CBRCase()
{
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
	int randi = (rand() % 50);
	float total = randi * exp(Exploration);
	return !((exp(Exploration) * (rand()%50)) > 25);	
}
//Calculates much the move has helped the AI
void CBRCase::CalculateUtility(CBRWeights * weight)
{
	Utility = CalculateFitness(EndEnviroment.get(),weight) - CalculateFitness(StartEnviroment.get(),weight);
}

//Calcuates the "fitness"/ how desirable an ENVIRONMENT is
float CBRCase::CalculateFitness(CBREnviroment * env,CBRWeights * weight)
{
	//This is the fittness function
	float distancesqrd = 0;
	for (int i = 0; i < env->ElementCount; ++i)
	{
		distancesqrd += weight->GetFitnessAttributes(i) * env->GetAttributes(i);
	}
	return (distancesqrd);
}

void CBRCase::Save(std::ofstream &s)
{
	StartEnviroment->Save(s);
	EndEnviroment->Save(s);
	s << Move << " ";
	s << Utility << " ";
	s << Exploration << " ";
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
	s >> ExplorationTestsCount;
}
