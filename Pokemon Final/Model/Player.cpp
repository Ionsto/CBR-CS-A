#include "Player.h"



Player::Player()
{
	Alive = true;
	ActivePokemon = -1;
	for (int i = 0; i < 4; ++i)
	{
		MyPokemon[i] = std::make_unique<PokemonBase>();
	}
}


Player::~Player()
{
}

int Player::GetMove()
{
	return 0;
}
void Player::Update()
{
	int TeamHealth = 0;
	for (int i = 0; i < 4; ++i)
	{
		TeamHealth += MyPokemon[i]->Health;
	}
	if (TeamHealth == 0)
	{
		Alive = false;
	}
}

PokemonBase * Player::GetActivePokemon()
{
	if (ActivePokemon >= 0 && ActivePokemon < 4)
	{
		return MyPokemon[ActivePokemon].get();
	}
	return NULL;
}