#include "Player.h"
#include "GameInstance.h"


Player::Player()
{
	Alive = true;
	ActivePokemon = -1;
	for (int i = 0; i < 4; ++i)
	{
		MyPokemon[i] = std::make_unique<PokemonBase>();
		MyPokemon[i]->Health = 0;
	}
}


Player::~Player()
{
	for (int i = 0; i < 4; ++i)
	{
		MyPokemon[i].release();
	}
}

int Player::GetMove(GameInstance * gm)
{
	return 0;
}
void Player::Update(GameInstance * gm)
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