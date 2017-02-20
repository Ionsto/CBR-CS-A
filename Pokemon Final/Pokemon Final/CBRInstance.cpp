#include "CBRInstance.h"
#include "CBRCaseBaseLinear.h"
CBRInstance::CBRInstance()
{
	IdenticalThreshold = 10;
	ExplorationConstant = 1;
	MaxSearchThreshold = 50;
	ReplacingUtilityThreshold = 10;
	CaseBase = std::make_unique<CBRCaseBaseLinear>();
	CurrentCase = std::make_unique<CBRCase>();
}

CBRInstance::~CBRInstance()
{
}
/*
-First find nearest case
*/
int CBRInstance::GetMove(std::unique_ptr<CBREnviroment> startenv)
{
	//Reset Current case
	CurrentCase = std::make_unique<CBRCase>();
	CurrentCase->StartEnviroment = std::move(startenv);


	if(CaseBase->IsEmpty())
	{
		//Make a random move
		CurrentCase->GenerateRandomMove();
		return CurrentCase->Move;
	}
	else
	{
		std::vector<CBRCaseDistance> NearestCases = CaseBase->GetKNN(20, MaxSearchThreshold, CurrentCase->StartEnviroment.get());
		if (NearestCases.size() == 0)
		{
			//Random moves
			CurrentCase->GenerateRandomMove();
		}
		else
		{
			CBRCaseDistance NearestCase = NearestCases[0];
			if (NearestCase.Distance < IdenticalThreshold)
			{
				//Chose whether to exploit or explore
				if (!NearestCase.Case->Exploit())
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
				//Adaption
				CurrentCase->Move = GetMoveFromCases(NearestCases);
			}
		}
	}
	return CurrentCase->Move;
}

int CBRInstance::GetMoveModel(std::vector<CBRCaseDistance> cases)
{
	int ModalCase[4] = { 0,0,0,0 };
	for (int i = 0;i < cases.size();++i)
	{
		++ModalCase[cases[i].Case->Move];
	}
	int BestMove = 0;
	int MoveVotes = 0;
	for (int i = 0;i < 4;++i)
	{
		if (ModalCase[i] > MoveVotes)
		{
			BestMove = i;
		}
	}
	return BestMove;
}
int CBRInstance::GetMoveWeightedAv(std::vector<CBRCaseDistance> cases)
{
	float AvCase[4] = {0,0,0,0};
	for (int i = 0;i < cases.size();++i)
	{
		AvCase[cases[i].Case->Move] += cases[i].Case->Utility/cases[i].Distance;
	}
	int BestMove = 0;
	int MoveVotes = -INT_MAX;
	for (int i = 0;i < 4;++i)
	{
		if (AvCase[i] > MoveVotes)
		{
			BestMove = i;
		}
	}
	return BestMove;
}
int CBRInstance::GetMoveFromCases(std::vector<CBRCaseDistance> cases)
{
	return GetMoveWeightedAv(cases);
}

void CBRInstance::ResolveAnswer(std::unique_ptr<CBREnviroment> finalenv)
{
	CurrentCase->EndEnviroment = std::move(finalenv);
	CurrentCase->CalculateUtility();
	
	//Lending valitity to previous cases, or discrediting them
	std::vector<CBRCaseDistance> NearestCases = CaseBase->GetKNN(10, MaxSearchThreshold, CurrentCase->EndEnviroment.get());
	if (NearestCases.size() == 0)
	{
		//Random moves
		CaseBase->InsertCase(std::move(CurrentCase));
	}
	else
	{
		CBRCaseDistance NearestCase = NearestCases[0];
		if (NearestCase.Distance < IdenticalThreshold)
		{
			if (NearestCase.Case->Move != CurrentCase->Move)
			{
				if ((CurrentCase->Utility - NearestCase.Case->Utility) > ReplacingUtilityThreshold)
				{
					//Remove the NearstCas
					CaseBase->RemoveCase(NearestCase.Case);
					//Insert the CurrentCase
					CaseBase->InsertCase(std::move(CurrentCase));
				}
			}
			else
			{
				float DeltaExploration = -CurrentCase->Utility * ExplorationConstant;
				if (CurrentCase->Utility < 0) {
					DeltaExploration *= 5;
				}
				NearestCase.Case->Exploration += DeltaExploration;
				if (++NearestCase.Case->ExplorationTestsCount >= NearestCase.Case->ExplorationMaxTests)
				{
					NearestCase.Case->ExplorationTestsCount = 0;
					NearestCase.Case->Exploration = 0;
				}
			}
		}
		else
		{
			//Insert the case
			CaseBase->InsertCase(std::move(CurrentCase));
		}
	}
}

