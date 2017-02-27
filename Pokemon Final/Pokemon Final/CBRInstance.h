/*
This is an instance of an AI, each AI will have different trained learned patterns or enviroment weights.
*/
#include <memory>
#include "CBREnviroment.h"
#include "CBRCaseBase.h"
#include "CBRCase.h"
class CBRInstance{
public:
	//float ExplorationConstant;
	//float IdenticalThreshold;
	//float MaxSearchThreshold;
	//float ReplacingUtilityThreshold;
	std::unique_ptr<CBRCaseBase> CaseBase;
	std::unique_ptr<CBRCase> CurrentCase;
	CBRInstance();
	~CBRInstance();
	int GetMoveModel(std::vector<CBRCaseDistance> cases);
	int GetMoveWeightedAv(std::vector<CBRCaseDistance> cases);
	int GetMoveFromCases(std::vector<CBRCaseDistance> cases);
	int GetMove(std::unique_ptr<CBREnviroment> startenv);
	void ResolveAnswer(std::unique_ptr<CBREnviroment> finalenv);
	void Save(std::string s);
	void Load(std::string s);
};			
