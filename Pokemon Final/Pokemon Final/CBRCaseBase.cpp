#include "CBRCaseBase.h"

CBRCaseBase::CBRCaseBase()
{
}

CBRCaseBase::~CBRCaseBase()
{
} 
//K-Nearest neighbor 
std::vector<CBRCaseDistance> CBRCaseBase::GetKNN(int K,float threshold)
{
	std::vector<CBRCaseDistance> NearestCases = std::vector<CBRCaseDistance>();
	
	return NearestCases;
}
//returns weighted eucliden distance between two Cases 
float CBRCaseBase::GetDistance(CBRCase * a, CBRCase * b)
{
  return 0;
}

void CBRCaseBase::InsertCase(std::unique_ptr<CBRCase> Case)
{
	//Move the case into its location
	//Pass off ownership to the casebase
}

void CBRCaseBase::RemoveCase(CBRCase * Case)
{
	//Get passed a view of the case, then remove it from ownership
	//Find Case
	//Delete Case
}
