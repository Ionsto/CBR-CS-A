/*
CBRCase is a class representing a single case in the Case-based-reasoning system
The case stores the start, end enviroments, and the move used to transform from the start to the end
it also stores some infomation about the utility(or usefulness of a move) and this forms the basis of the 
*/
#pragma once

#include "CBRWeights.h"
#include <memory>
#include "CBREnviroment.h"
class CBRCase
{
public:
	std::unique_ptr<CBREnviroment> StartEnviroment;
	std::unique_ptr<CBREnviroment> EndEnviroment;
	int Move;
	//This is a function of how effective the case was at improving 
	float Utility;
	//This is a counter, it is reset every ExplorationMaxTests tests, and it increments slightly on a +utility, and increments greatly on a -utility
	//This exploration value is used to pick randomly whether the AI will exploit, or explore 
	float Exploration;
	//Counter to keep track of exploration events
	int ExplorationTestsCount;
	CBRCase();
	~CBRCase();
	void GenerateRandomMove();
	bool Exploit();
	void CalculateUtility(CBRWeights * weight);
	float CalculateFitness(CBREnviroment * env,CBRWeights * weight);
	void Save(std::ofstream &s);
	void Load(std::ifstream &s);
};

