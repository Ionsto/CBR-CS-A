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
	//Case base
	std::vector<CBRCase*> CaseBase;
	CBRDiskManager * CaseBaseLoader;
	//Distance weightings
	CBRWeight DistanceWeights;
	//Value weightings
	CBRWeight ValueWeights;
	float UnclaimedOtherPenalty;
	float SearchDistanceThreshold;
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
	void Load(std::string loadloc);
	void FeedBackCase(CBRCase * Case);
	CBRCase * GetCase(CBREnvironment sitrep);
	float CalculateValue(CBREnvironment siterep);
	static bool AllPairsComp(float * a, float * b);
};

