#pragma once
#include "GameInstance.h"
#include "PlayerConsole.h"
#include "PlayerRandom.h"
#include "PlayerCBR.h"
#include "PlayerDeterministic.h"
#include "Pokemon Final\CBRCaseBaseLinear.h"
#include "Pokemon Final\CBRCase.h"
#include "Pokemon Final\CBREnviroment.h"
#include <iostream>
//
void TestAIInteraction();
//This test checks whether the save load mechanics work
void TestCaseSaveLoad();
//This plays a single AI against a random oponent 2000 times, loading from preset weights
void TestPlayOverTime();
//This plays a single AI against a random oponent 2000 times, loading from preset weights
void TestPlayDetermanisim();
//
void TestMergeSort();
//
void TestKNN();

static void TDisplayConsole(GameInstance * gi, std::unique_ptr<Player> * Players, GameInstance::MovePairs moves);
float TPlayCBRvsRandomInstance(std::unique_ptr<CBRInstance> * AI, int gamemax, bool DisplayRoundP = false);
float TPlayCBRvsDeterministicInstance(std::unique_ptr<CBRInstance> * AI, int gamemax, bool DisplayRoundP = false);
float TPlayCBRvsConsoleInstance(std::unique_ptr<CBRInstance> * AI, int gamemax);