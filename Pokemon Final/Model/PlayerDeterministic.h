#pragma once
#include "Player.h"
class PlayerDeterministic :
	public Player
{
public:
	int PlayCount;
	PlayerDeterministic();
	virtual ~PlayerDeterministic() override;
	int GetMove(Player * enemy) override;
};

