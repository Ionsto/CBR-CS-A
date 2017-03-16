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
	//The enviroment at the start and end of the case
	std::unique_ptr<CBREnviroment> StartEnviroment;
	std::unique_ptr<CBREnviroment> EndEnviroment;
	//The move played in between start & end environments - this cases move
	int Move;
	//This is a function of how effective the case was at "improving" the situation
	float Utility;
	//This is a counter, it is reset every ExplorationMaxTests tests, and it increments slightly on a +utility, and increments greatly on a -utility
	//This exploration value is used to pick randomly whether the AI will exploit, or explore 
	float Exploration;
	//Counter to keep track of exploration or explore events
	int ExplorationTestsCount;
	CBRCase();
	~CBRCase();
	void GenerateRandomMove();
	//This function consults the Exploration value, to check if the case should explore or exploit
	bool Exploit();
	//Gives a utlity value from start and end environments
	void CalculateUtility(CBRWeights * weight);
	//The fitness is a sum of the environment attributes * a weighting value
	//(NOTE unlike other weights, these are not passed through exp, as some attributes are negative)
	float CalculateFitness(CBREnviroment * env,CBRWeights * weight);
	//Save and load to files
	void Save(std::ofstream &s);
	void Load(std::ifstream &s);
};

