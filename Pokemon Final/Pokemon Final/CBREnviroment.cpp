#include "CBREnviroment.h"

CBREnviroment::CBREnviroment()
{

}

CBREnviroment::~CBREnviroment()
{
}

float CBREnviroment::GetAttribute(int n)
{
	//Mapping attributes to ids
	//Poor coding style, but otherwise correct
	//Also very fast, due to the fact it is one jump table, and one pointer
	const float* Attr[] = { 
		&Owned.Health,//0
		&Owned.Type,
		&Owned.Attack,
		&Owned.Defence,
		&Owned.Moves[0].AttackSpeed,
		&Owned.Moves[0].BaseDamage,
		&Owned.Moves[0].MaxUses,
		&Owned.Moves[0].CurrentUses,
		&Owned.Moves[0].AttackType,

		&Owned.Moves[1].AttackSpeed,
		&Owned.Moves[1].BaseDamage,
		&Owned.Moves[1].MaxUses,
		&Owned.Moves[1].CurrentUses,
		&Owned.Moves[1].AttackType,

		&Owned.Moves[2].AttackSpeed,
		&Owned.Moves[2].BaseDamage,
		&Owned.Moves[2].MaxUses,
		&Owned.Moves[2].CurrentUses,
		&Owned.Moves[2].AttackType,

		&Owned.Moves[3].AttackSpeed,
		&Owned.Moves[3].BaseDamage,
		&Owned.Moves[3].MaxUses,
		&Owned.Moves[3].CurrentUses,
		&Owned.Moves[3].AttackType, 
		&Opponent.Health,//27
		&Opponent.Type,
		&Opponent.Attack,
		&Opponent.Defence,
		&Opponent.Moves[0].AttackSpeed,
		&Opponent.Moves[0].BaseDamage,
		&Opponent.Moves[0].MaxUses,
		&Opponent.Moves[0].CurrentUses,
		&Opponent.Moves[0].AttackType,

		&Opponent.Moves[1].AttackSpeed,
		&Opponent.Moves[1].BaseDamage,
		&Opponent.Moves[1].MaxUses,
		&Opponent.Moves[1].CurrentUses,
		&Opponent.Moves[1].AttackType,

		&Opponent.Moves[2].AttackSpeed,
		&Opponent.Moves[2].BaseDamage,
		&Opponent.Moves[2].MaxUses,
		&Opponent.Moves[2].CurrentUses,
		&Opponent.Moves[2].AttackType,

		&Opponent.Moves[3].AttackSpeed,
		&Opponent.Moves[3].BaseDamage,
		&Opponent.Moves[3].MaxUses,
		&Opponent.Moves[3].CurrentUses,
		&Opponent.Moves[3].AttackType};
	return *(Attr[n]);
}