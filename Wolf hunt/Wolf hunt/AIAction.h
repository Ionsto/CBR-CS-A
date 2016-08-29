#pragma once
#include "EntityAI.h"
//This class gets loaded into the Execute stack
class AIAction
{
public:
	EntityAI * Owner;
	AIAction(EntityAI * owner);
	~AIAction();
	virtual void Execute();
	void RemoveSelf();
	virtual AIAction * CopySelf(EntityAI * newowner);
	virtual void Mutate(float Factor);
	virtual std::string Description();
};

