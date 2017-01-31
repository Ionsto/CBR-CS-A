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


PokemonBase::~PokemonBase()
{
	for (int i = 0; i < 4; ++i)
	{
		MoveSet[i].release();
	}
}
