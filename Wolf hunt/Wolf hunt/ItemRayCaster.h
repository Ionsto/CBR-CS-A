#pragma once
#include "Item.h"
#include "Entity.h"
class ItemRayCaster :
	public Item
{
public:
	ItemRayCaster();
	~ItemRayCaster();
	bool CanSeeEntity(Entity * me, Entity * them);
	float Distance(Vector pos, float Rot);
};

