#include "CBRWeights.h"
#include <math.h>
#include <stdlib.h>

CBRWeights::CBRWeights()
{
	ElementCount = 56;
	for (int i = 0; i < ElementCount; ++i)
	{
		Attr[i] = 1;
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
		Attr[i] += delta*(((rand() % 100) / (float)100) - 0.5);
	}
	//Difference in implementation for this and attr is due these constants being pulled over from 
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