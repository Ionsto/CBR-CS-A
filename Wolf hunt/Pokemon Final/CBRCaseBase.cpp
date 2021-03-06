#include "CBRCaseBase.h"
#include "CBREnviroment.h"
#include <math.h>
CBRCaseBase::CBRCaseBase()
{
}

CBRCaseBase::~CBRCaseBase()
{
} 

//K-Nearest neighbor 
std::vector<CBRCaseDistance> CBRCaseBase::GetKNN(int K,float threshold,CBREnviroment * env)
{
	std::vector<CBRCaseDistance> NearestCases = std::vector<CBRCaseDistance>();
	return NearestCases;
}
//Recursive merge sort
std::queue<CBRCaseDistance> CBRCaseBase::MergeSort(std::queue<CBRCaseDistance> list)
{
	if (list.size() <= 1)
	{
		return list;
	}
	std::queue<CBRCaseDistance> left = std::queue<CBRCaseDistance>();
	std::queue<CBRCaseDistance> right = std::queue<CBRCaseDistance>();
	int size = list.size();
	for (int i = 0; i < floor(size / 2);++i)
	{
		left.push(list.front());
		list.pop();
	}
	left = MergeSort(left);
	for (int i = floor(size / 2); i < size;++i)
	{
		right.push(list.front());
		list.pop();
	}
	right = MergeSort(right);
	return MergeMerge(left, right);
}
//Semi-abstract functions, these get overriden
CBRCase * CBRCaseBase::GetCaseView(int i)
{
	return NULL;
}
int CBRCaseBase::GetCaseCount()
{
	return 0;
}

std::queue<CBRCaseDistance> CBRCaseBase::MergeMerge(std::queue<CBRCaseDistance> a, std::queue<CBRCaseDistance> b)
{
	std::queue<CBRCaseDistance> returnvec = std::queue<CBRCaseDistance>();
	while (a.size() != 0 && b.size() != 0)
	{
		if (a.front().Distance < b.front().Distance)
		{
			returnvec.push(a.front());
			a.pop();
		}
		else
		{
			returnvec.push(b.front());
			b.pop();
		}
	}
	while (a.size() != 0)
	{
		returnvec.push(a.front());
		a.pop();
	}
	while (b.size() != 0)
	{
		returnvec.push(b.front());
		b.pop();
	}
	return returnvec;
}
//returns weighted eucliden distance between two Cases 
float CBRCaseBase::GetDistance(CBREnviroment * a, CBREnviroment * b)
{
	float distancesqrd = 0;
	//List all elements
	for (int i = 0;i < a->ElementCount;++i)
	{
		distancesqrd += expf(BehaviorWeight.GetDistanceAttributes(i)) * (a->GetAttributes(i) - b->GetAttributes(i)) * (a->GetAttributes(i) - b->GetAttributes(i));
	}
	//
	return sqrt(distancesqrd);
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

//Default behevior
bool CBRCaseBase::IsEmpty()
{
	return true;
}

void CBRCaseBase::Save(std::ofstream &s)
{
	BehaviorWeight.Save(s);
}
void CBRCaseBase::Load(std::ifstream &s)
{
	BehaviorWeight.Load(s);
}