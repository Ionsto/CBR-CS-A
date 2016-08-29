#pragma once
#include "EntityLiving.h"
#include "EntityAI.h"
class EntityGuard :
	public EntityAI
{
public:
	EntityGuard(World * world, Vector pos = Vector());
	~EntityGuard();
	void Update() override;
};

