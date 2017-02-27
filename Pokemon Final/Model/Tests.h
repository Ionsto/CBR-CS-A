#pragma once
#include "GameInstance.h"
#include "PlayerConsole.h"
#include "PlayerRandom.h"
#include "PlayerCBR.h"
#include <iostream>
//
void TestAIInteraction();
//This test checks whether the save load mechanics work
void TestCaseSaveLoad();
//
void TestPlayOverTime();
static void TDisplayConsole(GameInstance * gi, std::unique_ptr<Player> * Players, GameInstance::MovePairs moves);
float TPlayCBRvsRandomInstance(std::unique_ptr<CBRInstance> * AI, int gamemax,bool DisplayRoundP = false);
float TPlayCBRvsConsoleInstance(std::unique_ptr<CBRInstance> * AI, int gamemax);