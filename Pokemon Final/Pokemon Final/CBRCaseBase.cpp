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
