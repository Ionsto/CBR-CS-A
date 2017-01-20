#pragma once
#include "CBRCaseBase.h"
//Dummy class 
class CBRCaseBaseLinear : public CBRCaseBase{
public:
	CBRCaseBaseLinear();
	~CBRCaseBaseLinear(); 
	std::vector<CBRCaseDistance> GetKNN(int K,float threshold, CBREnviroment * env) override; 
	//float GetDistance(CBRCase * a, CBRCase * b) override;
};
