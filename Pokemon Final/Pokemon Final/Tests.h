#pragma once
#include ""
#include "PlayerConsole.h"
#include "PlayerRandom.h"
#include "PlayerCBR.h"
//This test checks whether the save load mechanics work
void TestCaseSaveLoad();

//
static void DisplayConsole(GameInstance * gi, std::unique_ptr<Player> * Players, GameInstance::MovePairs moves);