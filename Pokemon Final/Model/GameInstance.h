#pragma once
#include "Player.h"
class GameInstance
{
public:
	Player Players[2];
	GameInstance();
	~GameInstance();
	void Update();
	void GetPlayerMoves();
	float CalculateDamage();
};

