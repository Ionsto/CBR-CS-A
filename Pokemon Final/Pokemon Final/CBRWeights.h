#pragma once
#include <fstream>
class CBRWeights
{
public:
	//PokmonCase Owned;
	//PokmonCase Opponent;
	float ExplorationConstant;
	float IdenticalThreshold;
	float MaxSearchThreshold;
	//This is the max amount of tests that may happen, before the exploration is reset
	float ExplorationMaxTests;
	float SearchKNN;
	float ReplacingUtilityThreshold;
	float DistanceAttributes[48];
	float FitnessAttributes[48];
	int ElementCount;
	CBRWeights();
	~CBRWeights();
	void RandomiseWeights(float delta);
	float GetDistanceAttributes(int n);
	float GetFitnessAttributes(int n);
	void CopyWeights(CBRWeights weights);
	void Save(std::ofstream &s);
	void Load(std::ifstream &s);
};

