#include "PlayerDeterministic.h"
#include "PokemonPikachu.h"
#include <random>


PlayerDeterministic::PlayerDeterministic()
{
	MyPokemon[0] = std::make_unique<PokemonPikachu>();
	ActivePokemon = 0;
	PlayCount = 0;
}


PlayerDeterministic::~PlayerDeterministic()
{
}

int PlayerDeterministic::GetMove(Player * enemy)
{
	int Plays[] = {1,3,3,0,0,2,2};
	if (PlayCount > 7)
	{
		return 4;
	}
	return Plays[PlayCount++];
}