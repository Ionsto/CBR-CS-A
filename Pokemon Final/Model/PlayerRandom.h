#pragma once
#include "Player.h"
class PlayerRandom :
	public Player
{
public:
	PlayerRandom();
	~PlayerRandom();
	int GetMove(GameInstance * gm) override;
};

