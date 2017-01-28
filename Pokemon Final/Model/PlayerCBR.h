#pragma once
#include "Player.h"
#include <Pokemon Final\CBRInstance.h>
class PlayerCBR : public Player{
public:
	std::unique_ptr<CBRInstance> AIInstance;
	PlayerCBR();
	~PlayerCBR();
	int GetMove(Player * enemy) override;
	//Polymorphic function for getting players move 
	void Update(Player * enemy) override;
	void PopulateEnviroment(CBREnviroment * env, Player * enemy);
};
