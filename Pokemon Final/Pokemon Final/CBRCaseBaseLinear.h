#pragma once
//Dummy class 
class CBRCaseBaseLinear : public CBRCaseBaseLinear{
public:
	CBRCaseBaseLinear();
	~CBRCaseBaseLinear(); 
	std::vector<CBRCaseDistance> GetKNN(int K,float threshold) override; 
	float GetDistance(CBRCase * a, CBRCase * b) override;
};
