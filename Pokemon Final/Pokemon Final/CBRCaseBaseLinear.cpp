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
	std::vector<CBRCaseDistance> NearestCases = std::vector<CBRCaseDistance>();

	return NearestCases;
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