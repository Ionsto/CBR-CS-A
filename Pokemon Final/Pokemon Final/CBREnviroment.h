/*
The CBREnvrioment class represents a snapshot of the game at a spesific time.
The enviroments can be objectivly compared in similarity, with different weightings between each parameter
*/
#pragma once
#include <fstream>
struct MoveCase {
	float AttackSpeed; 
	float BaseDamage;
	float DefenseBuff;
	float MaxUses;
	float CurrentUses;
	float AttackType;
};
struct PokmonCase {
	float Health;
	float Type;
	float Attack;
	float Defence;
	MoveCase Moves[4];
};

class CBREnviroment{
public:
	PokmonCase Owned;
	PokmonCase Opponent;
	int ElementCount;
	CBREnviroment();
	~CBREnviroment();
	float GetAttribute(int n);
	void SetAttribute(int n,float val);
	void Save(std::ofstream &s);
	void Load(std::ifstream &s);
};
