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
};
class CBRCaseBase {
public:
	//Weights for the distance
	CBRWeights DistanceWeight;
	CBRCaseBase();
	~CBRCaseBase();
	virtual std::vector<CBRCaseDistance> GetKNN(int K,float threshold,CBREnviroment * env);
	//returns weighted eucliden distance between two Cases
	virtual float GetDistance(CBREnviroment * a,CBREnviroment * b);
	virtual bool IsEmpty();
	virtual void InsertCase(std::unique_ptr<CBRCase> Case);
	virtual void RemoveCase(CBRCase * Case);
	std::queue<CBRCaseDistance> MergeSort(std::queue<CBRCaseDistance> list);
	std::queue<CBRCaseDistance> MergeMerge(std::queue<CBRCaseDistance> a, std::queue<CBRCaseDistance> b);
};
