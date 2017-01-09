#pragma once
class CBRCase
{
public:
	std::unique_ptr<CBREnviroment> StartEnviroment;
	std::unique_ptr<CBREnviroment> EndEnviroment;
	int Move;
	//This is a function of how effective the case was at improving 
	float UtiltityValue;
	//Exploration vs exploitation is a 
	int Exploitation;
	int Exploration;
	CBRCase();
	~CBRCase();
	void GenerateRandomMove();
	void CalculateUtility();
	float CalculateFitness(CBREnviroment * env);
};

