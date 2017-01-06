#pragma once
class CBRCase
{
public:
	std::unique_ptr<CBREnviroment> StartEnviroment;
	std::unique_ptr<CBREnviroment> EndEnviroment;
	int Move;
	//This is a function of how effective the case was at improving 
	float UtiltityValue;
	CBRCase();
	~CBRCase();
	void CalculateUtility();
	float CalculateFitness(CBREnviroment * env);
};
