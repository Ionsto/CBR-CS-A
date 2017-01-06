#include "CBRCase.h"

CBRCase::CBRCase()
{
}


CBRCase::~CBRCase()
{
}

void CBRCase::CalculateUtility()
{
	Utility = CalculateFitness(EndEnviroment) - CalculateFitness(StartEnviroment);
}

float CBRCase::CalculateFitness(CBREnviroment * env)
{
	return 0.0; 	
}
