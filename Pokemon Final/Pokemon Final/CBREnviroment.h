/*
The CBREnvrioment class represents a snapshot of the game at a spesific time.
The enviroments can be objectivly compared in similarity, with different weightings between each parameter
*/
#pragma once
#include <fstream>
//Represents the attributes of a single move
struct MoveCase {
	float AttackSpeed; 
	float BaseDamage;
	float DefenseBuff;
	float UsesLeft;
	float AttackType;
	MoveCase()
	{
		AttackSpeed = 0;
		BaseDamage = 0;
		DefenseBuff = 0;
		UsesLeft = 0;
		AttackType = 0;
	}
};
//Represents the attributes of a single pokemon
struct PokmonCase {
	float Health;
	float Type;
	float Attack;
	float Defence;
	PokmonCase()
	{
		Health = 0;
		Type = 0;
		Attack = 0;
		Defence = 0;
	}
	MoveCase Moves[4];
};
//Represents the attributes of a single turn
class CBREnviroment{
public:
	PokmonCase Owned;
	PokmonCase Opponent;
	int ElementCount;
	//Mapping DistanceAttributes to ids
	//Poor coding style, but otherwise correct
	//Also very fast, due to the fact it is effectivly a jumptable, with data contiguous
	float* AttributesMap[48] = {
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
	//Gets & sets the value AT the pointer in the AttributeMap
	float GetAttributes(int n);
	void SetAttributes(int n,float val);
	//Saves and loads all of the attributes
	void Save(std::ofstream &s);
	void Load(std::ifstream &s);
};
