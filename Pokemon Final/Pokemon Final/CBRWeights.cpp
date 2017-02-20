#include "CBRWeights.h"
#include <math.h>
#include <stdlib.h>

CBRWeights::CBRWeights()
{
	ElementCount = 48;
	for (int i = 0; i < ElementCount; ++i)
	{
		Attr[i] = 0;
	}
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
}
void CBRWeights::CopyWeights(CBRWeights weights)
{
	for (int i = 0; i < ElementCount; ++i)
	{
		Attr[i] = weights.GetAttribute(i);
	}
}
float CBRWeights::GetAttribute(int n)
{
	return Attr[n];
}

void CBRWeights::Save(std::ofstream s)
{
	for (int i = 0; i < ElementCount; ++i)
	{
		s << Attr[i] << " ";
	}
}
void CBRWeights::Load(std::ifstream s)
{
	for (int i = 0; i < ElementCount; ++i)
	{
		s >> Attr[i];
	}
}