#pragma once
#include "EntityWolf.h"
//This class gets loaded into the Execute stack
class AIAction
{
public:
	EntityWolf * Owner;
	AIAction(EntityWolf * owner);
	~AIAction();
	virtual void Execute();
	void RemoveSelf();
	virtual AIAction * CopySelf(EntityWolf * newowner);
	virtual void Mutate(float Factor);
	virtual std::string Description();
};

