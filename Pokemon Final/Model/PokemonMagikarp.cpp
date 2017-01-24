#include "PokemonMagikarp.h"



PokemonMagikarp::PokemonMagikarp()
{
	this->PokemonType = TypeTypes::Water;
	MoveSet[0] = std::make_unique<PokemonMoveTackle>();
}


PokemonMagikarp::~PokemonMagikarp()
{
}
