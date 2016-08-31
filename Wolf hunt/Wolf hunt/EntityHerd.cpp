#include "EntityHerd.h"



EntityHerd::EntityHerd(World * world, Vector pos) : EntityLiving(world, pos)
{
	Type = EntityType::TypeHerd;
}


EntityHerd::~EntityHerd()
{
}
