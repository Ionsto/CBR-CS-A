
#pragma once
class CBRCase
{
public:
	std::unique_ptr<CBREnviroment> StartEnviroment;
	std::unique_ptr<CBREnviroment> EndEnviroment;
	int Move;
	//This is a function of how effective the case was at improving 
	float UtiltityValue;
	//Exploration count is the amount of tests that have taken place for other moves, but identical enviroments, increments on exploration
	int ExplorationCount;
	//This is a counter, it is reset every ExplorationMaxTests tests, and it increments slightly on a +utility, and increments greatly on a -utility
	//This exploration value is used to pick randomly whether the AI will exploit, or explore 
	float Exploration;
	//This is the max amount of tests that may happen, before the exploration is reset
	int ExplorationMaxTests;
	int ExplorationTestsCount;
	CBRCase();
	~CBRCase();
	void GenerateRandomMove();
	bool Exploit();
	void CalculateUtility();
	float CalculateFitness(CBREnviroment * env);
};

