#include "Tests.h"

void TestAIInteraction()
{
	std::unique_ptr<CBRInstance> instance = std::make_unique<CBRInstance>();
	if (std::ifstream("BestAI.txt"))
	{
		instance->Load("BestAI.txt");
	}
	else
	{
		std::ifstream stream = std::ifstream("BestWeights.txt");
		if (stream) {
			instance->CaseBase->DistanceWeight.Load(std::move(stream));
		}
		TPlayCBRvsRandomInstance(&instance, 500,true);
		instance->Save("BestAI.txt");
	}
	TPlayCBRvsConsoleInstance(&instance, 6);
	instance.reset();
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
	instance.reset();
	newinstance.reset();
	std::cout << SumDifference << " Difference";
}

void TestPlayOverTime()
{
	std::unique_ptr<CBRInstance> instance = std::make_unique<CBRInstance>();
	CBRWeights Weight = CBRWeights();
	std::ifstream stream = std::ifstream("HandicapedWeights.txt");
	if (stream) {
		Weight.Load(std::move(stream));
		instance->CaseBase->DistanceWeight.CopyWeights(Weight);
	}
	stream.close();
	TPlayCBRvsRandomInstance(&instance, 2000,true);
	instance.reset();
}
void TestPlayDetermanisim()
{
	std::unique_ptr<CBRInstance> instance = std::make_unique<CBRInstance>();
	CBRWeights Weight = CBRWeights();
	std::ifstream stream = std::ifstream("BestWeights.txt");
	if (stream) {
		Weight.Load(std::move(stream));
		instance->CaseBase->DistanceWeight.CopyWeights(Weight);
	}
	stream.close();
	TPlayCBRvsDeterministicInstance(&instance, 1000, true);
	instance.reset();
}
//
void TestKNN()
{
	CBRCaseBaseLinear Casebase = CBRCaseBaseLinear();
	//populate
	std::unique_ptr<CBRCase> NewCase = std::make_unique<CBRCase>();
	NewCase->StartEnviroment = std::make_unique<CBREnviroment>();
	NewCase->StartEnviroment->Owned.Attack = 4;
	Casebase.InsertCase(std::move(NewCase));

	NewCase = std::make_unique<CBRCase>();
	NewCase->StartEnviroment = std::make_unique<CBREnviroment>();
	NewCase->StartEnviroment->Owned.Attack = 2;
	Casebase.InsertCase(std::move(NewCase));

	NewCase = std::make_unique<CBRCase>();
	NewCase->StartEnviroment = std::make_unique<CBREnviroment>();
	NewCase->StartEnviroment->Owned.Attack = 3;
	Casebase.InsertCase(std::move(NewCase));

	NewCase = std::make_unique<CBRCase>();
	NewCase->StartEnviroment = std::make_unique<CBREnviroment>();
	NewCase->StartEnviroment->Owned.Attack = 1;
	Casebase.InsertCase(std::move(NewCase));

	NewCase = std::make_unique<CBRCase>();
	NewCase->StartEnviroment = std::make_unique<CBREnviroment>();
	NewCase->StartEnviroment->Owned.Attack = 0;
	Casebase.InsertCase(std::move(NewCase));
	//Get Knn
	auto CaseArray = Casebase.GetKNN(4, 4, new CBREnviroment());
	for each (auto Case in CaseArray)
	{
		std::cout << Case.Distance <<  " ";
	}
}
//
void TestMergeSort()
{
	std::queue<CBRCaseDistance> DistanceList = std::queue<CBRCaseDistance>();
	std::queue<CBRCaseDistance> DistanceListCopy = std::queue<CBRCaseDistance>();
	for (int i = 0; i < 20;++i)
	{
		CBRCaseDistance newdist = CBRCaseDistance();
		newdist.Distance = rand()%100;
		DistanceList.push(CBRCaseDistance(newdist));
		DistanceListCopy.push(newdist);
	}
	while (DistanceListCopy.size() > 0)
	{
		std::cout << DistanceListCopy.front().Distance << " ";
		DistanceListCopy.pop();
	}
	std::cout << std::endl;
	CBRCaseBaseLinear casebase = CBRCaseBaseLinear();
	DistanceList = casebase.MergeSort(DistanceList);
	while(DistanceList.size() > 0)
	{
		std::cout << DistanceList.front().Distance<<" ";
		DistanceList.pop();
	}
}

