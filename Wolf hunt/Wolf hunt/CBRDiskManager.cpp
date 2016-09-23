#include "CBRDiskManager.h"
#include <fstream>



CBRDiskManager::CBRDiskManager()
{
}


CBRDiskManager::~CBRDiskManager()
{
}

void CBRDiskManager::SaveCaseBase(std::string loc,CBRInstance * cbr)
{
	std::ofstream stream;
	stream.open(loc);
	if (stream.is_open())
	{
		for (int i = 0; i < cbr->CaseBase.size(); ++i)
		{
			stream << cbr->CaseBase[i];
		}
	}
	stream.close();
}
void CBRDiskManager::LoadCaseBase(std::string loc,CBRInstance * cbr)
{
	std::ifstream stream;
	stream.open(loc);
	if (stream.is_open())
	{
		while(!stream.eof())
		{
			CBRCase * newcase = new CBRCase();
			stream >> *newcase;
			cbr->CaseBase.push_back(newcase);
		}
	}
	stream.close();
}