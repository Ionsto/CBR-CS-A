#include "CBRInstance.h"
#include "CBRCaseBaseLinear.h"
#include <iostream>
CBRInstance::CBRInstance()
{
	CaseBase = std::make_unique<CBRCaseBaseLinear>();
	CurrentCase = std::make_unique<CBRCase>();
}

CBRInstance::~CBRInstance()
{
	CaseBase.reset();
	CurrentCase.reset();
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
		std::vector<CBRCaseDistance> NearestCases = CaseBase->GetKNN((int)expf(CaseBase->DistanceWeight.SearchKNN), expf(CaseBase->DistanceWeight.MaxSearchThreshold), CurrentCase->StartEnviroment.get());
		if (NearestCases.size() == 0)
		{
			//Random moves
			CurrentCase->GenerateRandomMove();
		}
		else
		{
			CBRCaseDistance NearestCase = NearestCases[0];
			if (NearestCase.Distance < expf(CaseBase->DistanceWeight.IdenticalThreshold))
			{
				//Chose whether to exploit or explore
				if (NearestCase.Case->Exploit())
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
				if (NearestCase.Case->Exploit())
				{
					CurrentCase->Move = GetMoveFromCases(NearestCases);
				}
				else
				{
					CurrentCase->GenerateRandomMove();
				}
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
		AvCase[cases[i].Case->Move] += cases[i].Case->Utility /(cases[i].Distance);
	}
	int BestMove = 0;
	float MoveVotes = -INT_MAX;
	for (int i = 0;i < 4;++i)
	{
		if (AvCase[i] > MoveVotes)
		{
			BestMove = i;
			MoveVotes = AvCase[i];
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
	CurrentCase->CalculateUtility(&CaseBase->DistanceWeight);
	
	//Lending valitity to previous cases, or discrediting them
	std::vector<CBRCaseDistance> NearestCases = CaseBase->GetKNN((int)expf(CaseBase->DistanceWeight.SearchKNN), expf(CaseBase->DistanceWeight.MaxSearchThreshold), CurrentCase->EndEnviroment.get());
	if (NearestCases.size() == 0)
	{
		//Random moves
		float DeltaExploration = -CurrentCase->Utility * expf(CaseBase->DistanceWeight.ExplorationConstant);
		if (CurrentCase->Utility < 0) {
			DeltaExploration *= 5;
		}
		CurrentCase->Exploration += DeltaExploration;
		CaseBase->InsertCase(std::move(CurrentCase));
	}
	else
	{
		CBRCaseDistance NearestCase = NearestCases[0];
		if (NearestCase.Distance < expf(CaseBase->DistanceWeight.IdenticalThreshold))
		{
			if (NearestCase.Case->Move != CurrentCase->Move)
			{
				if ((CurrentCase->Utility - NearestCase.Case->Utility) > expf(CaseBase->DistanceWeight.ReplacingUtilityThreshold))
				{
					//Remove the NearstCas
					CaseBase->RemoveCase(NearestCase.Case);
					//Insert the CurrentCase
					CaseBase->InsertCase(std::move(CurrentCase));
				}
			}
			else
			{
				float DeltaExploration = -CurrentCase->Utility * expf(CaseBase->DistanceWeight.ExplorationConstant);
				if (CurrentCase->Utility < 0) {
					DeltaExploration *= 5;
				}
				NearestCase.Case->Exploration += DeltaExploration;
				if (++NearestCase.Case->ExplorationTestsCount >= (int)(exp(CaseBase->DistanceWeight.ExplorationMaxTests)))
				{
					NearestCase.Case->ExplorationTestsCount = 0;
					NearestCase.Case->Exploration = 0;
				}
			}
		}
		else
		{
			float DeltaExploration = -CurrentCase->Utility * expf(CaseBase->DistanceWeight.ExplorationConstant);
			if (CurrentCase->Utility < 0) {
				DeltaExploration *= 5;
			}
			CurrentCase->Exploration += DeltaExploration;
			CaseBase->InsertCase(std::move(CurrentCase));
		}
	}
}


void CBRInstance::Load(std::string s)
{
	std::ifstream stream = std::ifstream(s);
	if (stream) {
		CaseBase->Load(stream);
	}
	stream.close();
}
void CBRInstance::Save(std::string s)
{
	std::ofstream stream = std::ofstream(s);
	if (stream) {
		CaseBase->Save(stream);
	}
	stream.close();
}
