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
	float UsesLeft;
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
	//Mapping attributes to ids
	//Poor coding style, but otherwise correct
	//Also very fast, due to the fact it is one jump table, and one pointer
	float* AttrMap[56] = {
		&Owned.Health,//0
		&Owned.Type,
		&Owned.Attack,
		&Owned.Defence,
		&Owned.Moves[0].AttackSpeed,
		&Owned.Moves[0].BaseDamage,
		&Owned.Moves[0].DefenseBuff,
		&Owned.Moves[0].UsesLeft,
		&Owned.Moves[0].AttackType,

		&Owned.Moves[1].AttackSpeed,
		&Owned.Moves[1].BaseDamage,
		&Owned.Moves[1].DefenseBuff,
		&Owned.Moves[1].UsesLeft,
		&Owned.Moves[1].AttackType,

		&Owned.Moves[2].AttackSpeed,
		&Owned.Moves[2].BaseDamage,
		&Owned.Moves[2].DefenseBuff,
		&Owned.Moves[2].UsesLeft,
		&Owned.Moves[2].AttackType,

		&Owned.Moves[3].AttackSpeed,
		&Owned.Moves[3].BaseDamage,
		&Owned.Moves[3].DefenseBuff,
		&Owned.Moves[3].UsesLeft,
		&Owned.Moves[3].AttackType,
		&Opponent.Health,//27
		&Opponent.Type,
		&Opponent.Attack,
		&Opponent.Defence,
		&Opponent.Moves[0].AttackSpeed,
		&Opponent.Moves[0].BaseDamage,
		&Opponent.Moves[0].DefenseBuff,
		&Opponent.Moves[0].UsesLeft,
		&Opponent.Moves[0].AttackType,

		&Opponent.Moves[1].AttackSpeed,
		&Opponent.Moves[1].BaseDamage,
		&Opponent.Moves[1].DefenseBuff,
		&Opponent.Moves[1].UsesLeft,
		&Opponent.Moves[1].AttackType,

		&Opponent.Moves[2].AttackSpeed,
		&Opponent.Moves[2].BaseDamage,
		&Opponent.Moves[2].DefenseBuff,
		&Opponent.Moves[2].UsesLeft,
		&Opponent.Moves[2].AttackType,

		&Opponent.Moves[3].AttackSpeed,
		&Opponent.Moves[3].BaseDamage,
		&Opponent.Moves[3].DefenseBuff,
		&Opponent.Moves[3].UsesLeft,
		&Opponent.Moves[3].AttackType};
	CBREnviroment();
	~CBREnviroment();
	float GetAttribute(int n);
	void SetAttribute(int n,float val);
	void Save(std::ofstream &s);
	void Load(std::ifstream &s);
};
