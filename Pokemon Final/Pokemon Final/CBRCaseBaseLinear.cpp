#include "CBRCaseBaseLinear.h"

CBRCaseBaseLinear::CBRCaseBaseLinear()
{
	CaseBase = std::vector<std::unique_ptr<CBRCase>>();
}
CBRCaseBaseLinear::~CBRCaseBaseLinear()
{
	for (int i = 0; i < CaseBase.size();++i)
	{
		CaseBase[i].reset();
	}
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
int CBRCaseBaseLinear::GetCaseCount()
{
	return CaseBase.size();
}
CBRCase * CBRCaseBaseLinear::GetCaseView(int i)
{
	return CaseBase[i].get();
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
void CBRCaseBaseLinear::Save(std::ofstream &s)
{
	DistanceWeight.Save(s);
	s << GetCaseCount() << " ";
	for (int i = 0; i < CaseBase.size(); ++i)
	{
		GetCaseView(i)->Save(s);
	}
}
void CBRCaseBaseLinear::Load(std::ifstream &s)
{
	DistanceWeight.Load(s);
	int CaseCount = 0;
	s >> CaseCount;
	for (int i = 0; i < CaseCount; ++i)
	{
		InsertCase(std::make_unique<CBRCase>());
		CaseBase[i]->Load(s);
	}
}