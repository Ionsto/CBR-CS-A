#include "CBRInstance.h"
#include "CBRCaseBaseLinear.h"
CBRInstance::CBRInstance()
{
	IdenticalThreshold = 1;
	ExplorationConstant = 1;
	MaxSearchThreshold = 10;
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
		std::vector<CBRCaseDistance> NearestCases = CaseBase->GetKNN(10, MaxSearchThreshold, startenv.get());
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
				if (CurrentCase->Exploit())
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
}

int CBRInstance::GetMoveFromCases(std::vector<CBRCaseDistance> cases)
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

void CBRInstance::ResolveAnswer(std::unique_ptr<CBREnviroment> finalenv)
{
	CurrentCase->EndEnviroment = std::move(finalenv);
	CurrentCase->CalculateUtility();
	
	//Lending valitity to previous cases, or discrediting them
	std::vector<CBRCaseDistance> NearestCases = CaseBase->GetKNN(10, MaxSearchThreshold, finalenv.get());
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
				float DeltaExploration = abs(CurrentCase->Utility) * ExplorationConstant;
				if (CurrentCase->Utility < 0) {
					DeltaExploration *= 5;
				}
				NearestCase.Case->Exploration += DeltaExploration;
				if (++NearestCase.Case->ExplorationTestsCount >= NearestCase.Case->ExplorationMaxTests)
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
}

