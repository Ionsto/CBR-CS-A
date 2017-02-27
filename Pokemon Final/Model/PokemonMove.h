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
	float DefenseBuff;
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

class PokemonMoveShock : public PokemonMove {
public:
	PokemonMoveShock();
};

class PokemonMoveLightning : public PokemonMove {
public:
	PokemonMoveLightning();
}; 

class PokemonMoveHarden : public PokemonMove {
public:
	PokemonMoveHarden();
};

