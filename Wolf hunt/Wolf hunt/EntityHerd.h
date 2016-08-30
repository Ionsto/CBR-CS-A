#pragma once
#include "EntityLiving.h"
class EntityHerd :
	public EntityLiving
{
public:
	EntityHerd(World * world, Vector pos);
	~EntityHerd();
};

