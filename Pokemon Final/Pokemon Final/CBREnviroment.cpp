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
	//More pointer magic, to use the DistanceAttributes as a huge switch-case system
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
	//Although ElementCount SHOULD be constant, it is loaded so that if an smaller DistanceAttributes system was implmented - no error 
	s >> ElementCount;
	float Attributes;
	for (int i = 0; i < ElementCount; ++i)
	{
		s >> Attributes;
		SetAttributes(i,Attributes);
	}
}