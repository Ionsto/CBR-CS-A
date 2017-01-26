#pragma once
#include "Player.h"
#include <Pokemon Final\CBRInstance.h>
class PlayerCBR : public Player{
	std::unique_ptr<CBRInstance> AIInstance;
	PlayerCBR();
	~PlayerCBR();
	//virtual int GetMove(); 
	//Polymorphic function for getting players move 
 	//virtual void Update(); 
};
