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

float CBREnviroment::GetAttribute(int n)
{
	return *(AttrMap[n]);
}
void CBREnviroment::SetAttribute(int n,float val)
{
	//More pointer magic, to use the Attr as a huge case switch system
	(*(AttrMap[n])) = val;
}
void CBREnviroment::Save(std::ofstream &s)
{
	s << ElementCount << " ";
	for (int i = 0; i < ElementCount; ++i)
	{
		s << GetAttribute(i) << " ";
	}
}
void CBREnviroment::Load(std::ifstream &s)
{
	//Although ElementCount SHOULD be constant, if an extended attribute system was implmented 
	s >> ElementCount;
	float Attribute;
	for (int i = 0; i < ElementCount; ++i)
	{
		s >> Attribute;
		SetAttribute(i,Attribute);
	}
}