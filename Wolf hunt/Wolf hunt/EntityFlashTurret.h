#pragma once
#include "EntityAI.h"
class EntityFlashTurret :
	public EntityAI
{
public:
	EntityFlashTurret(World * world,Vector pos = Vector());
	~EntityFlashTurret();
	void UpdateAI() override;
};

