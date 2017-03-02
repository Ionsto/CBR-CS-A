#include "PlayerConsole.h"
#include <iostream>
#include "PokemonPikachu.h"


PlayerConsole::PlayerConsole()
{
	MyPokemon[0] = std::make_unique<PokemonPikachu>();
	ActivePokemon = 0;
}


PlayerConsole::~PlayerConsole()
{
}

void PlayerConsole::Update(Player * enemy)
{
	Player::Update(enemy);
}
int PlayerConsole::GetMove(Player * enemy)
{
	if (ActivePokemon == -1)
	{
		std::cout << "Select pokemon" << std::endl;
		int SelectedPokemon = -1;
		while (SelectedPokemon == -1)
		{
			std::cin >> SelectedPokemon;
			if (SelectedPokemon < 0 || SelectedPokemon >= 4)
			{
				SelectedPokemon = -1;
			}
			else if (MyPokemon[SelectedPokemon]->Health == 0)
			{
				SelectedPokemon = -1;
			}
		}
		return SelectedPokemon;
	}
	else
	{
		std::cout << "Select move" << std::endl;
		for (int i = 0; i < 4; ++i)
		{
			std::cout << i << ":" << GetActivePokemon()->MoveSet[i]->Name <<" :"<< GetActivePokemon()->MoveSet[i]->MaxUses - GetActivePokemon()->MoveSet[i]->CurrentUses << std::endl;
		}
		int SelectedMove = -1;
		while (SelectedMove == -1)
		{
			std::cin >> SelectedMove;
		}
		return SelectedMove;
	}
	return 0;
}
