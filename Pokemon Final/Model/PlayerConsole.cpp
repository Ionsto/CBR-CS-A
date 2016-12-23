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

void PlayerConsole::Update()
{
	if (GetActivePokemon()->Health == 0)
	{
		ActivePokemon = -1;
	}
}
int PlayerConsole::GetMove()
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
			std::cout << i << ":" << GetActivePokemon()->MoveSet[i]->Name << std::endl;
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
