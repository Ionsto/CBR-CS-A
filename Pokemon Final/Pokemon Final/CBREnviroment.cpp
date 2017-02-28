#include "CBREnviroment.h"

CBREnviroment::CBREnviroment()
{
	ElementCount = 48;
	Owned = PokmonCase();
	Opponent = PokmonCase();
}

CBREnviroment::~CBREnviroment()
{
}

float CBREnviroment::GetAttributes(int n)
{
	return *(AttributesMap[n]);
}
void CBREnviroment::SetAttributes(int n,float val)
{
	//More pointer magic, to use the DistanceAttributes as a huge case switch system
	(*(AttributesMap[n])) = val;
}
void CBREnviroment::Save(std::ofstream &s)
{
	s << ElementCount << " ";
	for (int i = 0; i < ElementCount; ++i)
	{
		s << GetAttributes(i) << " ";
	}
}
void CBREnviroment::Load(std::ifstream &s)
{
	//Although ElementCount SHOULD be constant, if an extended DistanceAttributesibute system was implmented 
	s >> ElementCount;
	float Attributes;
	for (int i = 0; i < ElementCount; ++i)
	{
		s >> Attributes;
		SetAttributes(i,Attributes);
	}
}