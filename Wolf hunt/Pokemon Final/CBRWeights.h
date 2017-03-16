#pragma once
#include <fstream>
class CBRWeights
{
public:
	//A multiplier for the exploration
	float ExplorationConstant;
	//The distance at which two cases can be considered Identical 
	//i.e. consider your friend if they cut their hair, same person, minor distance 
	float IdenticalThreshold;
	//The pruning point for KNN, reject anything with distance greater than exp(this)
	float MaxSearchThreshold;
	//This is the max amount of tests that may happen, before the exploration system is reset for one case
	float ExplorationMaxTests;
	//Exp(this) is the amount of nearby cases that are retrieved to look at
	float SearchKNN;
	//The extra utility nessesary before a previous course of action is replaced by the new move
	float ReplacingUtilityThreshold;
	//The weighting values for each attribute when calculating distance - passed through exp
	float DistanceAttributes[48];
	//The weights for the Fittness calculations, since some attributes are harmfull, these weights can be -
	float FitnessAttributes[48];
	//The amount of elements in *Attributes
	int ElementCount;
	CBRWeights();
	~CBRWeights();
	//This shakes up the weights, sliding them by a value of delta * (random float from -0.5 to +0.5)
	void RandomiseWeights(float delta);
	//Getters
	float GetDistanceAttributes(int n);
	float GetFitnessAttributes(int n);
	//Copy system
	void CopyWeights(CBRWeights weights);
	//Saves and loads all weights
	void Save(std::ofstream &s);
	void Load(std::ifstream &s);
};

