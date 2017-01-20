/*
This is an instance of an AI, each AI will have different trained learned patterns or enviroment weights.
*/
#include <memory>
#include "CBREnviroment.h"
#include "CBRCaseBase.h"
#include "CBRCase.h"
class CBRInstance{
public:
	float ExplorationConstant;
	float IdenticalThreshold;
	float MaxSearchThreshold;
	float ReplacingUtilityThreshold;
	std::unique_ptr<CBRCaseBase> CaseBase;
	std::unique_ptr<CBRCase> CurrentCase;
	CBRInstance();
	~CBRInstance();
	int GetMoveFromCases(std::vector<CBRCaseDistance> cases);
	void GetMove(std::unique_ptr<CBREnviroment> startenv);
	void ResolveAnswer(std::unique_ptr<CBREnviroment> finalenv);
};			
