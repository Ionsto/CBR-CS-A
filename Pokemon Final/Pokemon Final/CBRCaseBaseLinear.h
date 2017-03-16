#pragma once
//This class is an implementation of the CaseBase using an linear storage system
#include "CBRCaseBase.h"
//Dummy class 
class CBRCaseBaseLinear : public CBRCaseBase {
public:
	//Linear vector
	std::vector<std::unique_ptr<CBRCase>> CaseBase;
	CBRCaseBaseLinear();
	//Implementations of parent class functions 
	virtual ~CBRCaseBaseLinear() override; 
	std::vector<CBRCaseDistance> GetKNN(int K,float threshold, CBREnviroment * env) override; 
	//float GetDistance(CBRCase * a, CBRCase * b) override;
	bool IsEmpty() override;
	void InsertCase(std::unique_ptr<CBRCase> Case) override;
	void RemoveCase(CBRCase * Case) override;
	CBRCase * GetCaseView(int i) override;
	virtual int GetCaseCount() override;
	void Save(std::ofstream &s) override;
	void Load(std::ifstream &s) override;
};
