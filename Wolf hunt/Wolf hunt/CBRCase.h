#pragma once
#include <queue>
#include "CBREnvironment.h"
#include "AIAction.h"
#include <iostream>
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
	Vector DeltaMovement;
	//std::vector<AIAction*> Moves;
	//case should contain the Result
	//This should have the total outcome, and also the calculated outcome of the situation
	CBREnvironment EnviromentEnd;
	float CalculatedValueEnd;
	float DeltaValue;
	//This is the amount of times the case has created similar outcomes
	int Validity;
	int ExecutionTime;
	CBRCase();
	~CBRCase();
	float& GetOutputParams(int id);
	void RandomiseMoves();
	void ApplyActionsToEntity(EntityWolf * entity); 
	void MutateCases(float subfactor);
	friend std::ostream& operator<<(std::ostream& ios, const CBRCase& cbrc);
	friend std::istream& operator>>(std::istream& ios, CBRCase& cbrc);
};

