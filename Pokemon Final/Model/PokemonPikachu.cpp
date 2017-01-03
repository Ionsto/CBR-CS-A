#include "PokemonPikachu.h"



PokemonPikachu::PokemonPikachu()
{
	this->PokemonType = TypeTypes::Electric;
	MoveSet[0] = std::make_unique<PokemonMoveQuickAttack>();
	MoveSet[1] = std::make_unique<PokemonMoveShock>();
}


PokemonPikachu::~PokemonPikachu()
{
}
