#include "CBRInstance.h"

CBRInstance::CBRInstance()
{
	
}

CBRInstance::~CBRInstance()
{
}
/*
-First find nearest case
*/
void CBRInstance::GetMove(std::unique_ptr<CBREnviroment> startenv)
{
	//
	CurrentCase->StartEnviroment = std::move(startenv);
	if(CaseBase.IsEmpty())
	{
		//Make a random move
		CurrentCase->GenerateRandomMove();
		return CurrentCase->Move;
	}
	else
	{
		float DistanceToNearestCase;
		if(DistanceToNearestCase < IdenticalThreshold)
		{
			
		}
		else
		{
			//Get nearest 10 cases
			//Use weighted linear regression based on (learned values of importance) and (utility of each case).	
		}
	}
}

void CBRInstance::ResolveAnswer(std::unique_ptr<CBREnviroment> finalenv)
{
	CurrentCase->EndEnviroment = std::move(finalenv);
	CurrentCase->CalcuateUtility();
}