void TestCaseAdaption()
{
	std::unique_ptr<CBRInstance> instance = std::make_unique<CBRInstance>();
	CBRWeights Weight = CBRWeights();
	std::ifstream stream = std::ifstream("TransfereWeights.txt");
	if (stream) {
		Weight.Load(std::move(stream));
		instance->CaseBase->DistanceWeight.CopyWeights(Weight);
	}
	stream.close();
	std::ofstream LearnElectric = std::ofstream("LearnElectric.txt");
	std::ofstream LearnWater = std::ofstream("LearnWater.txt");

	{
		int GameCount = 400;
		float won0 = 0;
		float GameCounter = 0;
		for (int i = 0; i < GameCount; ++i)
		{
			++GameCounter;
			GameInstance * Game = new GameInstance(std::make_unique<PlayerCBR>(std::move(instance)), std::make_unique<PlayerRandom>());
			if (i == GameCount / 2)
			{
				GameCounter = 1;
				won0 = 0;
			}
			if (i >= GameCount / 2) {
				Game->GetPlayer(0)->MyPokemon[0].reset();
				Game->GetPlayer(0)->MyPokemon[0] = std::make_unique<PokemonMareep>();
			}
			//if (i % 100 == 0 || i-1 % 100 == 0)
			//{
			//Game->DisplayCallback = DisplayConsole;
			//}
			for (int g = 0; g < 6 && !Game->Finished; ++g) {
				Game->Update();
			}
			//if (Game->GetPlayer(0)->TeamHealth > Game->GetPlayer(1)->TeamHealth)
			if (Game->GetPlayer(0)->Alive && Game->Finished)
			{
				++won0;
			}
			instance = std::move(((PlayerCBR*)Game->GetPlayer(0))->AIInstance);
			delete Game;
			LearnElectric << ((float)won0 / (GameCounter)) << std::endl;
		}
	} 
	{
		int GameCount = 400;
		float won0 = 0;
		float GameCounter = 0;
		for (int i = 0; i < GameCount; ++i)
		{
			GameCounter++;
			GameInstance * Game = new GameInstance(std::make_unique<PlayerCBR>(std::move(instance)), std::make_unique<PlayerRandom>());
			if (i == GameCount / 2)
			{
				GameCounter = 1;
				won0 = 0;
			}
			if (i < GameCount / 2)
			{
				Game->GetPlayer(0)->MyPokemon[0].reset();
				Game->GetPlayer(0)->MyPokemon[0] = std::make_unique<PokemonMagikarp>();
			}
			else
			{
				Game->GetPlayer(0)->MyPokemon[0].reset();
				Game->GetPlayer(0)->MyPokemon[0] = std::make_unique<PokemonMareep>();
			}
			//if (i % 100 == 0 || i-1 % 100 == 0)
			//{
			//Game->DisplayCallback = DisplayConsole;
			//}
			for (int g = 0; g < 6 && !Game->Finished; ++g) {
				Game->Update();
			}
			//if (Game->GetPlayer(0)->TeamHealth > Game->GetPlayer(1)->TeamHealth)
			if (Game->GetPlayer(0)->Alive && Game->Finished)
			{
				++won0;
			}
			instance = std::move(((PlayerCBR*)Game->GetPlayer(0))->AIInstance);
			delete Game;
			LearnWater << ((float)won0 / (GameCounter)) << std::endl;
		}
	}
	instance.reset();
}

static void TDisplayConsole(GameInstance * gi, std::unique_ptr<Player> * Players, GameInstance::MovePairs moves)
{
	std::cout << "Round Played" << std::endl;
	if (Players[0]->Alive) {
		std::cout << "Player 0: " << Players[0]->GetActivePokemon()->PokemonType << " Health:" << Players[0]->GetActivePokemon()->Health << ": " << Players[0]->GetActivePokemon()->MoveSet[moves.A]->Name << std::endl;
	}
	else
	{
		std::cout << "Player 0 is out" << std::endl;
	}
	if (Players[1]->Alive) {
		std::cout << "Player 1: " << Players[1]->GetActivePokemon()->PokemonType << " Health:" << Players[1]->GetActivePokemon()->Health << ": " << Players[1]->GetActivePokemon()->MoveSet[moves.B]->Name << std::endl;
	}
	else
	{
		std::cout << "Player 1 is out" << std::endl;
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
float TPlayCBRvsRandomInstance(std::unique_ptr<CBRInstance> * AI, int gamemax, bool DisplayRoundP)
{
	float won0 = 0;
	//Example program
	for (int i = 0; i < gamemax; ++i)
	{
		GameInstance * Game = new GameInstance(std::make_unique<PlayerCBR>(std::move((*AI))), std::make_unique<PlayerRandom>());
		//if (i % 100 == 0 || i-1 % 100 == 0)
		//{
		//Game->DisplayCallback = DisplayConsole;
		//}
		for (int g = 0; g < 6 && !Game->Finished; ++g) {
			Game->Update();
		}
		//if (Game->GetPlayer(0)->TeamHealth > Game->GetPlayer(1)->TeamHealth)
		if(Game->GetPlayer(0)->Alive && Game->Finished)
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
	std::cout << ((float)won0 / (gamemax))<< " ";
	return ((float)won0 / (gamemax));
}
float TPlayCBRvsDeterministicInstance(std::unique_ptr<CBRInstance> * AI, int gamemax, bool DisplayRoundP)
{
	float won0 = 0;
	//Example program
	for (int i = 0; i < gamemax; ++i)
	{//std::make_unique<PlayerCBR>(std::move(*AI))
		GameInstance * Game = new GameInstance(std::make_unique<PlayerCBR>(std::move(*AI)),std::make_unique<PlayerDeterministic>());
		//if (i % 100 == 0 || i-1 % 100 == 0)
		//{
		//Game->DisplayCallback = TDisplayConsole;
		//}
		for (int g = 0; g < 6 && !Game->Finished; ++g) {
			Game->Update();
		}
		if (Game->GetPlayer(0)->TeamHealth > Game->GetPlayer(1)->TeamHealth)
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

template<class PlayerClass>
float TPlayCBRvsPlayer(std::unique_ptr<CBRInstance> * AI, PlayerClass * PlayerCopy, int gamemax, bool DisplayRoundP)
{
	float won0 = 0;
	//Example program
	for (int i = 0; i < gamemax; ++i)
	{
		GameInstance * Game = new GameInstance(std::make_unique<PlayerCBR>(std::move((*AI))), std::make_unique<PlayerClass>(*PlayerCopy));
		//if (i % 100 == 0 || i-1 % 100 == 0)
		//{
		//Game->DisplayCallback = DisplayConsole;
		//}
		for (int g = 0; g < 6 && !Game->Finished; ++g) {
			Game->Update();
		}
		//if (Game->GetPlayer(0)->TeamHealth > Game->GetPlayer(1)->TeamHealth)
		if (Game->GetPlayer(0)->Alive && Game->Finished)
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
	std::cout << ((float)won0 / (gamemax)) << " ";
	return ((float)won0 / (gamemax));
}