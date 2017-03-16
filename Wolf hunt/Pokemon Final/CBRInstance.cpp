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
//Get move for the upcoming turn
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
		//Get nearby cases, to compare notes with CaseBase
		std::vector<CBRCaseDistance> NearestCases = CaseBase->GetKNN((int)expf(CaseBase->BehaviorWeight.SearchKNN), expf(CaseBase->BehaviorWeight.MaxSearchThreshold), CurrentCase->StartEnviroment.get());
		if (NearestCases.size() == 0)
		{
			//Random move, as we have no previous data
			CurrentCase->GenerateRandomMove();
		}
		else
		{
			CBRCaseDistance NearestCase = NearestCases[0];
			if (NearestCase.Distance < expf(CaseBase->BehaviorWeight.IdenticalThreshold))
			{
				//We know the case is identical now
				//Chose whether to exploit or explore
				if (NearestCase.Case->Exploit())
				{
					//We want to exploit the NearestCases known utility
					CurrentCase->Move = NearestCase.Case->Move;
				}
				else
				{
					//Going out on a limb to find new solutions
					CurrentCase->GenerateRandomMove();
				}
			}
			else
			{
				//Get nearest k cases
				//Use weighted modal move from k nearest cases to select a good move
				//Adaption
				if (NearestCase.Case->Exploit())
				{
					CurrentCase->Move = GetMoveFromCases(NearestCases);
				}
				else
				{
					//Find a new solution
					CurrentCase->GenerateRandomMove();
				}
			}
		}
	}
	return CurrentCase->Move;
}
//Unused
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
		//We want to push down cases that have -utility, as they are bad
		AvCase[cases[i].Case->Move] += cases[i].Case->Utility / (cases[i].Distance);
	}
	int BestMove = 0;
	float MoveVotes = -INT_MAX;
	//Find best move
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
	//Populate end envionment and complete the case
	CurrentCase->EndEnviroment = std::move(finalenv);
	CurrentCase->CalculateUtility(&CaseBase->BehaviorWeight);
	
	//Lending valitity to previous cases, or discrediting them
	std::vector<CBRCaseDistance> NearestCases = CaseBase->GetKNN((int)expf(CaseBase->BehaviorWeight.SearchKNN), expf(CaseBase->BehaviorWeight.MaxSearchThreshold), CurrentCase->EndEnviroment.get());
	if (NearestCases.size() == 0)
	{
		//Empty case, whack the new case right in there
		//dont forget to update exploration values
		float DeltaExploration = -CurrentCase->Utility * expf(CaseBase->BehaviorWeight.ExplorationConstant);
		if (CurrentCase->Utility < 0) {
			DeltaExploration *= 5;
		}
		CurrentCase->Exploration += DeltaExploration;
		CaseBase->InsertCase(std::move(CurrentCase));
	}
	else
	{
		CBRCaseDistance NearestCase = NearestCases[0];
		if (NearestCase.Distance < expf(CaseBase->BehaviorWeight.IdenticalThreshold))
		{
			//CurrentCase is identical to a previouse case
			if (NearestCase.Case->Move != CurrentCase->Move)
			{
				if ((CurrentCase->Utility - NearestCase.Case->Utility) > expf(CaseBase->BehaviorWeight.ReplacingUtilityThreshold))
				{
					//CurrentCase is better than the old one, so replace it
					//Remove the NearstCase
					CaseBase->RemoveCase(NearestCase.Case);
					//Insert the CurrentCase
					CaseBase->InsertCase(std::move(CurrentCase));
				}
			}
			else
			{
				//Either discredit, or lend support to the previouse case
				float DeltaExploration = -CurrentCase->Utility * expf(CaseBase->BehaviorWeight.ExplorationConstant);
				if (CurrentCase->Utility < 0) {
					DeltaExploration *= 5;
				}
				NearestCase.Case->Exploration += DeltaExploration;
				if (++NearestCase.Case->ExplorationTestsCount >= (int)(exp(CaseBase->BehaviorWeight.ExplorationMaxTests)))
				{
					NearestCase.Case->ExplorationTestsCount = 0;
					NearestCase.Case->Exploration = 0;
				}
			}
		}
		else
		{
			//No simalar cases, just add our case in
			float DeltaExploration = -CurrentCase->Utility * expf(CaseBase->BehaviorWeight.ExplorationConstant);
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
