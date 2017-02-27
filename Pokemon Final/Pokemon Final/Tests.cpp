#include "GameInstance.h"
#include "PlayerConsole.h"
#include "PlayerRandom.h"
#include "PlayerCBR.h"
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
bool Playtwo(std::unique_ptr<CBRInstance> * AI0, std::unique_ptr<CBRInstance> * AI1)
{
	float won0 = 0;
	int GamesPlayed = 1000;
	//Example program
	std::unique_ptr<CBRInstance> AI = std::make_unique<CBRInstance>();
	for (int i = 0; i < GamesPlayed; ++i)
	{
		GameInstance * Game = new GameInstance(std::make_unique<PlayerCBR>(std::move(AI)), std::make_unique<PlayerCBR>(std::move(AI)));
		//if (i % 100 == 0 || i-1 % 100 == 0)
		//{
		Game->DisplayCallback = DisplayConsole;
		//}
		while (!Game->Finished) {
			Game->Update();
		}
		if (Game->GetPlayer(0)->Alive)
		{
			++won0;
		}
		AI = std::move(((PlayerCBR*)Game->GetPlayer(0))->AIInstance);
		delete Game;
		std::cout << "Win % for p0:" << (won0*(float)100.0 / (i + 1)) << std::endl;
	}
	return false;
}
//Test program
float PlayOne(CBRWeights * Weights, int gamemax)
{
	float won0 = 0;
	//Example program
	std::unique_ptr<CBRInstance> AI = std::make_unique<CBRInstance>();
	AI->CaseBase->DistanceWeight = CBRWeights(*Weights);
	for (int i = 0; i < gamemax; ++i)
	{
		GameInstance * Game = new GameInstance(std::make_unique<PlayerCBR>(std::move(AI)), std::make_unique<PlayerRandom>());
		//if (i % 100 == 0 || i-1 % 100 == 0)
		//{
		//Game->DisplayCallback = DisplayConsole;
		//}
		while (!Game->Finished) {
			Game->Update();
		}
		if (Game->GetPlayer(0)->Alive)
		{
			++won0;
		}
		AI = std::move(((PlayerCBR*)Game->GetPlayer(0))->AIInstance);
		delete Game;
		//std::cout << "Win % for p0:" << (won0*(float)100.0 / (i + 1)) << std::endl;
		//std::cout << ((float)won0 / (i + 1)) << std::endl;
	}
	//std::cout << ((float)won0 / (gamemax))<< " ";
	return ((float)won0 / (gamemax));
}