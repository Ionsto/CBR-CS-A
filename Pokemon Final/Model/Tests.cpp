#include "Tests.h"

void TestAIInteraction()
{
	std::unique_ptr<CBRInstance> instance = std::make_unique<CBRInstance>();
	CBRWeights Weight = CBRWeights();
	std::ifstream stream = std::ifstream("weights.txt");
	if (stream) {
		Weight.Load(std::move(stream));
		instance->CaseBase->DistanceWeight.CopyWeights(Weight);
	}
	TPlayCBRvsRandomInstance(&instance, 100);
	TPlayCBRvsConsoleInstance(&instance, 1);
	instance.release();
}

void TestCaseSaveLoad()
{
	std::unique_ptr<CBRInstance> instance = std::make_unique<CBRInstance>();
	TPlayCBRvsRandomInstance(&instance,20);
	instance->Save("TestSave.txt");
	std::unique_ptr<CBRInstance> newinstance = std::make_unique<CBRInstance>();
	newinstance->Load("TestSave.txt");
	//Check to see if the two are identical
	float SumDifference = 0;
	for (int i = 0; i < instance->CaseBase->GetCaseCount(); ++i)
	{
		SumDifference += instance->CaseBase->GetDistance(instance->CaseBase->GetCaseView(i)->StartEnviroment.get(), newinstance->CaseBase->GetCaseView(i)->StartEnviroment.get());
		SumDifference += instance->CaseBase->GetDistance(instance->CaseBase->GetCaseView(i)->EndEnviroment.get(), newinstance->CaseBase->GetCaseView(i)->EndEnviroment.get());
		SumDifference += instance->CaseBase->GetCaseView(i)->Move - newinstance->CaseBase->GetCaseView(i)->Move;
		SumDifference += instance->CaseBase->GetCaseView(i)->Utility - newinstance->CaseBase->GetCaseView(i)->Utility;
	}
	instance.release();
	newinstance.release();
	std::cout << SumDifference << " Difference";
}

void TestPlayOverTime()
{
	std::unique_ptr<CBRInstance> instance = std::make_unique<CBRInstance>();
	CBRWeights Weight = CBRWeights();
	std::ifstream stream = std::ifstream("weights.txt");
	if (stream) {
		Weight.Load(std::move(stream));
		instance->CaseBase->DistanceWeight.CopyWeights(Weight);
	}
	TPlayCBRvsRandomInstance(&instance, 5000,true);
	instance.release();
}

static void TDisplayConsole(GameInstance * gi, std::unique_ptr<Player> * Players, GameInstance::MovePairs moves)
{
	std::cout << "Round Played" << std::endl;
	if (Players[0]->Alive) {
		std::cout << "Player 0: " << Players[0]->GetActivePokemon()->PokemonType << " Health:" << Players[0]->GetActivePokemon()->Health << ": " << Players[0]->GetActivePokemon()->MoveSet[moves.A]->Name << std::endl;
	}
	else
	{
		std::cout << "Player 0 is out - attempted " << Players[0]->GetActivePokemon()->MoveSet[moves.A]->Name << std::endl;
	}
	if (Players[1]->Alive) {
		std::cout << "Player 1: " << Players[1]->GetActivePokemon()->PokemonType << " Health:" << Players[1]->GetActivePokemon()->Health << ": " << Players[1]->GetActivePokemon()->MoveSet[moves.B]->Name << std::endl;
	}
	else
	{
		std::cout << "Player 1 is out - attempted " << Players[1]->GetActivePokemon()->MoveSet[moves.B]->Name << std::endl;
	}
	std::cout << "---------------------------------------" << std::endl;
}
//Test program
float TPlayOneWeight(CBRWeights * Weights, int gamemax)
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
float TPlayCBRvsRandomInstance(std::unique_ptr<CBRInstance> * AI, int gamemax,bool DisplayRoundP)
{
	float won0 = 0;
	//Example program
	for (int i = 0; i < gamemax; ++i)
	{
		GameInstance * Game = new GameInstance(std::make_unique<PlayerCBR>(std::move(*AI)), std::make_unique<PlayerRandom>());
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
		*AI = std::move(((PlayerCBR*)Game->GetPlayer(0))->AIInstance);
		delete Game;
		//std::cout << "Win % for p0:" << (won0*(float)100.0 / (i + 1)) << std::endl;
		if (DisplayRoundP) 
		{
			std::cout << ((float)won0 / (i + 1)) << std::endl;
		}
	}
	//std::cout << ((float)won0 / (gamemax))<< " ";
	return ((float)won0 / (gamemax));
}
float TPlayCBRvsConsoleInstance(std::unique_ptr<CBRInstance> * AI, int gamemax)
{
	float won0 = 0;
	//Example program
	for (int i = 0; i < gamemax; ++i)
	{
		GameInstance * Game = new GameInstance(std::make_unique<PlayerCBR>(std::move(*AI)), std::make_unique<PlayerConsole>());
		Game->DisplayCallback = TDisplayConsole;
		while (!Game->Finished) {
			Game->Update();
		}
		if (Game->GetPlayer(0)->Alive)
		{
			++won0;
		}
		*AI = std::move(((PlayerCBR*)Game->GetPlayer(0))->AIInstance);
		delete Game;
		//std::cout << "Win % for p0:" << (won0*(float)100.0 / (i + 1)) << std::endl;
		//std::cout << ((float)won0 / (i + 1)) << std::endl;
	}
	//std::cout << ((float)won0 / (gamemax))<< " ";
	return ((float)won0 / (gamemax));
}