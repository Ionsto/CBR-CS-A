#pragma once
#include <vector>
#include "CBRCase.h"
#include "CBREnvironment.h"
#include "CBRDiskManager.h"
#include "CBRWeight.h"
#include <iostream>
class CBRInstance
{
public:
	struct ClosePair {
		float NewDist;
		int CloseCase;
		ClosePair(float d, int cc) { NewDist = d; CloseCase = cc; };
		static bool SortComp(ClosePair a, ClosePair b)
		{
			return a.NewDist < b.NewDist;
		}
	};
	//Case base
	std::vector<CBRCase*> CaseBase;
	CBRDiskManager * CaseBaseLoader;
	//Distance weightings
	CBRWeight DistanceWeights;
	//Value weightings
	CBRWeight ValueWeights;
	float UnclaimedOtherPenalty;
	float IdenticalCaseThreshold;
	float MinInsertionThreshold;
	float NearestNeighborDistance;
	float ValidityDistanceThreshold;
	float MaxArrayClaimentThreshold;
	//Some form of mapping for parametors of the case base
	//Some form of situation calcuation
	CBRInstance();
	~CBRInstance();
	//This should return the calculat
	//float EvalCase(CBRCase * a);
	//Distance between two entities
	float DistanceInfo(EntityInfo a, EntityInfo b);
	//Gives distance in two cases according to this Instance
	float Distance(CBREnvironment a, CBREnvironment b);
	void Save(std::string loadloc);
	void Load(std::string loadloc);
	void FeedBackCase(CBRCase * Case);
	void AdaptionWeightedLinearRegression(CBRCase * NewCase,std::vector<ClosePair> nearcase);
	CBRCase * GetCase(CBREnvironment sitrep);
	void WeightedLinearRegression(std::vector<CBRCase*> cases,int paramx,int paramy,float * intercept, float * gradient, float * error);
	float CalculateValue(CBREnvironment siterep);
	static bool AllPairsComp(float * a, float * b);
};

