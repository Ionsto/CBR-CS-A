#include "PokemonMagikarp.h"



PokemonMagikarp::PokemonMagikarp()
{
	this->PokemonType = TypeTypes::Water;
	MoveSet[0] = std::make_unique<PokemonMoveTackle>();
	MoveSet[1] = std::make_unique<PokemonMoveTackle>();
	MoveSet[2] = std::make_unique<PokemonMoveTackle>();
	MoveSet[3] = std::make_unique<PokemonMoveTackle>();
}


PokemonMagikarp::~PokemonMagikarp()
{

}
