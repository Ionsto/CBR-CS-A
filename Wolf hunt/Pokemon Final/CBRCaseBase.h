/*
CBRCasebase is a system for holding, saving and loading cases, it also hold the code for searching for KNN cases
The CBRCasebase will have two versions, a linear list (slow but for testing) and a kd-tree (a kind of binary tree) [not implmented]
*/
#pragma once
#include <vector>
#include <queue>
#include <memory>
#include "CBRCase.h"
#include "CBRWeights.h"
//This structure is used by the KNN to represent Cases and there Distance from another environment (env is implicit)
struct CBRCaseDistance{
  float Distance;
  CBRCase * Case;
  CBRCaseDistance()
  {
	  Distance = 0;
	  Case = NULL;
  };
  //Copy constructors are explicitly needed for unique_ptr
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
	//Weights that set an array of psuedo constants throughout the program, they define the charictor of the AI
	CBRWeights BehaviorWeight;
	CBRCaseBase();
	virtual ~CBRCaseBase();
	//Returns the K- nearest neighbores of environment in the casebase (within a threshold for early pruning)
	virtual std::vector<CBRCaseDistance> GetKNN(int K,float threshold,CBREnviroment * env);
	//Returns a weighted euclidean distance between two Cases
	virtual float GetDistance(CBREnviroment * a,CBREnviroment * b);
	//Function just needs to guarantee that each case in the case base can be accesed if i goes from 0 to (Case Count - 1)
	//(effectivly an enumarator)
	virtual CBRCase * GetCaseView(int i);
	virtual int GetCaseCount();
	virtual bool IsEmpty();
	virtual void InsertCase(std::unique_ptr<CBRCase> Case);
	//Key fact about this is that you do not need ownership unique_ptr, just a pointer (*),
	//as casebase should have constant ownership of the cases in the casebase
	virtual void RemoveCase(CBRCase * Case);
	//These two are recursive mergesorts, they are sorting with lowest distance to highest
	std::queue<CBRCaseDistance> MergeSort(std::queue<CBRCaseDistance> list);
	std::queue<CBRCaseDistance> MergeMerge(std::queue<CBRCaseDistance> a, std::queue<CBRCaseDistance> b);
	//Saves and loads all the cases and weight
	virtual void Save(std::ofstream &s);
	virtual void Load(std::ifstream &s);
};
