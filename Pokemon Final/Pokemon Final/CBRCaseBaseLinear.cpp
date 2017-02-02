#include "CBRCaseBaseLinear.h"

CBRCaseBaseLinear::CBRCaseBaseLinear()
{
	CaseBase = std::vector<std::unique_ptr<CBRCase>>();
}
CBRCaseBaseLinear::~CBRCaseBaseLinear()
{
}

std::vector<CBRCaseDistance> CBRCaseBaseLinear::GetKNN(int K, float threshold, CBREnviroment * env)
{
	std::queue<CBRCaseDistance> NearestCases = std::queue<CBRCaseDistance>();
	for (int i = 0;i < CaseBase.size();++i)
	{
		float Distance = GetDistance(CaseBase[i]->StartEnviroment.get(),env);
		if (Distance < threshold)
		{
			CBRCaseDistance dist = CBRCaseDistance();
			dist.Case = CaseBase[i].get();
			dist.Distance = Distance;
			NearestCases.push(dist);
		}
	}
	//Merge sort
	NearestCases = MergeSort(NearestCases);
	std::vector<CBRCaseDistance> NearestCasesVec = std::vector<CBRCaseDistance>();
	//Get all elements up to K cases
	for (int i = 0;i < fminf(K,NearestCases.size());++i)
	{
		NearestCasesVec.push_back(NearestCases.front());
		NearestCases.pop();
	}
	return NearestCasesVec;
}
bool CBRCaseBaseLinear::IsEmpty()
{
	return CaseBase.empty();
}
void CBRCaseBaseLinear::InsertCase(std::unique_ptr<CBRCase> Case)
{
	CaseBase.push_back(std::move(Case));
}

void CBRCaseBaseLinear::RemoveCase(CBRCase * Case)
{
	//Get passed a view of the case, then remove it from ownership
	//Find Case
	//Delete Case
	for (int i = 0; i < CaseBase.size();++i)
	{
		if (CaseBase[i].get() == Case)
		{
			CaseBase.erase(CaseBase.begin() + i);
			return;
		}
	}
}