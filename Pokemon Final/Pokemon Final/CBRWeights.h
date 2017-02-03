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
class CBRWeights
{
public:
	//PokmonCase Owned;
	//PokmonCase Opponent;
	float Attr[48];
	int ElementCount;
	CBRWeights();
	~CBRWeights();
	float GetAttribute(int n);
};

