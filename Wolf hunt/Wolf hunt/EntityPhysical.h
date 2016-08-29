#pragma once
#include "Entity.h"
class EntityPhysical : public Entity
{
public:
	EntityPhysical(World * world);
	~EntityPhysical();
	void Update();
	void UpdatePhysics();
};