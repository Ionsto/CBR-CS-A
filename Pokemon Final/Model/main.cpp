#include "GameInstance.h"
#include "PlayerConsole.h"
#include "PlayerRandom.h"
#include <iostream>


static void DisplayConsole(GameInstance * gi, std::unique_ptr<Player> * Players, GameInstance::MovePairs moves)
{
	std::cout << "Round Played" << std::endl;
	if (Players[0]->Alive) {
		std::cout << "Player 0:" << Players[0]->GetActivePokemon()->PokemonType << " Health:" << Players[0]->GetActivePokemon()->Health << ": " << Players[0]->GetActivePokemon()->MoveSet[moves.A]->Name << std::endl;
	}
	else
	{
		std::cout << "Player 0 is out" << std::endl;
	}
	if (Players[1]->Alive) {
		std::cout << "Player 1:" << Players[1]->GetActivePokemon()->PokemonType << " Health:" << Players[1]->GetActivePokemon()->Health << ": " << Players[0]->GetActivePokemon()->MoveSet[moves.B]->Name << std::endl;
	}
	else
	{
		std::cout << "Player 1 is out" << std::endl;
	}
	std::cout << "---------------------------------------" << std::endl;
}
int main(int argc, char **args)
{
	float won0 = 0;
	int GamesPlayed = 100000;
	//Example program
	for (int i = 0;i < GamesPlayed;++i)
	{
		GameInstance * Game = new GameInstance(std::make_unique<PlayerRandom>(), std::make_unique<PlayerRandom>());
		//Game->DisplayCallback = DisplayConsole;
		while (!Game->Finished) {
			Game->Update();
		}
		if (Game->GetPlayer(0)->Alive)
		{
			++won0;
		}
		delete Game;
	}
	std::cout << "Win % for p0:" << (won0*100 / (GamesPlayed)) << std::endl;
	int i = 0;
	std::cin >> i;
	return 0;
}