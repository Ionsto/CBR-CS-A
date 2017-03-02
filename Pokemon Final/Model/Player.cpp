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
		MyPokemon[i].reset();
	}
}

int Player::GetMove(Player * enemy)
{
	return 0;
}
void Player::Update(Player * enemy)
{
	TeamHealth = 0;
	for (int i = 0; i < 4; ++i)
	{
		TeamHealth += MyPokemon[i]->Health;
		if (MyPokemon[i]->Health < 0)
		{
			MyPokemon[i]->Health = 0;
		}
	}
	if (TeamHealth <= 0)
	{
		Alive = false;
		ActivePokemon = -1;
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