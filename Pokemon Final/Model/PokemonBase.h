#pragma once
#include "PokemonMove.h"
#include <memory>
class PokemonBase
{
public:
	//These are two base stats that affect the damage calculations
	float Attack;
	float Defense;
	int Health;
	//The way types interact gives very large modifiers on the damage calculations
	TypeTypes PokemonType;
	std::unique_ptr<PokemonMove> MoveSet[4];
	PokemonBase();
	PokemonBase(const PokemonBase & base);
	~PokemonBase();
};

