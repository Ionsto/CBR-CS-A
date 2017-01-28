#pragma once
#include "Player.h"
class PlayerConsole :
	public Player
{
public:
	PlayerConsole();
	~PlayerConsole();
	virtual int GetMove(Player * enemy) override;
	virtual void Update(Player * enemy) override;
};

