#pragma once
#include "Player.h"
class PlayerConsole :
	public Player
{
public:
	PlayerConsole();
	~PlayerConsole();
	virtual int GetMove(GameInstance * gm) override;
	virtual void Update(GameInstance * gm) override;
};

