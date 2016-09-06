#pragma once
#include "EntityLiving.h"
class EntityHerd :
	public EntityLiving
{
public:
	float MoveTowards;
	float MoveNormal;
	float MoveTogether;
	EntityHerd(World * world, Vector pos);
	~EntityHerd();
};

