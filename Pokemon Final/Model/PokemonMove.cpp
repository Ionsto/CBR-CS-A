#include "PokemonMove.h"



PokemonMove::PokemonMove()
{
	AttackSpeed = 5;
	BaseDamage = 10;
	CurrentUses = 0;
	MaxUses = 8;
	AttackType = TypeTypes::Normal;
}


PokemonMove::~PokemonMove()
{
}

//Attack definitions

PokemonMoveQuickAttack::PokemonMoveQuickAttack()
{
	BaseDamage = 20;
	AttackSpeed = 1;
	MaxUses = 4;
	AttackType = TypeTypes::Normal;
}
PokemonMoveTackle::PokemonMoveTackle()
{
	BaseDamage = 40;
	AttackSpeed = 5;
	AttackType = TypeTypes::Normal;
}