#include "CBRWeights.h"
#include <math.h>
#include <stdlib.h>

CBRWeights::CBRWeights()
{
	ElementCount = 56;
	for (int i = 0; i < ElementCount; ++i)
	{
		Attr[i] = 0;
	}
	IdenticalThreshold = 10;
	ExplorationConstant = 1;
	MaxSearchThreshold = 50;
	ReplacingUtilityThreshold = 2;
}

CBRWeights::~CBRWeights()
{
}
void CBRWeights::RandomiseWeights(float delta)
{
	for (int i = 0; i < ElementCount; ++i)
	{
		Attr[i] += delta*(((rand() % 100)/(float)100)-0.5);
	}
	//Difference in implementation for this and attr is due these constants being pulled over from 
	IdenticalThreshold = expf(logf(IdenticalThreshold) + delta*(((rand() % 100) / (float)100) - 0.5));
	ExplorationConstant = expf(logf(ExplorationConstant) + delta*(((rand() % 100) / (float)100) - 0.5));
	MaxSearchThreshold = expf(logf(MaxSearchThreshold) + delta*(((rand() % 100) / (float)100) - 0.5));
	ReplacingUtilityThreshold = expf(logf(ReplacingUtilityThreshold) + delta*(((rand() % 100) / (float)100) - 0.5));
}
void CBRWeights::CopyWeights(CBRWeights weights)
{
	for (int i = 0; i < ElementCount; ++i)
	{
		Attr[i] = weights.GetAttribute(i);
	}
	IdenticalThreshold = weights.IdenticalThreshold;
	ExplorationConstant = weights.ExplorationConstant;
	MaxSearchThreshold = weights.MaxSearchThreshold;
	ReplacingUtilityThreshold = weights.ReplacingUtilityThreshold;
}
float CBRWeights::GetAttribute(int n)
{
	return Attr[n];
}

void CBRWeights::Save(std::ofstream &s)
{
	for (int i = 0; i < ElementCount; ++i)
	{
		s << Attr[i] << " ";
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
		s >> Attr[i];
	}
	s >> IdenticalThreshold;
	s >> ExplorationConstant;
	s >> MaxSearchThreshold;
	s >> ReplacingUtilityThreshold;
}