#include "CBRWeights.h"
#include <math.h>
#include <stdlib.h>

CBRWeights::CBRWeights()
{
	ElementCount = 56;
	for (int i = 0; i < ElementCount; ++i)
	{
		DistanceAttributes[i] = 0;
		FitnessAttributes[i] = 0;
	}
	IdenticalThreshold = 0;
	ExplorationConstant = 0;
	MaxSearchThreshold = 0;
	ReplacingUtilityThreshold = 0;
}

CBRWeights::~CBRWeights()
{
}
void CBRWeights::RandomiseWeights(float delta)
{
	for (int i = 0; i < ElementCount; ++i)
	{
		DistanceAttributes[i] += delta*(((rand() % 100) / (float)100) - 0.5);
		FitnessAttributes[i] += delta*(((rand() % 100) / (float)100) - 0.5);
	}
	//Difference in implementation for this and DistanceAttributes is due these constants being pulled over from 
	IdenticalThreshold += delta*(((rand() % 100) / (float)100) - 0.5);
	ExplorationConstant += delta*(((rand() % 100) / (float)100) - 0.5);
	MaxSearchThreshold += delta*(((rand() % 100) / (float)100) - 0.5);
	ReplacingUtilityThreshold += delta*(((rand() % 100) / (float)100) - 0.5);
	//if (MaxSearchThreshold > 500)
	//{
	//	MaxSearchThreshold = 500;
	//}
}
void CBRWeights::CopyWeights(CBRWeights weights)
{
	for (int i = 0; i < ElementCount; ++i)
	{
		DistanceAttributes[i] = weights.GetDistanceAttributes(i);
		FitnessAttributes[i] = weights.GetFitnessAttributes(i);
	}
	IdenticalThreshold = weights.IdenticalThreshold;
	ExplorationConstant = weights.ExplorationConstant;
	MaxSearchThreshold = weights.MaxSearchThreshold;
	ReplacingUtilityThreshold = weights.ReplacingUtilityThreshold;
}
float CBRWeights::GetDistanceAttributes(int n)
{
	return DistanceAttributes[n];
}

float CBRWeights::GetFitnessAttributes(int n)
{
	return DistanceAttributes[n];
}

void CBRWeights::Save(std::ofstream &s)
{
	for (int i = 0; i < ElementCount; ++i)
	{
		s << DistanceAttributes[i] << " ";
		s << FitnessAttributes[i] << " ";
	}
	s << IdenticalThreshold << " ";
	s << ExplorationConstant << " ";
	s << MaxSearchThreshold << " ";
	s << ReplacingUtilityThreshold << " ";
}
void CBRWeights::Load(std::ifstream &s)
{
	for (int i = 0; i < ElementCount; ++i)
	{
		s >> DistanceAttributes[i];
		s >> FitnessAttributes[i];
	}
	s >> IdenticalThreshold;
	s >> ExplorationConstant;
	s >> MaxSearchThreshold;
	s >> ReplacingUtilityThreshold;
}