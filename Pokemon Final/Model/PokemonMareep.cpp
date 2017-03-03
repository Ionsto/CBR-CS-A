#include "PokemonMareep.h"



PokemonMareep::PokemonMareep()
{
	this->PokemonType = TypeTypes::Electric;
	MoveSet[0] = std::make_unique<PokemonMoveQuickAttack>();
	MoveSet[1] = std::make_unique<PokemonMoveQuickAttack>();
	MoveSet[2] = std::make_unique<PokemonMoveLightning>();
	MoveSet[3] = std::make_unique<PokemonMoveQuickAttack>();
}


PokemonMareep::~PokemonMareep()
{
}
