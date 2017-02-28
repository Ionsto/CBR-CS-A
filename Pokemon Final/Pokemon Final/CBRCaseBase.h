/*
CBRCasebase is a delegaded system for storing retrieving and removeing cases.
The CBRCasebase will have two versions, a linear list (slow but for testing) and a kd-tree (a kind of binary tree)
*/
#pragma once
#include <vector>
#include <queue>
#include <memory>
#include "CBRCase.h"
#include "CBRWeights.h"
struct CBRCaseDistance{
  float Distance;
  CBRCase * Case;
  CBRCaseDistance()
  {
	  Distance = 0;
	  Case = NULL;
  };
  CBRCaseDistance(const CBRCaseDistance & Case)
  {
	  Distance = Case.Distance;
	  this->Case = Case.Case;
  };
  ~CBRCaseDistance()
  {
  };
};
class CBRCaseBase {
public:
	//Weights for the distance
	CBRWeights DistanceWeight;
	CBRCaseBase();
	virtual ~CBRCaseBase();
	virtual std::vector<CBRCaseDistance> GetKNN(int K,float threshold,CBREnviroment * env);
	//returns weighted eucliden distance between two Cases
	virtual float GetDistance(CBREnviroment * a,CBREnviroment * b);
	//Function just needs to garuntee that each case in the case base can be accesed if i goes from 0 to (Case Count - 1)
	virtual CBRCase * GetCaseView(int i);
	virtual int GetCaseCount();
	virtual bool IsEmpty();
	virtual void InsertCase(std::unique_ptr<CBRCase> Case);
	virtual void RemoveCase(CBRCase * Case);
	std::queue<CBRCaseDistance> MergeSort(std::queue<CBRCaseDistance> list);
	std::queue<CBRCaseDistance> MergeMerge(std::queue<CBRCaseDistance> a, std::queue<CBRCaseDistance> b);
	virtual void Save(std::ofstream &s);
	virtual void Load(std::ifstream &s);
};
