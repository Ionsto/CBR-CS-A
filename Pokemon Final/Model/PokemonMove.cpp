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
	Name = "Quick attack";
	BaseDamage = 20;
	AttackSpeed = 1;
	MaxUses = 4;
	AttackType = TypeTypes::Normal;
}
PokemonMoveTackle::PokemonMoveTackle()
{
	Name = "Tackle";
	BaseDamage = 30;
	AttackSpeed = 5;
	MaxUses = 2;
	AttackType = TypeTypes::Normal;
}
PokemonMoveShock::PokemonMoveShock()
{
	Name = "Shock";
	BaseDamage = 40;
	AttackSpeed = 2;
	MaxUses = 2;
	AttackType = TypeTypes::Electric;
}