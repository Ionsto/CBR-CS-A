#include "PlayerConsole.h"
#include <iostream>


PlayerConsole::PlayerConsole()
{
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
	}
	return 0;
}
