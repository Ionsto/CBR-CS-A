/*
This is an instance of an AI, each AI will have different trained learned patterns or enviroment weights.
*/
#include <memory>
#include "CBREnviroment.h"
#include "CBRCaseBase.h"
#include "CBRCase.h"
class CBRInstance{
public:
	//The case base
	std::unique_ptr<CBRCaseBase> CaseBase;
	//Case the AI is currently working on (needed to be kept from getmove->resolveanswer)
	std::unique_ptr<CBRCase> CurrentCase;
	CBRInstance();
	~CBRInstance();
	//An adaption function that takes the mode of the nearby moves
	int GetMoveModel(std::vector<CBRCaseDistance> cases);
	//This takes a mode weighted by applicablity (Utility/Distance)
	int GetMoveWeightedAv(std::vector<CBRCaseDistance> cases);
	int GetMoveFromCases(std::vector<CBRCaseDistance> cases);
	//This one half of the AI system, gets the move to be played, called before a turn
	int GetMove(std::unique_ptr<CBREnviroment> startenv);
	//This is the other half, it resolves what happened in the turn, called after a turn 
	void ResolveAnswer(std::unique_ptr<CBREnviroment> finalenv);
	//Saves and loads the entirety of the AI
	void Save(std::string s);
	void Load(std::string s);
};			
