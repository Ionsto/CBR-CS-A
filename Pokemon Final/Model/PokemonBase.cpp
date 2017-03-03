#include "PokemonBase.h"



PokemonBase::PokemonBase()
{
	for (int i = 0; i < 4; ++i)
	{
		MoveSet[i] = std::make_unique<PokemonMove>();
	}
	Health = 100;
	Defense = 22;
	Attack = 20;
}
PokemonBase::PokemonBase(const PokemonBase & base)
{
	for (int i = 0; i < 4; ++i)
	{
		MoveSet[i] = std::make_unique<PokemonMove>(*base.MoveSet[i].get());
	}
	Health = base.Health;
	Defense = base.Defense;
	Attack = base.Attack;
}


PokemonBase::~PokemonBase()
{
	for (int i = 0; i < 4; ++i)
	{
		MoveSet[i].reset();
	}
}
