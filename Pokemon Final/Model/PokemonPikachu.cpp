#include "PokemonPikachu.h"



PokemonPikachu::PokemonPikachu()
{
	this->PokemonType = TypeTypes::Electric;
	MoveSet[0] = std::make_unique<PokemonMoveQuickAttack>();
	MoveSet[1] = std::make_unique<PokemonMoveShock>();
	MoveSet[2] = std::make_unique<PokemonMoveTackle>();
	MoveSet[3] = std::make_unique<PokemonMoveTackle>();
}


PokemonPikachu::~PokemonPikachu()
{
}
