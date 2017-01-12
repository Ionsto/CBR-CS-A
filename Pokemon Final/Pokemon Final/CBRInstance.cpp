#include "CBRInstance.h"

CBRInstance::CBRInstance()
{
	IdenticalThreshold = 1;
	ExplorationConstant = 1;
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
		CBRCaseDistance NearestCase = CaseBase->GetNearestCase(startenv);
		if(NearestCase.Distance < IdenticalThreshold)
		{
			//Chose whether to exploit or explore
			if(CurrentCase->Exploit())
			{
				CurrentCase->Move = NearestCase.Case->Move;
			}
			else
			{
				CurrentCase->GenerateRandomMove();
			}
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
	CurrentCase->CalculateUtility();
	
	//Lending valitity to previous cases, or discrediting them
	CBRCaseDistance NearestCase = CaseBase->GetNearestCase(startenv);
	if(NearestCase.Case->Distance(CurrentCase) < IdenticalCase)
	{
		float DeltaExploration = abs(CurrentCase->Utility) * ExplorationConstant;
		if(CurrentCase->Utility < 0){
			DeltaExploration *= 5;
		}
		NearestCase.Case->Exploration += DeltaExploration;
		if(++NearestCase.Case->ExplorationTestsCount >= NearestCase.Case->ExplorationMaxTests)
		{
			NearestCase.Case->ExplorationTestsCount = 0;
		}
	}
}

