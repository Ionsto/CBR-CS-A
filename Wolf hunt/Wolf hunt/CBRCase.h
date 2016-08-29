#pragma once
#include <queue>
#include "CBREnvironment.h"
#include "AIAction.h"
class CBRCase
{
public:
	//case should contain the Situation
	//IDK, positions of Entities, types, health and 
	///Self
	CBREnvironment EnviromentStart;
	float CalculatedValueStart;
	//Enviroment
	//case should contain the Solution
	std::vector<AIAction*> Moves;
	//case should contain the Result
	//This should have the total outcome, and also the calculated outcome of the situation
	CBREnvironment EnviromentEnd;
	float CalculatedValueEnd;
	//This is the amount of times the case has created similar outcomes
	int Validity;
	int ExecutionTime;
	CBRCase();
	~CBRCase();
	void RandomiseMoves();
	void ApplyActionsToEntity(EntityAI * entity); 
	void MutateCases(float subfactor);
};

