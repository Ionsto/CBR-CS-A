#include "CBRWeights.h"
#include <math.h>
#include <stdlib.h>

CBRWeights::CBRWeights()
{
	ElementCount = 48;
	for (int i = 0; i < ElementCount; ++i)
	{
		DistanceAttributes[i] = 0;
		FitnessAttributes[i] = 0;
	}
	IdenticalThreshold = 0;
	ExplorationConstant = 0;
	MaxSearchThreshold = logf(60);
	ReplacingUtilityThreshold = 0;
	ExplorationMaxTests = logf(5);
	SearchKNN = logf(15);
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
	IdenticalThreshold += delta*(((rand() % 100) / (float)100) - 0.5);
	ExplorationConstant += delta*(((rand() % 100) / (float)100) - 0.5);
	MaxSearchThreshold += delta*(((rand() % 100) / (float)100) - 0.5);
	ReplacingUtilityThreshold += delta*(((rand() % 100) / (float)100) - 0.5);
	ExplorationMaxTests += delta*(((rand() % 100) / (float)100) - 0.5);
	SearchKNN += delta*(((rand() % 100) / (float)100) - 0.5);
	if (SearchKNN > logf(60))
	{
		SearchKNN = logf(60);
	}
	if (SearchKNN < 0)
	{
		SearchKNN = 0;
	}
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
	ExplorationMaxTests = weights.ExplorationMaxTests;
	SearchKNN = weights.SearchKNN;
}
float CBRWeights::GetDistanceAttributes(int n)
{
	return DistanceAttributes[n];
}

float CBRWeights::GetFitnessAttributes(int n)
{
	return FitnessAttributes[n];
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
	s << ExplorationMaxTests << " ";
	s << SearchKNN << " ";
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
	s >> ExplorationMaxTests;
	s >> SearchKNN;
}
