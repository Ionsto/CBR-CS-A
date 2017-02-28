#pragma once
#include "Player.h"
class PlayerRandom :
	public Player
{
public:
	PlayerRandom();
	virtual ~PlayerRandom() override;
	int GetMove(Player * enemy) override;
};

