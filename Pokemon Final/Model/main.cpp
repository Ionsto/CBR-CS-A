#include "GameInstance.h"
#include "PlayerConsole.h"
#include "PlayerRandom.h"
#include "PlayerCBR.h"
#include <iostream>
#include "Tests.h"

static void DisplayConsole(GameInstance * gi, std::unique_ptr<Player> * Players, GameInstance::MovePairs moves)
{
	std::cout << "Round Played" << std::endl;
	if (Players[0]->Alive) {
		std::cout << "Player 0:" << Players[0]->GetActivePokemon()->PokemonType << " Health:" << Players[0]->GetActivePokemon()->Health << ": " << Players[0]->GetActivePokemon()->MoveSet[moves.A]->Name <<"("<<(Players[0]->GetActivePokemon()->MoveSet[moves.A]->MaxUses - Players[0]->GetActivePokemon()->MoveSet[moves.A]->CurrentUses)<<")" << std::endl;
	}
	else
	{
		std::cout << "Player 0 is out" << std::endl;
	}
	if (Players[1]->Alive) {
		std::cout << "Player 1:" << Players[1]->GetActivePokemon()->PokemonType << " Health:" << Players[1]->GetActivePokemon()->Health << ": " << Players[1]->GetActivePokemon()->MoveSet[moves.B]->Name << "(" << (Players[1]->GetActivePokemon()->MoveSet[moves.B]->MaxUses - Players[1]->GetActivePokemon()->MoveSet[moves.B]->CurrentUses) << ")" << std::endl;
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
float PlayOne(CBRWeights * Weights, int gamemax,bool Display = false)
{
	float won0 = 0;
	//Example program
	std::unique_ptr<CBRInstance> AI = std::make_unique<CBRInstance>();
	AI->CaseBase->DistanceWeight = CBRWeights(*Weights);
	for (int i = 0; i < gamemax; ++i)
	{
		GameInstance * Game = new GameInstance(std::make_unique<PlayerCBR>(std::move(AI)), std::make_unique<PlayerRandom>());
		////TRANFER
		if (i < gamemax / 2)
		{
			Game->GetPlayer(0)->MyPokemon[0].reset();
			Game->GetPlayer(0)->MyPokemon[0] = std::make_unique<PokemonMagikarp>();
		}
		else
		{
			Game->GetPlayer(0)->MyPokemon[0].reset();
			Game->GetPlayer(0)->MyPokemon[0] = std::make_unique<PokemonMareep>();
		}
		///
		if (Display)
		{
			Game->DisplayCallback = DisplayConsole;
		}
		for (int g = 0; g < 10 && !Game->Finished; ++g) {
			Game->Update();
		}
		//if (Game->GetPlayer(0)->TeamHealth > Game->GetPlayer(1)->TeamHealth)
		if (Game->GetPlayer(0)->Alive && Game->Finished)
		{
			++won0;
		}
		AI = std::move(((PlayerCBR*)Game->GetPlayer(0))->AIInstance);
		delete Game;
		//std::cout << "Win % for p0:" << (won0*(float)100.0 / (i + 1)) << std::endl;
		//std::cout << ((float)won0 / (i + 1)) << std::endl;
	}
	AI.reset();
	//std::cout << ((float)won0 / (gamemax))<< " ";
	return ((float)won0 / (gamemax));
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
			//Game->DisplayCallback = DisplayConsole;
		}
		//for (int g = 0; g < 7 && !Game->Finished;++g) {
		while(!Game->Finished){
			Game->Update();
		}
		if (Game->GetPlayer(0)->Alive)// TeamHealth > Game->GetPlayer(1)->TeamHealth)
		{
			++win0;
		}
		else
		{
			++win1;
		}		
		if (i == PlayGames-1)
		{
			//std::cout << "Win % for p0:" << (win0*(float)100.0 / (win0 + win1)) << std::endl;
		}
		//std::cout << ((float)win0 / (win0 + win1)) << std::endl;
		AI0 = std::move(((PlayerCBR*)Game->GetPlayer(0))->AIInstance);
		AI1 = std::move(((PlayerCBR*)Game->GetPlayer(1))->AIInstance);
		delete Game;
	}
	AI0.reset();
	AI1.reset();
	if (win0 > win1)
	{
		return true;
	}
	return false;
};
void WeightingRoundRobin(float Target,std::string SaveLocation, float Delta = 1)
{
	std::ofstream LearningTrendFile;
	LearningTrendFile.open(SaveLocation+"LearningTrend.txt", std::ios_base::app);
	int WeightCount = 20;
	int RoundCount = 500;
	std::deque<std::unique_ptr<CBRWeights>> Weights = std::deque<std::unique_ptr<CBRWeights>>();
	for (int i = 0; i < WeightCount; ++i)
	{
		std::unique_ptr<CBRWeights> NewWeight = std::make_unique<CBRWeights>();
		NewWeight->RandomiseWeights(Delta);
		Weights.push_back(std::move(NewWeight));
	}
	std::ifstream stream = std::ifstream(SaveLocation+"Weights.txt");
	if (stream) {
		Weights[0]->Load(std::move(stream));
		for (int i = 1; i < WeightCount; ++i)
		{
			Weights[i]->CopyWeights(*Weights[0].get());
			Weights[i]->RandomiseWeights(Delta);
		}
	}
	stream.close();
	for (int rounds = 0; rounds >= 0; ++rounds)
	{
		float SumWinrate = 0;
		std::cout << "---ROUND" << rounds << std::endl;
		std::unique_ptr<CBRWeights> BestWeight = std::move(Weights.front());
		const int GameCount = 400;
		float WinRate = PlayOne((BestWeight.get()), GameCount);
		SumWinrate += WinRate;
		Weights.pop_front();
		for (int i = 1; i < WeightCount; ++i)
		{
			std::unique_ptr<CBRWeights> CurrentWeight = std::move(Weights.front());
			Weights.pop_front();
			float Rate = PlayOne((CurrentWeight.get()), GameCount);
			SumWinrate += Rate;
			std::cout << "---WEIGHT" << i << " " << Rate << std::endl;
			if (abs(Rate - Target) < abs(WinRate - Target))
			{
				BestWeight.reset();
				BestWeight = std::move(CurrentWeight);
				WinRate = Rate;
			}
			else
			{
				CurrentWeight.reset();
			}
		}
		PlayOne(BestWeight.get(), 1, true);
		std::cout << "---BEST---" << WinRate << std::endl;
		for (int i = 1; i < WeightCount; ++i) {
			std::unique_ptr<CBRWeights> Copy = std::make_unique<CBRWeights>(*BestWeight.get());
			Copy->RandomiseWeights(Delta);
			Weights.push_back(std::move(Copy));
		}
		LearningTrendFile << (SumWinrate/WeightCount) << std::endl;
		std::ofstream streamout = std::ofstream(SaveLocation+"Weights.txt");
		BestWeight->Save(std::move(streamout));
		streamout.flush();
		streamout.close();
		Weights.push_back(std::move(BestWeight));
	}
}
int main(int argc, char **args)
{
	/*float Delta = 1;
	std::unique_ptr<CBRWeights> Weight0 = std::make_unique<CBRWeights>();
	std::unique_ptr<CBRWeights> Weight1 = std::make_unique<CBRWeights>();
	std::ifstream stream = std::ifstream("Weights.txt");
	if (stream) {
		Weight0->Load(std::move(stream));
		Weight1->CopyWeights(*Weight0.get());
	}
	Weight0->RandomiseWeights(Delta);
	std::cout<<PlayOne(Weight0.get(), 1000);*/
	//PlayWeights(Weight0.get(),Weight1.get(),200);
	//WeightingRoundRobin();
	//TestAIInteraction();
	//TestCaseSaveLoad();
	//TestPlayOverTime();
	//TestPlayDetermanisim();
	//TPlayCBRvsDeterministicInstance(NULL, 1);
	WeightingRoundRobin(1, "Transfere");
	//TestKNN();
	//TestMergeSort();
	TestCaseAdaption();
	int i = 0;
	std::cin >> i;
	return 0;
}