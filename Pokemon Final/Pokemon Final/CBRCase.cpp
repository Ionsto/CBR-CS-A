#include "CBRCase.h"

CBRCase::CBRCase()
{
}


CBRCase::~CBRCase()
{
}

void CBRCase::GenerateRandomMove()
{
	this->Move = rand()%4;
}

void CBRCase::CalculateUtility()
{
	Utility = CalculateFitness(EndEnviroment) - CalculateFitness(StartEnviroment);
}

float CBRCase::CalculateFitness(CBREnviroment * env)
{
	return 0.0; 	
}
