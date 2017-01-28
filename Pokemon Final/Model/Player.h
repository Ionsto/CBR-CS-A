#pragma once
#include <memory>
#include "PokemonBase.h"
class GameInstance;
class Player
{
public:
	bool Alive;
	int ActivePokemon;
	//This is the list of actors(pokemon) availible
	std::unique_ptr<PokemonBase> MyPokemon[4];
	Player();
	~Player();
	//Polymorphic function for getting players move
	virtual int GetMove(Player * enemy);
	//Polymorphic function for getting players move
	virtual void Update(Player * enemy);
	//Returns active pokemon
	PokemonBase * GetActivePokemon();
};

