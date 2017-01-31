#pragma once
#include "CBRCaseBase.h"
//Dummy class 
class CBRCaseBaseLinear : public CBRCaseBase {
public:
	//This is a dummy class
	std::vector<std::unique_ptr<CBRCase>> CaseBase;
	CBRCaseBaseLinear();
	~CBRCaseBaseLinear(); 
	std::vector<CBRCaseDistance> GetKNN(int K,float threshold, CBREnviroment * env) override; 
	//float GetDistance(CBRCase * a, CBRCase * b) override;
	bool IsEmpty() override;
	void InsertCase(std::unique_ptr<CBRCase> Case) override;
	void RemoveCase(CBRCase * Case) override;
};
