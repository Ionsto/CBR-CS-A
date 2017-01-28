/*
The CBREnvrioment class represents a snapshot of the game at a spesific time.
The enviroments can be objectivly compared in similarity, with different weightings between each parameter
*/
#pragma once
struct MoveCase {
	float AttackSpeed; 
	float BaseDamage;
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
	CBREnviroment();
	~CBREnviroment();
	float GetAttribute(int n);
};
