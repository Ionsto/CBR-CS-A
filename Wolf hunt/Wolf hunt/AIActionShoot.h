#pragma once
#include "AIAction.h"
class AIActionShoot :
	public AIAction
{
public:
	int Weapon;
	int ShotCount;
	int ShotCounter;
	AIActionShoot(EntityAI * owner, int Weapon, int Count);
	~AIActionShoot();
	void Execute() override;
	AIAction * CopySelf(EntityAI * newowner) override;
	void Mutate(float Factor) override;
	std::string Description() override;
};

