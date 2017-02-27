#pragma once
#include "Player.h"
class PlayerDeterministic :
	public Player
{
public:
	int PlayCount;
	PlayerDeterministic();
	~PlayerDeterministic();
	int GetMove(Player * enemy) override;
};

