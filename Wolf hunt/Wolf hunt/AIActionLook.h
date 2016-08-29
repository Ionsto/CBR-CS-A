#pragma once
#include "AIAction.h"
class AIActionLook :
	public AIAction
{
public:
	Vector ShotLocation;
	AIActionLook(EntityAI * owner,Vector ShotLoc);
	~AIActionLook();
	void Execute() override;
	AIAction * CopySelf(EntityAI * newowner) override;
	void Mutate(float Factor) override;
	std::string Description() override;
};

