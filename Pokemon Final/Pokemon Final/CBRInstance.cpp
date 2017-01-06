#include "CBRInstance.h"

CBRInstance::CBRInstance()
{
	
}

CBRInstance::~CBRInstance()
{
}
/*
-First find nearest case
*/
void CBRInstance::GetMove(std::unique_ptr<CBREnviroment> startenv)
{
	//
	CurrentCase->StartEnviroment = std::move(startenv);
	if(CaseBase.IsEmpty())
	{
		//Make a random move
		
	}
	else
	{
		//Get nearest case
		//Make a random choice of what to 
	}
}

void CBRInstance::ResolveAnswer(std::unique_ptr<CBREnviroment> finalenv)
{
	CurrentCase->EndEnviroment = std::move(finalenv);
	CurrentCase->CalcuateUtility();
}
