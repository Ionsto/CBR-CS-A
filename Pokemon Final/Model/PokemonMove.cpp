#include "PokemonMove.h"



PokemonMove::PokemonMove()
{
	AttackSpeed = 5;
	BaseDamage = 10;
	CurrentUses = 0;
	MaxUses = 8;
	DefenseBuff = 1;
	AttackType = TypeTypes::Normal;
}
PokemonMove::PokemonMove(const PokemonMove & move)
{
	AttackSpeed = move.AttackSpeed;
	BaseDamage = move.BaseDamage;
	CurrentUses = move.CurrentUses;
	MaxUses = move.MaxUses;
	DefenseBuff = move.DefenseBuff;
	AttackType = move.AttackType;
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
	MaxUses = 2;
	AttackType = TypeTypes::Normal;
}
PokemonMoveTackle::PokemonMoveTackle()
{
	Name = "Tackle";
	BaseDamage = 30;
	AttackSpeed = 5;
	MaxUses = 3;
	AttackType = TypeTypes::Normal;
}
PokemonMoveShock::PokemonMoveShock()
{
	Name = "Shock";
	BaseDamage = 40;
	AttackSpeed = 2;
	MaxUses = 1;
	AttackType = TypeTypes::Electric;
}

PokemonMoveLightning::PokemonMoveLightning()
{
	Name = "Lightning";
	BaseDamage = 35;
	AttackSpeed = 3;
	MaxUses = 2;
	AttackType = TypeTypes::Electric;
}

PokemonMoveHarden::PokemonMoveHarden()
{
	Name = "Harden";
	BaseDamage = 10;
	AttackSpeed = 2;
	MaxUses = 2;
	DefenseBuff = 2;
	AttackType = TypeTypes::Normal;
}