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
void PlayOne()
{
	float won0 = 0;
	int GamesPlayed = 1000;
	//Example program
	std::unique_ptr<CBRInstance> AI = std::make_unique<CBRInstance>();
	for (int i = 0; i < GamesPlayed; ++i)
	{
		GameInstance * Game = new GameInstance(std::make_unique<PlayerCBR>(std::move(AI)), std::make_unique<PlayerRandom>());
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
		if (i == 900)
		{
			int kys = 0;
		}
		std::cout << "Win % for p0:" << (won0*(float)100.0 / (i + 1)) << std::endl;
	}
	int i = 0;
	std::cin >> i;
}
bool PlayWeights(CBRWeights * W0,CBRWeights * W1,int Games = 50)
{
	std::unique_ptr<CBRInstance> AI0 = std::make_unique<CBRInstance>();
	std::unique_ptr<CBRInstance> AI1 = std::make_unique<CBRInstance>();
	AI0->CaseBase->DistanceWeight = CBRWeights(*W0);
	AI1->CaseBase->DistanceWeight = CBRWeights(*W1);
	int win0 = 0;
	int win1 = 0;
	int PlayGames = Games;
	for (int i = 0; i < PlayGames; ++i)
	{
		GameInstance * Game = new GameInstance(std::make_unique<PlayerCBR>(std::move(AI0)), std::make_unique<PlayerCBR>(std::move(AI1)));
		std::cout << i<<std::endl;
		if (fmod((double)i,5.0) == 0)
		{
			Game->DisplayCallback = DisplayConsole;
		}
		for (int g = 0; g < 7 && !Game->Finished;++g) {
			Game->Update();
		}
		if (Game->GetPlayer(0)->TeamHealth > Game->GetPlayer(1)->TeamHealth)
		{
			++win0;
		}
		else
		{
			++win1;
		}		
		if (i == PlayGames-1)
		{
			std::cout << "Win % for p0:" << (win0*(float)100.0 / (win0 + win1)) << std::endl;
		}
		AI0 = std::move(((PlayerCBR*)Game->GetPlayer(0))->AIInstance);
		AI1 = std::move(((PlayerCBR*)Game->GetPlayer(1))->AIInstance);
		delete Game;
	}
	AI0.release();
	AI1.release();
	if (win0 > win1)
	{
		return true;
	}
	return false;
};
void WeightingRoundRobin()
{
	int WeightCount = 10;
	int RoundCount = 50;
	float Delta = 20;
	std::deque<std::unique_ptr<CBRWeights>> Weights = std::deque<std::unique_ptr<CBRWeights>>();
	for (int i = 0; i < WeightCount; ++i)
	{
		std::unique_ptr<CBRWeights> NewWeight = std::make_unique<CBRWeights>();
		NewWeight->RandomiseWeights(Delta);
		Weights.push_back(std::move(NewWeight));
	}
	std::ifstream stream = std::ifstream("weights.txt");
	if (stream) {
		Weights[0]->Load(std::move(stream));
		for (int i = 1; i < WeightCount; ++i)
		{
			Weights[i]->CopyWeights(*Weights[0].get());
			Weights[i]->RandomiseWeights(Delta);
		}
	}
	stream.close();
	for (int rounds = 0; rounds < RoundCount; ++rounds)
	{
		std::cout << "---ROUND" << rounds << std::endl;
		for (int i = 0; i < WeightCount/2; ++i)
		{
			std::cout << "---WEIGHT" << i*2 << std::endl;
			std::unique_ptr<CBRWeights> P0 = std::move(Weights.front());
			Weights.pop_front();
			std::unique_ptr<CBRWeights> P1 = std::move(Weights.front());
			Weights.pop_front();
			if (PlayWeights(P0.get(), P1.get()))
			{

				std::unique_ptr<CBRWeights> P0Copy = std::make_unique<CBRWeights>(*P0.get());
				P0->RandomiseWeights(Delta);
				P0Copy->RandomiseWeights(Delta);
				Weights.push_back(std::move(P0));
				Weights.push_back(std::move(P0Copy));
			}
			else
			{
				std::unique_ptr<CBRWeights> P1Copy = std::make_unique<CBRWeights>(*P1.get());
				P1->RandomiseWeights(Delta);
				P1Copy->RandomiseWeights(Delta);
				Weights.push_back(std::move(P1));
				Weights.push_back(std::move(P1Copy));
			}
		}
		std::random_shuffle(Weights.begin(), Weights.end());
	}
	std::ofstream streamout = std::ofstream("weights.txt");
	Weights[0]->Save(std::move(streamout));
	streamout.flush();
	streamout.close();
}
int main(int argc, char **args)
{
	float Delta = 1;
	std::unique_ptr<CBRWeights> Weight0 = std::make_unique<CBRWeights>();
	std::unique_ptr<CBRWeights> Weight1 = std::make_unique<CBRWeights>();
	std::ifstream stream = std::ifstream("weights.txt");
	if (stream) {
		Weight0->Load(std::move(stream));
		Weight1->CopyWeights(*Weight0.get());
	}
	Weight0->RandomiseWeights(Delta);
	PlayWeights(Weight0.get(),Weight1.get(),200);
	int i = 0;
	std::cin >> i;
	return 0;
}