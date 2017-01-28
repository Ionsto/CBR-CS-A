#include "PlayerRandom.h"
#include "PokemonPikachu.h"
#include <random>


PlayerRandom::PlayerRandom()
{
	MyPokemon[0] = std::make_unique<PokemonPikachu>();
	ActivePokemon = 0;
}


PlayerRandom::~PlayerRandom()
{
}

int PlayerRandom::GetMove(Player * enemy)
{
	return (rand() % 4);
}