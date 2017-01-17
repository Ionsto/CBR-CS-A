#pragma once
class PlayerCBR : public Player{
	std::unique_ptr<CBRInstance> AIInstance;
	virtual int GetMove(); 
	//Polymorphic function for getting players move 
 	virtual void Update(); 
};
