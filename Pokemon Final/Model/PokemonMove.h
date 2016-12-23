#pragma once
#include "TypeOptions.h"
#include <string>
class PokemonMove
{
public:
	//0 means attack is executed instantly, execution bias to A.
	//The higher the speed, the lower the first execution bias (e.g. MS = 1 Attacks are always executed before MS = 4 attacks)
	std::string Name;
	int AttackSpeed;
	int BaseDamage;
	int MaxUses;
	int CurrentUses;
	TypeTypes AttackType;
	PokemonMove();
	~PokemonMove();
};

class PokemonMoveTackle : public PokemonMove {
public:
	PokemonMoveTackle();
};
class PokemonMoveQuickAttack : public PokemonMove {
public:
	PokemonMoveQuickAttack();
};

