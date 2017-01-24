#include "GameInstance.h"
#include "PlayerConsole.h"
#include <iostream>

static void DisplayConsole(GameInstance * gi, std::unique_ptr<Player> * Players)
{
	std::cout << "Round Played" << std::endl;
	if (Players[0]->ActivePokemon != -1) {
		std::cout << "Player 0:" << Players[0]->GetActivePokemon()->PokemonType << " Health:" << Players[0]->GetActivePokemon()->Health << std::endl;
	}
	else
	{
		std::cout << "Player 0 is out" << std::endl;
	}
	if (Players[1]->ActivePokemon != -1) {
		std::cout << "Player 1:" << Players[1]->GetActivePokemon()->PokemonType << " Health:" << Players[1]->GetActivePokemon()->Health << std::endl;
	}
	else
	{
		std::cout << "Player 1 is out" << std::endl;
	}
	std::cout << "---------------------------------------" << std::endl;
}
int main(int argc, char **args)
{
	//Example program
	GameInstance * Game = new GameInstance(std::make_unique<PlayerConsole>(), std::make_unique<PlayerConsole>());
	Game->DisplayCallback = DisplayConsole;
	while (!Game->Finished) {
		Game->Update();
	}
	return 0;
}