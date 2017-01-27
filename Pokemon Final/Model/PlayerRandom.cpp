#include "PlayerRandom.h"
#include "PokemonMagikarp.h"
#include <random>


PlayerRandom::PlayerRandom()
{
	MyPokemon[0] = std::make_unique<PokemonMagikarp>();
	ActivePokemon = 0;
}


PlayerRandom::~PlayerRandom()
{
}

int PlayerRandom::GetMove(GameInstance * gm)
{
	return (rand() % 4);
}