#include "CBRInstance.h"

CBRInstance::CBRInstance()
{
	IdenticalThreshold = 1;
	ExplorationConstant = 1;
	MaxSearchThreshold = 10;
	ReplacingUtilityThreshold = 10;
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
			if(CurrentCase->Exploit() && NearestCase->Move != NULL)
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
			//Alternitivly use modal move from knearest cases
			std::vector<CBRCaseDistance> NearestCases = CaseBase->GetKNN(10, MaxSearchThreshold);
			if(NearestCases.size() > 0)
			{
				//Adaption
				CurrentCase->Move = GetMoveFromCases(NearestCases);
			}
			else
			{
				//Random move
				CurrentCase->GenerateRandomMove();
			}
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
		if(NearestCase.Case->Move != CurrentCase->Move)
		{
			if((CurrentCase->Utility - NearestCase.Case->Utility) > ReplacingUtilityThreshold)
			{
				//Remove the NearstCas
				CaseBase->RemoveCase(NearestCase.Case);
				//Insert the CurrentCase
				CaseBase->InsertCase(std::move(CurrentCase));
			}
		}
		else	
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
	else
	{
		//Insert the case
		CaseBase->InsertCase(std::move(CurrentCase));
	}
}

